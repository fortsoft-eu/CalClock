#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include "TimeZoneSupport.h"
#include <windows.h>
#include <algorithm>
#include <cwchar>

typedef DWORD(WINAPI* EnumDynamicTimeZoneInformationProc)(DWORD index, PDYNAMIC_TIME_ZONE_INFORMATION timeZoneInformation);
typedef DWORD(WINAPI* GetDynamicTimeZoneInformationProc)(PDYNAMIC_TIME_ZONE_INFORMATION timeZoneInformation);
typedef BOOL(WINAPI* GetTimeZoneInformationForYearProc)(USHORT year, PDYNAMIC_TIME_ZONE_INFORMATION dynamicTimeZoneInformation, LPTIME_ZONE_INFORMATION timeZoneInformation);
typedef BOOL(WINAPI* SystemTimeToTzSpecificLocalTimeExProc)(const DYNAMIC_TIME_ZONE_INFORMATION* timeZoneInformation, const SYSTEMTIME* universalTime, SYSTEMTIME* localTime);

struct RegistryTimeZoneInformation {
    LONG bias;
    LONG standardBias;
    LONG daylightBias;
    SYSTEMTIME standardDate;
    SYSTEMTIME daylightDate;
};

static FARPROC FindProcedure(const wchar_t* moduleName, const char* procedureName) {
    HMODULE module = GetModuleHandleW(moduleName);
    return module == nullptr ? nullptr : GetProcAddress(module, procedureName);
}

static EnumDynamicTimeZoneInformationProc GetEnumDynamicTimeZoneInformationProc() {
    static EnumDynamicTimeZoneInformationProc procedure = reinterpret_cast<EnumDynamicTimeZoneInformationProc>(FindProcedure(L"Advapi32.dll", "EnumDynamicTimeZoneInformation"));
    return procedure;
}

static GetDynamicTimeZoneInformationProc GetGetDynamicTimeZoneInformationProc() {
    static GetDynamicTimeZoneInformationProc procedure = reinterpret_cast<GetDynamicTimeZoneInformationProc>(FindProcedure(L"Kernel32.dll", "GetDynamicTimeZoneInformation"));
    return procedure;
}

static GetTimeZoneInformationForYearProc GetGetTimeZoneInformationForYearProc() {
    static GetTimeZoneInformationForYearProc procedure = reinterpret_cast<GetTimeZoneInformationForYearProc>(FindProcedure(L"Kernel32.dll", "GetTimeZoneInformationForYear"));
    return procedure;
}

static SystemTimeToTzSpecificLocalTimeExProc GetSystemTimeToTzSpecificLocalTimeExProc() {
    static SystemTimeToTzSpecificLocalTimeExProc procedure = reinterpret_cast<SystemTimeToTzSpecificLocalTimeExProc>(FindProcedure(L"Kernel32.dll", "SystemTimeToTzSpecificLocalTimeEx"));
    return procedure;
}

static bool ReadRegistryString(HKEY key, const wchar_t* name, wchar_t* value, DWORD characterCount) {
    if (key == nullptr || name == nullptr || value == nullptr || characterCount == 0) {
        return false;
    }
    DWORD type = 0;
    DWORD bytes = characterCount * sizeof(wchar_t);
    LSTATUS status = RegQueryValueExW(key, name, nullptr, &type, reinterpret_cast<BYTE*>(value), &bytes);
    if (status != ERROR_SUCCESS || (type != REG_SZ && type != REG_EXPAND_SZ)) {
        value[0] = L'\0';
        return false;
    }
    value[characterCount - 1] = L'\0';
    return true;
}

static void CopyTimeZoneInformation(const DYNAMIC_TIME_ZONE_INFORMATION& source, TIME_ZONE_INFORMATION* destination) {
    ZeroMemory(destination, sizeof(*destination));
    destination->Bias = source.Bias;
    wcscpy_s(destination->StandardName, source.StandardName);
    destination->StandardDate = source.StandardDate;
    destination->StandardBias = source.StandardBias;
    wcscpy_s(destination->DaylightName, source.DaylightName);
    destination->DaylightDate = source.DaylightDate;
    destination->DaylightBias = source.DaylightBias;
    if (source.DynamicDaylightTimeDisabled) {
        ZeroMemory(&destination->StandardDate, sizeof(destination->StandardDate));
        ZeroMemory(&destination->DaylightDate, sizeof(destination->DaylightDate));
    }
}

static void LoadTimeZoneListFromRegistry(std::vector<DYNAMIC_TIME_ZONE_INFORMATION>* zones) {
    HKEY root = nullptr;
    if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Time Zones", 0, KEY_READ, &root) != ERROR_SUCCESS) {
        return;
    }
    for (DWORD index = 0;; index++) {
        wchar_t keyName[128] = {};
        DWORD keyNameLength = ARRAYSIZE(keyName);
        LSTATUS enumerationStatus = RegEnumKeyExW(root, index, keyName, &keyNameLength, nullptr, nullptr, nullptr, nullptr);
        if (enumerationStatus == ERROR_NO_MORE_ITEMS) {
            break;
        }
        if (enumerationStatus != ERROR_SUCCESS) {
            continue;
        }
        HKEY key = nullptr;
        if (RegOpenKeyExW(root, keyName, 0, KEY_READ, &key) != ERROR_SUCCESS) {
            continue;
        }
        RegistryTimeZoneInformation registryInformation = {};
        DWORD type = 0;
        DWORD bytes = sizeof(registryInformation);
        LSTATUS informationStatus = RegQueryValueExW(key, L"TZI", nullptr, &type, reinterpret_cast<BYTE*>(&registryInformation), &bytes);
        if (informationStatus == ERROR_SUCCESS && type == REG_BINARY && bytes == sizeof(registryInformation)) {
            DYNAMIC_TIME_ZONE_INFORMATION zone = {};
            zone.Bias = registryInformation.bias;
            zone.StandardBias = registryInformation.standardBias;
            zone.DaylightBias = registryInformation.daylightBias;
            zone.StandardDate = registryInformation.standardDate;
            zone.DaylightDate = registryInformation.daylightDate;
            ReadRegistryString(key, L"Std", zone.StandardName, ARRAYSIZE(zone.StandardName));
            ReadRegistryString(key, L"Dlt", zone.DaylightName, ARRAYSIZE(zone.DaylightName));
            wcscpy_s(zone.TimeZoneKeyName, keyName);
            if (zone.StandardName[0] == L'\0') {
                wcscpy_s(zone.StandardName, keyName);
            }
            if (zone.DaylightName[0] == L'\0') {
                wcscpy_s(zone.DaylightName, zone.StandardName);
            }
            zones->push_back(zone);
        }
        RegCloseKey(key);
    }
    RegCloseKey(root);
}

void LoadTimeZoneList(std::vector<DYNAMIC_TIME_ZONE_INFORMATION>* zones) {
    if (zones == nullptr) {
        return;
    }
    zones->clear();
    EnumDynamicTimeZoneInformationProc enumerate = GetEnumDynamicTimeZoneInformationProc();
    if (enumerate != nullptr) {
        for (DWORD index = 0;; index++) {
            DYNAMIC_TIME_ZONE_INFORMATION zone = {};
            DWORD result = enumerate(index, &zone);
            if (result == ERROR_NO_MORE_ITEMS) {
                break;
            }
            if (result != ERROR_SUCCESS) {
                break;
            }
            zones->push_back(zone);
        }
    }
    if (zones->empty()) {
        LoadTimeZoneListFromRegistry(zones);
    }
    std::sort(zones->begin(), zones->end(), [](const DYNAMIC_TIME_ZONE_INFORMATION& left, const DYNAMIC_TIME_ZONE_INFORMATION& right) {
        return _wcsicmp(left.StandardName, right.StandardName) < 0;
    });
}

std::wstring GetSystemTimeZoneKey(const std::vector<DYNAMIC_TIME_ZONE_INFORMATION>& zones) {
    GetDynamicTimeZoneInformationProc getDynamic = GetGetDynamicTimeZoneInformationProc();
    if (getDynamic != nullptr) {
        DYNAMIC_TIME_ZONE_INFORMATION current = {};
        if (getDynamic(&current) != TIME_ZONE_ID_INVALID && current.TimeZoneKeyName[0] != L'\0') {
            return current.TimeZoneKeyName;
        }
    }
    HKEY key = nullptr;
    wchar_t keyName[128] = {};
    if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\TimeZoneInformation", 0, KEY_READ, &key) == ERROR_SUCCESS) {
        ReadRegistryString(key, L"TimeZoneKeyName", keyName, ARRAYSIZE(keyName));
        RegCloseKey(key);
    }
    if (keyName[0] != L'\0') {
        return keyName;
    }
    TIME_ZONE_INFORMATION current = {};
    if (GetTimeZoneInformation(&current) != TIME_ZONE_ID_INVALID) {
        for (size_t index = 0; index < zones.size(); index++) {
            if (_wcsicmp(zones[index].StandardName, current.StandardName) == 0) {
                return zones[index].TimeZoneKeyName;
            }
        }
    }
    return zones.empty() ? L"" : zones[0].TimeZoneKeyName;
}

bool ConvertUtcToTimeZone(const DYNAMIC_TIME_ZONE_INFORMATION& zone, const SYSTEMTIME& utc, SYSTEMTIME* local) {
    if (local == nullptr) {
        return false;
    }
    SystemTimeToTzSpecificLocalTimeExProc convertDynamic = GetSystemTimeToTzSpecificLocalTimeExProc();
    if (convertDynamic != nullptr) {
        return convertDynamic(&zone, &utc, local) != FALSE;
    }
    TIME_ZONE_INFORMATION information = {};
    GetTimeZoneInformationForYearProc getForYear = GetGetTimeZoneInformationForYearProc();
    if (getForYear == nullptr || !getForYear(utc.wYear, const_cast<PDYNAMIC_TIME_ZONE_INFORMATION>(&zone), &information)) {
        CopyTimeZoneInformation(zone, &information);
    }
    return SystemTimeToTzSpecificLocalTime(&information, &utc, local) != FALSE;
}
