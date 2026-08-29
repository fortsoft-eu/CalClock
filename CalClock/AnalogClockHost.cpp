#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include "AnalogClockHost.h"
#include <windows.h>
#include <cstring>
#include <cwchar>

static const DWORD PROFILE_104[14] = { 104, 5002, 5003, 51, 51, 27, 2, 0, 37, 2, 0, 50, 1, 13 };
static const DWORD PROFILE_130[14] = { 130, 5000, 5001, 63, 63, 35, 2, 0, 46, 2, 0, 64, 1, 18 };
static const DWORD PROFILE_166[14] = { 166, 5008, 5009, 81, 81, 43, 2, 0, 60, 2, 0, 80, 1, 20 };
static const DWORD PROFILE_198[14] = { 198, 5004, 5005, 97, 97, 53, 3, 0, 71, 3, 0, 95, 1, 24 };

typedef UINT(__fastcall* RegisterClockClassProc)(HINSTANCE);
typedef void(__fastcall* RenderClockProc)(void* state, void* unused, HDC targetDC);

static HMODULE timeDateModule = nullptr;
static RegisterClockClassProc registerClockClass = nullptr;
static RenderClockProc renderClock = nullptr;
static DWORD* analogProfile198 = nullptr;
static DWORD* activeAnalogProfile = nullptr;

static BYTE* FindModulePattern(BYTE* begin, size_t length, const BYTE* pattern, size_t patternLength) {
    if (begin == nullptr || pattern == nullptr || patternLength == 0 || length < patternLength) {
        return nullptr;
    }
    for (size_t offset = 0; offset <= length - patternLength; offset++) {
        if (memcmp(begin + offset, pattern, patternLength) == 0) {
            return begin + offset;
        }
    }
    return nullptr;
}

static bool ResolveAnalogClockInternals() {
    if (timeDateModule == nullptr) {
        return false;
    }
    BYTE* module = reinterpret_cast<BYTE*>(timeDateModule);
    IMAGE_DOS_HEADER* dosHeader = reinterpret_cast<IMAGE_DOS_HEADER*>(module);
    if (dosHeader->e_magic != IMAGE_DOS_SIGNATURE || dosHeader->e_lfanew <= 0) {
        return false;
    }
    IMAGE_NT_HEADERS32* ntHeaders = reinterpret_cast<IMAGE_NT_HEADERS32*>(module + dosHeader->e_lfanew);
    if (ntHeaders->Signature != IMAGE_NT_SIGNATURE || ntHeaders->OptionalHeader.Magic != IMAGE_NT_OPTIONAL_HDR32_MAGIC || ntHeaders->OptionalHeader.SizeOfImage == 0) {
        return false;
    }
    size_t imageSize = ntHeaders->OptionalHeader.SizeOfImage;
    BYTE* profile = FindModulePattern(module, imageSize, reinterpret_cast<const BYTE*>(PROFILE_198), sizeof(PROFILE_198));
    if (profile == nullptr || profile + sizeof(PROFILE_198) + sizeof(PROFILE_166) + sizeof(PROFILE_130) > module + imageSize ||
        memcmp(profile + sizeof(PROFILE_198), PROFILE_166, sizeof(PROFILE_166)) != 0 ||
        memcmp(profile + sizeof(PROFILE_198) + sizeof(PROFILE_166), PROFILE_130, sizeof(PROFILE_130)) != 0) {
        return false;
    }
    const BYTE registerPattern[] = { 0x8B, 0xFF, 0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x2C, 0x56, 0x33, 0xC0, 0xC7, 0x45, 0xE4, 0x04, 0x00, 0x00, 0x00, 0x68, 0x00, 0x7F, 0x00, 0x00, 0x50, 0x8B, 0xF1, 0x89, 0x45, 0xE0, 0x89, 0x45, 0xEC, 0x89, 0x45, 0xF8 };
    BYTE* registerAddress = nullptr;
    BYTE* search = module;
    size_t remaining = imageSize;
    DWORD expectedDescriptorAddress = static_cast<DWORD>(reinterpret_cast<ULONG_PTR>(profile - 0x200));
    while (remaining >= sizeof(registerPattern)) {
        BYTE* candidate = FindModulePattern(search, remaining, registerPattern, sizeof(registerPattern));
        if (candidate == nullptr) {
            break;
        }
        size_t candidateOffset = static_cast<size_t>(candidate - module);
        if (candidateOffset + 62 <= imageSize && candidate[55] == 0xC7 && candidate[56] == 0x45 && candidate[57] == 0xFC) {
            DWORD descriptorAddress = 0;
            CopyMemory(&descriptorAddress, candidate + 58, sizeof(descriptorAddress));
            if (descriptorAddress == expectedDescriptorAddress) {
                registerAddress = candidate;
                break;
            }
        }
        search = candidate + 1;
        remaining = imageSize - static_cast<size_t>(search - module);
    }
    const BYTE renderPattern[] = { 0x8B, 0xFF, 0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x40, 0x53, 0x56, 0x8B, 0xF1, 0x33, 0xC0, 0x57, 0x89, 0x75, 0xDC, 0x39, 0x46, 0x34 };
    BYTE* renderAddress = FindModulePattern(module, imageSize, renderPattern, sizeof(renderPattern));
    if (registerAddress == nullptr || renderAddress == nullptr) {
        return false;
    }
    BYTE* secondRenderAddress = FindModulePattern(renderAddress + 1, imageSize - static_cast<size_t>(renderAddress + 1 - module), renderPattern, sizeof(renderPattern));
    if (secondRenderAddress != nullptr) {
        return false;
    }
    registerClockClass = reinterpret_cast<RegisterClockClassProc>(registerAddress);
    renderClock = reinterpret_cast<RenderClockProc>(renderAddress);
    analogProfile198 = reinterpret_cast<DWORD*>(profile);
    activeAnalogProfile = nullptr;
    return true;
}

static bool IsAnalogClockClassRegistered() {
    if (timeDateModule == nullptr) {
        return false;
    }
    WNDCLASSW clockClass = {};
    return GetClassInfoW(reinterpret_cast<HINSTANCE>(timeDateModule), L"ClockWndMain", &clockClass) != FALSE;
}

static bool LoadAnalogClockClass() {
    if (sizeof(void*) != 4) {
        return false;
    }
    if (timeDateModule == nullptr) {
        wchar_t systemDirectory[MAX_PATH] = {};
        UINT length = GetSystemWow64DirectoryW(systemDirectory, ARRAYSIZE(systemDirectory));
        if (length == 0 || length >= ARRAYSIZE(systemDirectory)) {
            length = GetSystemDirectoryW(systemDirectory, ARRAYSIZE(systemDirectory));
        }
        if (length == 0 || length >= ARRAYSIZE(systemDirectory)) {
            return false;
        }
        wchar_t path[MAX_PATH] = {};
        swprintf_s(path, L"%s\\timedate.cpl", systemDirectory);
        timeDateModule = LoadLibraryW(path);
        if (timeDateModule == nullptr) {
            return false;
        }
        if (!ResolveAnalogClockInternals()) {
            FreeLibrary(timeDateModule);
            timeDateModule = nullptr;
            return false;
        }
    }
    if (IsAnalogClockClassRegistered()) {
        return true;
    }
    if (registerClockClass == nullptr && !ResolveAnalogClockInternals()) {
        return false;
    }
    if (registerClockClass == nullptr) {
        return false;
    }
    registerClockClass(reinterpret_cast<HINSTANCE>(timeDateModule));
    return IsAnalogClockClassRegistered();
}

static const DWORD* ProfileForSize(int size) {
    if (size == 104) {
        return PROFILE_104;
    }
    if (size == 166) {
        return PROFILE_166;
    }
    if (size == 198) {
        return PROFILE_198;
    }
    return PROFILE_130;
}

static bool ApplyAnalogProfile(int size, bool showSeconds) {
    if (!LoadAnalogClockClass()) {
        return false;
    }
    DWORD profile[14] = {};
    CopyMemory(profile, ProfileForSize(size), sizeof(profile));
    if (!showSeconds) {
        profile[11] = profile[12] = profile[13] = 0;
    }
    if (activeAnalogProfile == nullptr) {
        HDC screen = GetDC(nullptr);
        int dpi = screen == nullptr ? 96 : GetDeviceCaps(screen, LOGPIXELSX);
        if (screen != nullptr) {
            ReleaseDC(nullptr, screen);
        }
        activeAnalogProfile = analogProfile198 + (dpi <= 120 ? 28 : (dpi <= 144 ? 14 : 0));
    }
    DWORD oldProtect = 0;
    if (!VirtualProtect(activeAnalogProfile, sizeof(profile), PAGE_READWRITE, &oldProtect)) {
        return false;
    }
    CopyMemory(activeAnalogProfile, profile, sizeof(profile));
    DWORD ignored = 0;
    VirtualProtect(activeAnalogProfile, sizeof(profile), oldProtect, &ignored);
    return true;
}

HWND CreateAnalogClockControl(HWND parent, int x, int y, int size, bool showSeconds, bool visible) {
    if (parent == nullptr || !ApplyAnalogProfile(size, showSeconds)) {
        return nullptr;
    }
    DWORD style = WS_CHILD | 0x10 | (visible ? WS_VISIBLE : 0);
    return CreateWindowExW(0, L"ClockWndMain", L"", style, x, y, size, size, parent, reinterpret_cast<HMENU>(113),
        reinterpret_cast<HINSTANCE>(timeDateModule), nullptr);
}

void SetAnalogClockTime(HWND control, const SYSTEMTIME& time) {
    if (control != nullptr) {
        SendMessageW(control, WM_USER + 1, 0, reinterpret_cast<LPARAM>(&time));
    }
}

COLORREF ReadAnalogClockBackground(HWND control) {
    if (control == nullptr) {
        return GetSysColor(COLOR_WINDOW);
    }
    LONG_PTR stateValue = GetWindowLongPtrW(control, GWLP_USERDATA);
    if (stateValue == 0) {
        return GetSysColor(COLOR_WINDOW);
    }
    BYTE* state = reinterpret_cast<BYTE*>(stateValue);
    DWORD** backgroundAddress = reinterpret_cast<DWORD**>(state + 0x20);
    if (backgroundAddress != nullptr && *backgroundAddress != nullptr) {
        return static_cast<COLORREF>(**backgroundAddress & 0x00FFFFFF);
    }
    return GetSysColor(COLOR_WINDOW);
}

bool RenderAnalogClock(HWND control, HDC targetDC, DWORD background) {
    if (control == nullptr || targetDC == nullptr || renderClock == nullptr) {
        return false;
    }
    LONG_PTR stateValue = GetWindowLongPtrW(control, GWLP_USERDATA);
    if (stateValue == 0) {
        return false;
    }
    BYTE* state = reinterpret_cast<BYTE*>(stateValue);
    DWORD** backgroundAddress = reinterpret_cast<DWORD**>(state + 0x20);
    if (backgroundAddress == nullptr || *backgroundAddress == nullptr) {
        return false;
    }
    DWORD oldBackground = **backgroundAddress;
    **backgroundAddress = background;
    renderClock(state, nullptr, targetDC);
    **backgroundAddress = oldBackground;
    return true;
}

void ShutdownAnalogClockHost() {
    registerClockClass = nullptr;
    renderClock = nullptr;
    analogProfile198 = nullptr;
    activeAnalogProfile = nullptr;
    if (timeDateModule != nullptr) {
        FreeLibrary(timeDateModule);
        timeDateModule = nullptr;
    }
}
