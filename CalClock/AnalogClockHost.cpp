#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include "AnalogClockHost.h"
#include <windows.h>
#include <cstring>
#include <cwchar>

static const int ANALOG_PROFILE_COUNT = 4;
static const int ANALOG_PROFILE_LENGTH = 14;
static const int ANALOG_PROFILE_SIZES[ANALOG_PROFILE_COUNT] = {
    104,
    130,
    166,
    198
};

typedef UINT(__fastcall* RegisterClockClassProc)(HINSTANCE);
typedef ATOM(WINAPI* VistaRegisterClockClassProc)(HINSTANCE);
typedef void(__fastcall* RenderClockProc)(void* state, void* unused, HDC targetDC);
typedef BOOL(__fastcall* VistaLoadClockResourcesProc)(void* state);
typedef void(__fastcall* VistaReleaseClockResourcesProc)(void* state);

enum AnalogClockImplementation {
    ANALOG_CLOCK_UNKNOWN,
    ANALOG_CLOCK_MODERN,
    ANALOG_CLOCK_WINDOWS_7,
    ANALOG_CLOCK_VISTA
};

static HMODULE timeDateModule = nullptr;
static RegisterClockClassProc registerClockClass = nullptr;
static VistaRegisterClockClassProc vistaRegisterClockClass = nullptr;
static RenderClockProc renderClock = nullptr;
static VistaLoadClockResourcesProc vistaLoadClockResources = nullptr;
static VistaReleaseClockResourcesProc vistaReleaseClockResources = nullptr;
static DWORD* analogProfileTable = nullptr;
static DWORD detectedAnalogProfiles[ANALOG_PROFILE_COUNT][ANALOG_PROFILE_LENGTH] = {};
static AnalogClockImplementation analogClockImplementation = ANALOG_CLOCK_UNKNOWN;

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

static bool ContainsPattern(const BYTE* begin, size_t length, const BYTE* pattern, size_t patternLength) {
    return FindModulePattern(const_cast<BYTE*>(begin), length, pattern, patternLength) != nullptr;
}

static bool GetExecutableCodeRange(BYTE* module, IMAGE_NT_HEADERS32* ntHeaders, BYTE** codeBegin, size_t* codeSize) {
    if (module == nullptr || ntHeaders == nullptr || codeBegin == nullptr || codeSize == nullptr) {
        return false;
    }
    IMAGE_SECTION_HEADER* section = IMAGE_FIRST_SECTION(ntHeaders);
    BYTE* selectedBegin = nullptr;
    size_t selectedSize = 0;
    for (WORD index = 0; index < ntHeaders->FileHeader.NumberOfSections; index++) {
        if ((section[index].Characteristics & IMAGE_SCN_MEM_EXECUTE) == 0) {
            continue;
        }
        size_t size = section[index].Misc.VirtualSize;
        if (size == 0 || section[index].VirtualAddress >= ntHeaders->OptionalHeader.SizeOfImage || size > ntHeaders->OptionalHeader.SizeOfImage - section[index].VirtualAddress) {
            continue;
        }
        if (size > selectedSize) {
            selectedBegin = module + section[index].VirtualAddress;
            selectedSize = size;
        }
    }
    if (selectedBegin == nullptr) {
        return false;
    }
    *codeBegin = selectedBegin;
    *codeSize = selectedSize;
    return true;
}

static int AnalogProfileIndex(DWORD size) {
    for (int index = 0; index < ANALOG_PROFILE_COUNT; index++) {
        if (size == static_cast<DWORD>(ANALOG_PROFILE_SIZES[index])) {
            return index;
        }
    }
    return -1;
}

static bool IsValidAnalogProfile(const DWORD* profile) {
    return !(profile == nullptr
        || AnalogProfileIndex(profile[0]) < 0
        || profile[1] == 0 || profile[2] == 0
        || profile[1] == profile[2]
        || profile[3] == 0
        || profile[3] != profile[4]
        || profile[3] > profile[0]
        || profile[5] == 0
        || profile[5] > profile[0]
        || profile[6] > 10
        || profile[7] != 0
        || profile[8] > profile[0]
        || profile[9] > 10
        || profile[10] != 0
        || profile[11] > profile[0]
        || profile[12] > 10
        || profile[13] > profile[0]);
}

static DWORD* FindAnalogProfileTable(BYTE* module, size_t imageSize) {
    const size_t tableSize = ANALOG_PROFILE_COUNT * ANALOG_PROFILE_LENGTH * sizeof(DWORD);
    DWORD* result = nullptr;
    for (size_t offset = 0; offset + tableSize <= imageSize; offset += sizeof(DWORD)) {
        DWORD* candidate = reinterpret_cast<DWORD*>(module + offset);
        bool foundSizes[ANALOG_PROFILE_COUNT] = {};
        bool valid = true;
        for (int row = 0; row < ANALOG_PROFILE_COUNT; row++) {
            DWORD* profile = candidate + row * ANALOG_PROFILE_LENGTH;
            int profileIndex = AnalogProfileIndex(profile[0]);
            if (profileIndex < 0 || foundSizes[profileIndex] || !IsValidAnalogProfile(profile)) {
                valid = false;
                break;
            }
            foundSizes[profileIndex] = true;
        }
        if (!valid) {
            continue;
        }
        if (result != nullptr) {
            return nullptr;
        }
        result = candidate;
    }
    return result;
}

static void CacheAnalogProfiles(DWORD* profileTable) {
    ZeroMemory(detectedAnalogProfiles, sizeof(detectedAnalogProfiles));
    for (int row = 0; row < ANALOG_PROFILE_COUNT; row++) {
        DWORD* profile = profileTable + row * ANALOG_PROFILE_LENGTH;
        int profileIndex = AnalogProfileIndex(profile[0]);
        if (profileIndex >= 0) {
            CopyMemory(detectedAnalogProfiles[profileIndex], profile, ANALOG_PROFILE_LENGTH * sizeof(DWORD));
        }
    }
}

static BYTE* FindPreviousFunctionStart(BYTE* codeBegin, BYTE* address) {
    const BYTE prolog[] = {
        0x8B,
        0xFF,
        0x55,
        0x8B,
        0xEC
    };
    if (codeBegin == nullptr || address == nullptr || address < codeBegin + sizeof(prolog)) {
        return nullptr;
    }
    size_t distance = static_cast<size_t>(address - codeBegin);
    size_t maximumDistance = distance < 192 ? distance : 192;
    for (size_t back = 0; back <= maximumDistance; back++) {
        BYTE* candidate = address - back;
        if (candidate >= codeBegin && memcmp(candidate, prolog, sizeof(prolog)) == 0) {
            return candidate;
        }
    }
    return nullptr;
}

static BYTE* FindClockRegisterAddress(BYTE* module, size_t imageSize, BYTE* codeBegin, size_t codeSize, bool* usesStackArgument) {
    const BYTE classNameBytes[] = {
        0x43,
        0,
        0x6C,
        0,
        0x6F,
        0,
        0x63,
        0,
        0x6B,
        0,
        0x57,
        0,
        0x6E,
        0,
        0x64,
        0,
        0x4D,
        0,
        0x61,
        0,
        0x69,
        0,
        0x6E,
        0,
        0,
        0
    };
    const BYTE cursorPattern[] = {
        0x68,
        0x00,
        0x7F,
        0x00,
        0x00
    };
    const BYTE stackArgumentPattern[] = {
        0x8B,
        0x75,
        0x08
    };
    const BYTE fastcallPattern[] = {
        0x8B,
        0xF1
    };
    BYTE* result = nullptr;
    bool resultUsesStackArgument = false;
    BYTE* stringSearch = module;
    size_t stringRemaining = imageSize;
    while (stringRemaining >= sizeof(classNameBytes)) {
        BYTE* className = FindModulePattern(stringSearch, stringRemaining, classNameBytes, sizeof(classNameBytes));
        if (className == nullptr) {
            break;
        }
        DWORD classAddress = static_cast<DWORD>(reinterpret_cast<ULONG_PTR>(className));
        BYTE addressBytes[sizeof(classAddress)] = {};
        CopyMemory(addressBytes, &classAddress, sizeof(addressBytes));
        BYTE* referenceSearch = codeBegin;
        size_t referenceRemaining = codeSize;
        while (referenceRemaining >= sizeof(addressBytes)) {
            BYTE* reference = FindModulePattern(referenceSearch, referenceRemaining, addressBytes, sizeof(addressBytes));
            if (reference == nullptr) {
                break;
            }
            BYTE* candidate = FindPreviousFunctionStart(codeBegin, reference);
            if (candidate != nullptr) {
                size_t candidateLength = static_cast<size_t>(reference + sizeof(addressBytes) - candidate);
                bool hasCursor = ContainsPattern(candidate, candidateLength, cursorPattern, sizeof(cursorPattern));
                bool stackArgument = ContainsPattern(candidate, candidateLength, stackArgumentPattern, sizeof(stackArgumentPattern));
                bool fastcallArgument = ContainsPattern(candidate, candidateLength, fastcallPattern, sizeof(fastcallPattern));
                if (hasCursor && stackArgument != fastcallArgument) {
                    if (result != nullptr && result != candidate) {
                        return nullptr;
                    }
                    result = candidate;
                    resultUsesStackArgument = stackArgument;
                }
            }
            referenceSearch = reference + 1;
            referenceRemaining = codeSize - static_cast<size_t>(referenceSearch - codeBegin);
        }
        stringSearch = className + sizeof(classNameBytes);
        stringRemaining = imageSize - static_cast<size_t>(stringSearch - module);
    }
    if (result != nullptr && usesStackArgument != nullptr) {
        *usesStackArgument = resultUsesStackArgument;
    }
    return result;
}

static BYTE* FindModernClockRenderAddress(BYTE* codeBegin, size_t codeSize) {
    const BYTE prolog[] = {
        0x8B,
        0xFF,
        0x55,
        0x8B,
        0xEC
    };
    const BYTE stateArgumentPattern[] = {
        0x8B,
        0xF1
    };
    const BYTE readyPattern[] = {
        0x39,
        0x46,
        0x34
    };
    const BYTE facePattern[] = {
        0x39,
        0x46,
        0x10
    };
    const BYTE remoteDirectPattern[] = {
        0x83,
        0x7E,
        0x60,
        0x00
    };
    const BYTE remoteAddressPattern[] = {
        0x8D,
        0x5E,
        0x60
    };
    const BYTE secondsPattern[] = {
        0x83,
        0x7E,
        0x58,
        0x00
    };
    BYTE* result = nullptr;
    BYTE* search = codeBegin;
    size_t remaining = codeSize;
    while (remaining >= sizeof(prolog)) {
        BYTE* candidate = FindModulePattern(search, remaining, prolog, sizeof(prolog));
        if (candidate == nullptr) {
            break;
        }
        BYTE* next = FindModulePattern(candidate + sizeof(prolog), codeSize - static_cast<size_t>(candidate + sizeof(prolog) - codeBegin), prolog, sizeof(prolog));
        size_t functionLength = next == nullptr ? codeSize - static_cast<size_t>(candidate - codeBegin) : static_cast<size_t>(next - candidate);
        if (functionLength > 2048) {
            functionLength = 2048;
        }
        size_t argumentLength = functionLength < 32 ? functionLength : 32;
        size_t initialLength = functionLength < 96 ? functionLength : 96;
        bool stateArgument = ContainsPattern(candidate, argumentLength, stateArgumentPattern, sizeof(stateArgumentPattern));
        bool readyState = ContainsPattern(candidate, initialLength, readyPattern, sizeof(readyPattern));
        bool faceState = ContainsPattern(candidate, initialLength, facePattern, sizeof(facePattern));
        bool remoteState = ContainsPattern(candidate, functionLength, remoteDirectPattern, sizeof(remoteDirectPattern))
            || ContainsPattern(candidate, functionLength, remoteAddressPattern, sizeof(remoteAddressPattern));
        bool secondsState = ContainsPattern(candidate, functionLength, secondsPattern, sizeof(secondsPattern));
        if (stateArgument && readyState && faceState && remoteState && secondsState) {
            if (result != nullptr) {
                return nullptr;
            }
            result = candidate;
        }
        search = candidate + 1;
        remaining = codeSize - static_cast<size_t>(search - codeBegin);
    }
    return result;
}

static BYTE* FindLegacyClockRegisterAddress(BYTE* module, size_t imageSize) {
    const BYTE registerPattern[] = {
        0x8B,
        0xFF,
        0x55,
        0x8B,
        0xEC,
        0x83,
        0xEC,
        0x28,
        0x56,
        0x8B,
        0x75,
        0x08,
        0x57,
        0x8D,
        0x45,
        0xD8,
        0x50
    };
    BYTE* registerAddress = nullptr;
    BYTE* search = module;
    size_t remaining = imageSize;
    while (remaining >= sizeof(registerPattern)) {
        BYTE* candidate = FindModulePattern(search, remaining, registerPattern, sizeof(registerPattern));
        if (candidate == nullptr) {
            break;
        }
        if (candidate + 22 <= module + imageSize && candidate[17] == 0xBF) {
            DWORD classAddressValue = 0;
            CopyMemory(&classAddressValue, candidate + 18, sizeof(classAddressValue));
            const wchar_t* className = reinterpret_cast<const wchar_t*>(static_cast<ULONG_PTR>(classAddressValue));
            if (reinterpret_cast<const BYTE*>(className) >= module &&
                reinterpret_cast<const BYTE*>(className) + sizeof(L"ClockWndMain") <= module + imageSize &&
                wcscmp(className, L"ClockWndMain") == 0) {
                if (registerAddress != nullptr) {
                    return nullptr;
                }
                registerAddress = candidate;
            }
        }
        search = candidate + 1;
        remaining = imageSize - static_cast<size_t>(search - module);
    }
    return registerAddress;
}

static bool ResolveWindows7AnalogClockInternals(BYTE* module, size_t imageSize) {
    const BYTE renderPattern[] = {
        0x8B,
        0xFF,
        0x55,
        0x8B,
        0xEC,
        0x83,
        0xEC,
        0x34,
        0x56,
        0x57,
        0x8B,
        0xF1,
        0x33,
        0xFF,
        0x39,
        0x7E,
        0x34
    };
    BYTE* registerAddress = FindLegacyClockRegisterAddress(module, imageSize);
    BYTE* renderAddress = FindModulePattern(module, imageSize, renderPattern, sizeof(renderPattern));
    if (registerAddress == nullptr || renderAddress == nullptr) {
        return false;
    }
    BYTE* secondRenderAddress = FindModulePattern(renderAddress + 1, imageSize - static_cast<size_t>(renderAddress + 1 - module), renderPattern, sizeof(renderPattern));
    if (secondRenderAddress != nullptr) {
        return false;
    }
    vistaRegisterClockClass = reinterpret_cast<VistaRegisterClockClassProc>(registerAddress);
    renderClock = reinterpret_cast<RenderClockProc>(renderAddress);
    analogClockImplementation = ANALOG_CLOCK_WINDOWS_7;
    return true;
}

static bool ResolveVistaAnalogClockInternals(BYTE* module, size_t imageSize) {
    const BYTE renderPattern[] = {
        0x8B,
        0xFF,
        0x55,
        0x8B,
        0xEC,
        0x83,
        0xEC,
        0x3C,
        0x56,
        0x57,
        0x8B,
        0xF1,
        0x33,
        0xFF,
        0x39,
        0x7E,
        0x44
    };
    const BYTE loadPattern[] = {
        0x8B,
        0xFF,
        0x55,
        0x8B,
        0xEC,
        0x51,
        0x56,
        0x57,
        0x8B,
        0xF1,
        0x33,
        0xFF,
        0x33,
        0xC0,
        0x39,
        0x7E,
        0x68
    };
    const BYTE releasePattern[] = {
        0x8B,
        0xFF,
        0x56,
        0x8B,
        0xF1,
        0x8B,
        0x4E,
        0x14,
        0x57,
        0x33,
        0xFF,
        0x3B,
        0xCF
    };
    BYTE* registerAddress = FindLegacyClockRegisterAddress(module, imageSize);
    BYTE* renderAddress = FindModulePattern(module, imageSize, renderPattern, sizeof(renderPattern));
    BYTE* loadAddress = FindModulePattern(module, imageSize, loadPattern, sizeof(loadPattern));
    BYTE* releaseAddress = FindModulePattern(module, imageSize, releasePattern, sizeof(releasePattern));
    if (registerAddress == nullptr || renderAddress == nullptr || loadAddress == nullptr || releaseAddress == nullptr) {
        return false;
    }
    BYTE* secondRenderAddress = FindModulePattern(renderAddress + 1, imageSize - static_cast<size_t>(renderAddress + 1 - module), renderPattern, sizeof(renderPattern));
    BYTE* secondLoadAddress = FindModulePattern(loadAddress + 1, imageSize - static_cast<size_t>(loadAddress + 1 - module), loadPattern, sizeof(loadPattern));
    BYTE* secondReleaseAddress = FindModulePattern(releaseAddress + 1, imageSize - static_cast<size_t>(releaseAddress + 1 - module), releasePattern, sizeof(releasePattern));
    if (secondRenderAddress != nullptr || secondLoadAddress != nullptr || secondReleaseAddress != nullptr) {
        return false;
    }
    vistaRegisterClockClass = reinterpret_cast<VistaRegisterClockClassProc>(registerAddress);
    renderClock = reinterpret_cast<RenderClockProc>(renderAddress);
    vistaLoadClockResources = reinterpret_cast<VistaLoadClockResourcesProc>(loadAddress);
    vistaReleaseClockResources = reinterpret_cast<VistaReleaseClockResourcesProc>(releaseAddress);
    analogClockImplementation = ANALOG_CLOCK_VISTA;
    return true;
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
    BYTE* codeBegin = nullptr;
    size_t codeSize = 0;
    if (!GetExecutableCodeRange(module, ntHeaders, &codeBegin, &codeSize)) {
        return false;
    }
    DWORD* profileTable = FindAnalogProfileTable(module, imageSize);
    if (profileTable == nullptr) {
        return ResolveVistaAnalogClockInternals(module, imageSize);
    }
    analogProfileTable = profileTable;
    CacheAnalogProfiles(profileTable);
    if (profileTable[0] == 104 && ResolveWindows7AnalogClockInternals(module, imageSize)) {
        return true;
    }
    bool usesStackArgument = false;
    BYTE* registerAddress = FindClockRegisterAddress(module, imageSize, codeBegin, codeSize, &usesStackArgument);
    if (registerAddress != nullptr && usesStackArgument) {
        registerAddress = nullptr;
    }
    const BYTE renderPattern[] = {
        0x8B,
        0xFF,
        0x55,
        0x8B,
        0xEC,
        0x83,
        0xEC,
        0x40,
        0x53,
        0x56,
        0x8B,
        0xF1,
        0x33,
        0xC0,
        0x57,
        0x89,
        0x75,
        0xDC,
        0x39,
        0x46,
        0x34
    };
    BYTE* renderAddress = FindModulePattern(codeBegin, codeSize, renderPattern, sizeof(renderPattern));
    if (renderAddress != nullptr) {
        BYTE* secondRenderAddress = FindModulePattern(renderAddress + 1, codeSize - static_cast<size_t>(renderAddress + 1 - codeBegin), renderPattern, sizeof(renderPattern));
        if (secondRenderAddress != nullptr) {
            renderAddress = nullptr;
        }
    }
    if (renderAddress == nullptr) {
        renderAddress = FindModernClockRenderAddress(codeBegin, codeSize);
    }
    if (registerAddress == nullptr || renderAddress == nullptr) {
        return false;
    }
    registerClockClass = reinterpret_cast<RegisterClockClassProc>(registerAddress);
    renderClock = reinterpret_cast<RenderClockProc>(renderAddress);
    analogClockImplementation = ANALOG_CLOCK_MODERN;
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
    if (registerClockClass == nullptr && vistaRegisterClockClass == nullptr && !ResolveAnalogClockInternals()) {
        return false;
    }
    if (analogClockImplementation == ANALOG_CLOCK_VISTA || analogClockImplementation == ANALOG_CLOCK_WINDOWS_7) {
        if (vistaRegisterClockClass == nullptr) {
            return false;
        }
        vistaRegisterClockClass(reinterpret_cast<HINSTANCE>(timeDateModule));
    } else {
        if (registerClockClass == nullptr) {
            return false;
        }
        registerClockClass(reinterpret_cast<HINSTANCE>(timeDateModule));
    }
    return IsAnalogClockClassRegistered();
}

static const DWORD* ProfileForSize(int size) {
    int profileIndex = AnalogProfileIndex(size);
    if (profileIndex < 0) {
        profileIndex = AnalogProfileIndex(130);
    }
    return detectedAnalogProfiles[profileIndex];
}

static bool ApplyAnalogProfile(int size, bool showSeconds) {
    if (!LoadAnalogClockClass()) {
        return false;
    }
    if (analogClockImplementation == ANALOG_CLOCK_VISTA) {
        return true;
    }
    DWORD profile[14] = {};
    CopyMemory(profile, ProfileForSize(size), sizeof(profile));
    if (!showSeconds) {
        profile[11] = profile[12] = profile[13] = 0;
    }
    if (analogProfileTable == nullptr) {
        return false;
    }
    const size_t tableSize = ANALOG_PROFILE_COUNT * ANALOG_PROFILE_LENGTH * sizeof(DWORD);
    DWORD oldProtect = 0;
    if (!VirtualProtect(analogProfileTable, tableSize, PAGE_READWRITE, &oldProtect)) {
        return false;
    }
    for (int row = 0; row < ANALOG_PROFILE_COUNT; row++) {
        CopyMemory(analogProfileTable + row * ANALOG_PROFILE_LENGTH, profile, sizeof(profile));
    }
    DWORD ignored = 0;
    VirtualProtect(analogProfileTable, tableSize, oldProtect, &ignored);
    return true;
}

static bool ConfigureVistaAnalogClock(HWND control, int size, bool showSeconds) {
    LONG_PTR stateValue = GetWindowLongPtrW(control, GWLP_USERDATA);
    if (stateValue == 0 || vistaLoadClockResources == nullptr || vistaReleaseClockResources == nullptr) {
        return false;
    }
    BYTE* state = reinterpret_cast<BYTE*>(stateValue);
    DWORD smallResources = size == 103 || size == 129 ? 8 : 0;
    DWORD highDpiResources = size == 129 || size == 160 ? 1 : 0;
    if (*reinterpret_cast<DWORD*>(state + 0x68) != smallResources || *reinterpret_cast<DWORD*>(state + 0x74) != highDpiResources) {
        vistaReleaseClockResources(state);
        *reinterpret_cast<DWORD*>(state + 0x68) = smallResources;
        *reinterpret_cast<DWORD*>(state + 0x74) = highDpiResources;
        if (!vistaLoadClockResources(state)) {
            return false;
        }
    }
    *reinterpret_cast<DWORD*>(state + 0x78) = size;
    SetWindowPos(control, nullptr, 0, 0, size, size, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
    RECT client = {};
    GetClientRect(control, &client);
    CopyMemory(state + 0x28, &client, sizeof(client));
    *reinterpret_cast<DWORD*>(state + 0x38) = size / 2;
    *reinterpret_cast<DWORD*>(state + 0x3C) = size / 2;
    *reinterpret_cast<DWORD*>(state + 0x40) = size / 2;
    *reinterpret_cast<DWORD*>(state + 0x44) = 1;
    *reinterpret_cast<DWORD*>(state + 0x68) = showSeconds && (size == 128 || size == 160) ? 0 : 8;
    return true;
}

bool ConfigureAnalogClockControl(HWND control, int size, bool showSeconds) {
    if (analogClockImplementation == ANALOG_CLOCK_VISTA) {
        return ConfigureVistaAnalogClock(control, size, showSeconds);
    }
    LONG_PTR stateValue = GetWindowLongPtrW(control, GWLP_USERDATA);
    if (stateValue == 0) {
        return false;
    }
    BYTE* state = reinterpret_cast<BYTE*>(stateValue);
    *reinterpret_cast<DWORD*>(state + 0x60) = 0;
    return true;
}

bool SetAnalogClockSeconds(HWND control, int size, bool showSeconds) {
    LONG_PTR stateValue = GetWindowLongPtrW(control, GWLP_USERDATA);
    if (stateValue == 0) {
        return false;
    }
    BYTE* state = reinterpret_cast<BYTE*>(stateValue);
    if (analogClockImplementation == ANALOG_CLOCK_VISTA) {
        *reinterpret_cast<DWORD*>(state + 0x68) = showSeconds && (size == 128 || size == 160) ? 0 : 8;
        return true;
    }
    const DWORD* profile = ProfileForSize(size);
    DWORD* instanceProfile = reinterpret_cast<DWORD*>(state + 0x64);
    if (memcmp(instanceProfile, profile, 11 * sizeof(DWORD)) != 0) {
        return false;
    }
    for (int index = 11; index < ANALOG_PROFILE_LENGTH; index++) {
        instanceProfile[index] = showSeconds ? profile[index] : 0;
    }
    return true;
}

HWND CreateAnalogClockControl(HWND parent, int x, int y, int size, bool showSeconds, bool visible) {
    if (parent == nullptr || !ApplyAnalogProfile(size, showSeconds)) {
        return nullptr;
    }
    DWORD style = WS_CHILD | 0x10 | (visible ? WS_VISIBLE : 0);
    if (analogClockImplementation == ANALOG_CLOCK_VISTA && (size == 103 || size == 129)) {
        style |= 0x8;
    }
    HWND control = CreateWindowExW(0, L"ClockWndMain", L"", style, x, y, size, size, parent, reinterpret_cast<HMENU>(113), reinterpret_cast<HINSTANCE>(timeDateModule), nullptr);
    if (control != nullptr) {
        if (!ConfigureAnalogClockControl(control, size, showSeconds)) {
            DestroyWindow(control);
            return nullptr;
        }
    }
    return control;
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
    if (analogClockImplementation == ANALOG_CLOCK_VISTA || analogClockImplementation == ANALOG_CLOCK_WINDOWS_7) {
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
    RECT client = {};
    if (!GetClientRect(control, &client)) {
        return false;
    }
    COLORREF color = RGB(static_cast<BYTE>(background >> 16), static_cast<BYTE>(background >> 8), static_cast<BYTE>(background));
    HBRUSH brush = CreateSolidBrush(color);
    FillRect(targetDC, &client, brush);
    DeleteObject(brush);
    if (analogClockImplementation == ANALOG_CLOCK_VISTA) {
        renderClock(reinterpret_cast<void*>(stateValue), nullptr, targetDC);
        return true;
    }
    if (analogClockImplementation == ANALOG_CLOCK_WINDOWS_7) {
        renderClock(reinterpret_cast<void*>(stateValue), nullptr, targetDC);
        return true;
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

int GetSupportedAnalogClockSizes(int* sizes, int capacity) {
    if (!LoadAnalogClockClass()) {
        return 0;
    }
    const int vistaSizes[] = {
        103,
        128,
        129,
        160
    };
    const int otherSizes[] = {
        104,
        130,
        166,
        198
    };
    const int* supportedSizes = analogClockImplementation == ANALOG_CLOCK_VISTA ? vistaSizes : otherSizes;
    int count = analogClockImplementation == ANALOG_CLOCK_VISTA ? ARRAYSIZE(vistaSizes) : ARRAYSIZE(otherSizes);
    if (sizes != nullptr && capacity > 0) {
        int copyCount = capacity < count ? capacity : count;
        CopyMemory(sizes, supportedSizes, copyCount * sizeof(int));
    }
    return count;
}

bool AnalogClockSupportsSeconds(int size) {
    if (!LoadAnalogClockClass()) {
        return true;
    }
    return analogClockImplementation != ANALOG_CLOCK_VISTA || size == 128 || size == 160;
}

void ShutdownAnalogClockHost() {
    registerClockClass = nullptr;
    vistaRegisterClockClass = nullptr;
    renderClock = nullptr;
    vistaLoadClockResources = nullptr;
    vistaReleaseClockResources = nullptr;
    analogProfileTable = nullptr;
    ZeroMemory(detectedAnalogProfiles, sizeof(detectedAnalogProfiles));
    analogClockImplementation = ANALOG_CLOCK_UNKNOWN;
    if (timeDateModule != nullptr) {
        FreeLibrary(timeDateModule);
        timeDateModule = nullptr;
    }
}
