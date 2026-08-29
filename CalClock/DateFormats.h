#pragma once

#include "CalClockTypes.h"

std::wstring FormatWidgetDate(const WidgetConfig& config, const SYSTEMTIME& date, int formatIndex);
std::wstring DateFormatCaption(const WidgetConfig& config, const SYSTEMTIME& date, int formatIndex);
bool DateFormatStartsGroup(int formatIndex);
