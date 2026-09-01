#pragma once

#include <windows.h>
#include <vector>

struct WidgetPlacement {
    int id = 0;
    RECT rect = {};
};

bool ArrangeWidgetPlacements(std::vector<WidgetPlacement>* items, const RECT& work, int anchorId = -1);
