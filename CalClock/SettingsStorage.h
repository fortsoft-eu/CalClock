#pragma once

#include "CalClockTypes.h"

using WidgetDefaultsFactory = WidgetConfig(*)(WidgetType type, int index, AppLanguage language, int fontAntialiasing);

std::wstring AutomaticXmlSettingsPath(bool createDirectory);
void RemoveAutomaticXmlSettings();
void RemoveRegistrySettings();
bool WriteSettingsXml(const std::wstring& path, const SettingsSnapshot& snapshot);
bool ReadSettingsXml(const std::wstring& path, AppLanguage defaultLanguage, WidgetDefaultsFactory createDefaults, SettingsSnapshot* snapshot);
bool ReadRegistrySettings(const SettingsSnapshot& defaults, WidgetDefaultsFactory createDefaults, SettingsSnapshot* snapshot);
bool WriteRegistrySettings(const SettingsSnapshot& snapshot);
