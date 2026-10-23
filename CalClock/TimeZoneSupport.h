/**
 * This is open-source software licensed under the terms of the MIT License.
 *
 * Copyright (c) 2026 Petr Červinka - FortSoft <cervinka@fortsoft.eu>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 **
 * Last modified for version 1.6.1.1
 */

#pragma once

#include <windows.h>
#include <string>
#include <vector>

extern const wchar_t SYSTEM_TIME_ZONE_KEY[];

/// Rebuilds the zone list with current Windows settings first, followed by sorted named zones and fixed UTC offsets.
void LoadTimeZoneList(std::vector<DYNAMIC_TIME_ZONE_INFORMATION>* zones);

/// Prefixes a named zone with its UTC offset at the supplied instant, including applicable daylight saving time.
/// Returns only the normalized offset for fixed-offset, unnamed, or current-Windows-settings zones.
std::wstring TimeZoneDisplayName(const DYNAMIC_TIME_ZONE_INFORMATION& zone, const SYSTEMTIME& utc);

/// Finds the current Windows time-zone key using available APIs, the registry, or a standard-name match.
/// Falls back to the first listed explicit zone, or an empty string when none is available.
std::wstring GetSystemTimeZoneKey(const std::vector<DYNAMIC_TIME_ZONE_INFORMATION>& zones);

/// Converts UTC using current Windows settings, fixed offsets, or dynamic or yearly rules for named zones.
/// Returns false if the destination is null or Windows cannot perform the conversion.
bool ConvertUtcToTimeZone(const DYNAMIC_TIME_ZONE_INFORMATION& zone, const SYSTEMTIME& utc, SYSTEMTIME* local);
