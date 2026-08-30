#include "DateFormats.h"
#include "Localization.h"
#include <algorithm>

enum DateFormatGroup {
    DATE_FORMAT_GROUP_LOCAL,
    DATE_FORMAT_GROUP_SORTABLE,
    DATE_FORMAT_GROUP_DAY_FIRST,
    DATE_FORMAT_GROUP_MONTH_FIRST,
    DATE_FORMAT_GROUP_TEXT,
    DATE_FORMAT_GROUP_WEEKDAY
};

struct DateFormatDefinition {
    const wchar_t* caption;
    const wchar_t* pattern;
    DWORD flags;
    DateFormatGroup group;
};

const DateFormatDefinition DATE_FORMAT_DEFINITIONS[DATE_FORMAT_COUNT] = {
    {
        nullptr,
        nullptr,
        DATE_SHORTDATE,
        DATE_FORMAT_GROUP_LOCAL
    },
    {
        nullptr,
        nullptr,
        DATE_LONGDATE,
        DATE_FORMAT_GROUP_LOCAL
    },
    {
        L"yyyy-MM-dd",
        L"yyyy'-'MM'-'dd",
        0,
        DATE_FORMAT_GROUP_SORTABLE
    },
    {
        L"yyyyMMdd",
        L"yyyyMMdd",
        0,
        DATE_FORMAT_GROUP_SORTABLE
    },
    {
        L"yy-MM-dd",
        L"yy'-'MM'-'dd",
        0,
        DATE_FORMAT_GROUP_SORTABLE
    },
    {
        L"yyMMdd",
        L"yyMMdd",
        0,
        DATE_FORMAT_GROUP_SORTABLE
    },
    {
        L"yyyy/MM/dd",
        L"yyyy'/'MM'/'dd",
        0,
        DATE_FORMAT_GROUP_SORTABLE
    },
    {
        L"yyyy.MM.dd",
        L"yyyy'.'MM'.'dd",
        0,
        DATE_FORMAT_GROUP_SORTABLE
    },
    {
        L"d.M.yyyy",
        L"d'.'M'.'yyyy",
        0,
        DATE_FORMAT_GROUP_DAY_FIRST
    },
    {
        L"dd.MM.yyyy",
        L"dd'.'MM'.'yyyy",
        0,
        DATE_FORMAT_GROUP_DAY_FIRST
    },
    {
        L"d.M.yy",
        L"d'.'M'.'yy",
        0,
        DATE_FORMAT_GROUP_DAY_FIRST
    },
    {
        L"dd.MM.yy",
        L"dd'.'MM'.'yy",
        0,
        DATE_FORMAT_GROUP_DAY_FIRST
    },
    {
        L"d/M/yyyy",
        L"d'/'M'/'yyyy",
        0,
        DATE_FORMAT_GROUP_DAY_FIRST
    },
    {
        L"dd/MM/yyyy",
        L"dd'/'MM'/'yyyy",
        0,
        DATE_FORMAT_GROUP_DAY_FIRST
    },
    {
        L"dd/MM/yy",
        L"dd'/'MM'/'yy",
        0,
        DATE_FORMAT_GROUP_DAY_FIRST
    },
    {
        L"d-M-yyyy",
        L"d'-'M'-'yyyy",
        0,
        DATE_FORMAT_GROUP_DAY_FIRST
    },
    {
        L"dd-MM-yyyy",
        L"dd'-'MM'-'yyyy",
        0,
        DATE_FORMAT_GROUP_DAY_FIRST
    },
    {
        L"M/d/yyyy",
        L"M'/'d'/'yyyy",
        0,
        DATE_FORMAT_GROUP_MONTH_FIRST
    },
    {
        L"MM/dd/yyyy",
        L"MM'/'dd'/'yyyy",
        0,
        DATE_FORMAT_GROUP_MONTH_FIRST
    },
    {
        L"MM/dd/yy",
        L"MM'/'dd'/'yy",
        0,
        DATE_FORMAT_GROUP_MONTH_FIRST
    },
    {
        L"M-d-yyyy",
        L"M'-'d'-'yyyy",
        0,
        DATE_FORMAT_GROUP_MONTH_FIRST
    },
    {
        L"MM-dd-yyyy",
        L"MM'-'dd'-'yyyy",
        0,
        DATE_FORMAT_GROUP_MONTH_FIRST
    },
    {
        L"d MMM yyyy",
        L"d MMM yyyy",
        0,
        DATE_FORMAT_GROUP_TEXT
    },
    {
        L"d MMMM yyyy",
        L"d MMMM yyyy",
        0,
        DATE_FORMAT_GROUP_TEXT
    },
    {
        L"MMM d, yyyy",
        L"MMM d',' yyyy",
        0,
        DATE_FORMAT_GROUP_TEXT
    },
    {
        L"MMMM d, yyyy",
        L"MMMM d',' yyyy",
        0,
        DATE_FORMAT_GROUP_TEXT
    },
    {
        L"ddd, d MMM yyyy",
        L"ddd',' d MMM yyyy",
        0,
        DATE_FORMAT_GROUP_WEEKDAY
    },
    {
        L"dddd d MMMM yyyy",
        L"dddd d MMMM yyyy",
        0,
        DATE_FORMAT_GROUP_WEEKDAY
    },
    {
        L"ddd, MMM d, yyyy",
        L"ddd',' MMM d',' yyyy",
        0,
        DATE_FORMAT_GROUP_WEEKDAY
    },
    {
        L"dddd, MMMM d, yyyy",
        L"dddd',' MMMM d',' yyyy",
        0,
        DATE_FORMAT_GROUP_WEEKDAY
    },
    {
        L"ddd, dd MMM yyyy",
        L"ddd',' dd MMM yyyy",
        0,
        DATE_FORMAT_GROUP_WEEKDAY
    },
    {
        L"ddd d.M.yyyy",
        L"ddd d'.'M'.'yyyy",
        0,
        DATE_FORMAT_GROUP_WEEKDAY
    },
    {
        L"dddd d.M.yyyy",
        L"dddd d'.'M'.'yyyy",
        0,
        DATE_FORMAT_GROUP_WEEKDAY
    }
};
static_assert(ARRAYSIZE(DATE_FORMAT_DEFINITIONS) == DATE_FORMAT_COUNT);

std::wstring FormatWidgetDate(const WidgetConfig& config, const SYSTEMTIME& date, int formatIndex) {
    int selected = std::clamp(formatIndex, 0, DATE_FORMAT_COUNT - 1);
    const DateFormatDefinition& definition = DATE_FORMAT_DEFINITIONS[selected];
    wchar_t text[160] = {};
    int length = GetDateFormatEx(LANGUAGE_LOCALES[config.language], definition.flags, &date, definition.pattern, text, ARRAYSIZE(text), nullptr);
    if (length == 0) {
        swprintf_s(text, L"%04d-%02d-%02d", date.wYear, date.wMonth, date.wDay);
    }
    return text;
}

static std::wstring GetLocaleDatePattern(const WidgetConfig& config, int formatIndex) {
    LCTYPE type = formatIndex == DATE_LOCAL_LONG ? LOCALE_SLONGDATE : LOCALE_SSHORTDATE;
    wchar_t pattern[160] = {};
    if (GetLocaleInfoEx(LANGUAGE_LOCALES[config.language], type, pattern, ARRAYSIZE(pattern)) == 0) {
        return formatIndex == DATE_LOCAL_LONG ? LOCAL_LONG_LABELS[config.language] : LOCAL_SHORT_LABELS[config.language];
    }
    return pattern;
}

std::wstring DateFormatCaption(const WidgetConfig& config, const SYSTEMTIME& date, int formatIndex) {
    int selected = std::clamp(formatIndex, 0, DATE_FORMAT_COUNT - 1);
    const DateFormatDefinition& definition = DATE_FORMAT_DEFINITIONS[selected];
    std::wstring name = definition.caption == nullptr ? GetLocaleDatePattern(config, selected) : definition.caption;
    if (selected == DATE_LOCAL_SHORT || selected == DATE_LOCAL_LONG) {
        name += L" (";
        name += selected == DATE_LOCAL_SHORT ? LOCAL_SHORT_LABELS[config.language] : LOCAL_LONG_LABELS[config.language];
        name += L")";
    }
    return name + L"  —  " + FormatWidgetDate(config, date, selected);
}

bool DateFormatStartsGroup(int formatIndex) {
    if (formatIndex <= 0 || formatIndex >= DATE_FORMAT_COUNT) {
        return false;
    }
    return DATE_FORMAT_DEFINITIONS[formatIndex].group != DATE_FORMAT_DEFINITIONS[formatIndex - 1].group;
}
