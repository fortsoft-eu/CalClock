#pragma once

#include <windows.h>
#include <string>
#include <vector>

void LoadTimeZoneList(std::vector<DYNAMIC_TIME_ZONE_INFORMATION>* zones);
std::wstring GetSystemTimeZoneKey(const std::vector<DYNAMIC_TIME_ZONE_INFORMATION>& zones);
bool ConvertUtcToTimeZone(const DYNAMIC_TIME_ZONE_INFORMATION& zone, const SYSTEMTIME& utc, SYSTEMTIME* local);
