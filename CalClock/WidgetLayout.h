#pragma once

#include <windows.h>
#include <vector>

struct WidgetPlacement {
    int id = 0;
    RECT rect = {};
};

bool ArrangeWidgetPlacements(std::vector<WidgetPlacement>* items, const RECT& work, int anchorId = -1);
POINT SnapWidgetPositionToWorkArea(const RECT& widgetRect, const RECT& work, POINT position, int snapDistance);
POINT PreserveWidgetWorkAreaAttachment(const RECT& widgetRect, const RECT& work, int newWidth, int newHeight, int snapDistance, bool* horizontalAttachment = nullptr, bool* verticalAttachment = nullptr);
