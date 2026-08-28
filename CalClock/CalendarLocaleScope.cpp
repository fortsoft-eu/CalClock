#include "CalendarLocaleScope.h"

thread_local LCID activeCalendarLocale = 0;

CalendarLocaleScope::CalendarLocaleScope(const wchar_t* localeName) {
    previousOverride = activeCalendarLocale;
    previousLocale = GetThreadLocale();
    previousUiLanguage = GetThreadUILanguage();
    activeCalendarLocale = LocaleNameToLCID(localeName, 0);
    if (activeCalendarLocale != 0) {
        SetThreadLocale(activeCalendarLocale);
        SetThreadUILanguage(LANGIDFROMLCID(activeCalendarLocale));
    }
}

CalendarLocaleScope::~CalendarLocaleScope() {
    SetThreadUILanguage(previousUiLanguage);
    SetThreadLocale(previousLocale);
    activeCalendarLocale = previousOverride;
}
