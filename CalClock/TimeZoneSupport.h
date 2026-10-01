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
 * Last modified for version 1.5.1.0
 */

#pragma once

#include <windows.h>
#include <string>
#include <vector>

/// Rebuilds the zone list from Windows APIs or the registry, adds fixed UTC offsets, and sorts the result.
void LoadTimeZoneList(std::vector<DYNAMIC_TIME_ZONE_INFORMATION>* zones);

/// Prefixes a named zone with its UTC offset at the supplied instant, including applicable daylight saving time.
/// Returns only the normalized offset for fixed-offset or unnamed zones.
std::wstring TimeZoneDisplayName(const DYNAMIC_TIME_ZONE_INFORMATION& zone, const SYSTEMTIME& utc);

/// Finds the current Windows time-zone key using available APIs, the registry, or a standard-name match.
/// Falls back to the first listed zone, or an empty string when the list is empty.
std::wstring GetSystemTimeZoneKey(const std::vector<DYNAMIC_TIME_ZONE_INFORMATION>& zones);

/// Converts UTC to the selected zone, using fixed offsets directly and dynamic or yearly rules for named zones.
/// Returns false if the destination is null or Windows cannot perform the conversion.
bool ConvertUtcToTimeZone(const DYNAMIC_TIME_ZONE_INFORMATION& zone, const SYSTEMTIME& utc, SYSTEMTIME* local);
