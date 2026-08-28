#pragma once

#include <windows.h>

extern thread_local LCID activeCalendarLocale;

class CalendarLocaleScope {
public:
    explicit CalendarLocaleScope(const wchar_t* localeName);
    ~CalendarLocaleScope();

private:
    LCID previousOverride;
    LCID previousLocale;
    LANGID previousUiLanguage;
};
