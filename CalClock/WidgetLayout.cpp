#define NOMINMAX
#include "WidgetLayout.h"
#include <algorithm>
#include <climits>

static const int WIDGET_GAP = 10;
static const int WIDGET_GRID_STEP = 16;

static LONG Width(const RECT& rect) {
    return rect.right - rect.left;
}

static LONG Height(const RECT& rect) {
    return rect.bottom - rect.top;
}

static RECT At(const RECT& original, LONG x, LONG y) {
    return { x, y, x + Width(original), y + Height(original) };
}

static LONG CenterX(const RECT& rect) {
    return rect.left + Width(rect) / 2;
}

static LONG CenterY(const RECT& rect) {
    return rect.top + Height(rect) / 2;
}

static LONG AlignUpToGrid(LONG value, LONG origin) {
    LONG remainder = (value - origin) % WIDGET_GRID_STEP;
    if (remainder < 0) {
        remainder += WIDGET_GRID_STEP;
    }
    return remainder == 0 ? value : value + WIDGET_GRID_STEP - remainder;
}

static bool IsSeparated(const RECT& candidate, const std::vector<RECT>& placed, LONG gap) {
    for (const RECT& current : placed) {
        if (candidate.right + gap > current.left && candidate.left < current.right + gap && candidate.bottom + gap > current.top && candidate.top < current.bottom + gap) {
            return false;
        }
    }
    return true;
}

static bool FindNearestGridPlacement(const WidgetPlacement& item, const RECT& work, const std::vector<RECT>& placed,
    LONG gridOriginX, LONG gridOriginY, LONG gap, RECT* placement) {
    LONG minimumCenterX = work.left + Width(item.rect) / 2;
    LONG maximumCenterX = work.right - Width(item.rect) + Width(item.rect) / 2;
    LONG minimumCenterY = work.top + Height(item.rect) / 2;
    LONG maximumCenterY = work.bottom - Height(item.rect) + Height(item.rect) / 2;
    LONG firstCenterX = AlignUpToGrid(minimumCenterX, gridOriginX);
    LONG firstCenterY = AlignUpToGrid(minimumCenterY, gridOriginY);
    bool found = false;
    LONGLONG bestDistance = LLONG_MAX;
    RECT best = {};
    for (LONG centerY = firstCenterY; centerY <= maximumCenterY; centerY += WIDGET_GRID_STEP) {
        for (LONG centerX = firstCenterX; centerX <= maximumCenterX; centerX += WIDGET_GRID_STEP) {
            RECT candidate = At(item.rect, centerX - Width(item.rect) / 2, centerY - Height(item.rect) / 2);
            if (!IsSeparated(candidate, placed, gap)) {
                continue;
            }
            LONGLONG deltaX = static_cast<LONGLONG>(centerX) - CenterX(item.rect);
            LONGLONG deltaY = static_cast<LONGLONG>(centerY) - CenterY(item.rect);
            LONGLONG distance = deltaX * deltaX + deltaY * deltaY;
            if (!found || distance < bestDistance || distance == bestDistance && (candidate.top < best.top || candidate.top == best.top && candidate.left < best.left)) {
                found = true;
                bestDistance = distance;
                best = candidate;
            }
        }
    }
    if (found) {
        *placement = best;
    }
    return found;
}

static bool SnapToGrid(const std::vector<WidgetPlacement>& original, const RECT& work, int anchorId,
    std::vector<WidgetPlacement>* arranged) {
    if (arranged == nullptr || original.empty()) {
        return false;
    }
    std::vector<size_t> order(original.size());
    for (size_t index = 0; index < order.size(); index++) {
        order[index] = index;
    }
    size_t anchorIndex = original.size();
    for (size_t index = 0; index < original.size(); index++) {
        if (original[index].id == anchorId) {
            anchorIndex = index;
            break;
        }
    }
    std::stable_sort(order.begin(), order.end(), [&original](size_t left, size_t right) {
        if (original[left].rect.top != original[right].rect.top) {
            return original[left].rect.top < original[right].rect.top;
        }
        if (original[left].rect.left != original[right].rect.left) {
            return original[left].rect.left < original[right].rect.left;
        }
        return original[left].id < original[right].id;
    });
    if (anchorIndex != original.size()) {
        std::vector<size_t>::iterator anchor = std::find(order.begin(), order.end(), anchorIndex);
        std::rotate(order.begin(), anchor, anchor + 1);
    }
    LONG gridOriginX = anchorIndex == original.size() ? work.left : CenterX(original[anchorIndex].rect);
    LONG gridOriginY = anchorIndex == original.size() ? work.top : CenterY(original[anchorIndex].rect);
    std::vector<WidgetPlacement> result = original;
    std::vector<RECT> placed;
    for (size_t index : order) {
        if (index == anchorIndex) {
            placed.push_back(original[index].rect);
            continue;
        }
        RECT placement = {};
        if (!FindNearestGridPlacement(original[index], work, placed, gridOriginX, gridOriginY, WIDGET_GAP, &placement)) {
            if (!FindNearestGridPlacement(original[index], work, placed, gridOriginX, gridOriginY, 0, &placement)) {
                return false;
            }
        }
        result[index].rect = placement;
        placed.push_back(placement);
    }
    *arranged = std::move(result);
    return true;
}

bool ArrangeWidgetPlacements(std::vector<WidgetPlacement>* items, const RECT& work, int anchorId) {
    if (items == nullptr) {
        return false;
    }
    if (items->empty()) {
        return true;
    }
    for (size_t index = 0; index < items->size(); index++) {
        const WidgetPlacement& item = (*items)[index];
        if (Width(item.rect) <= 0 || Height(item.rect) <= 0 || Width(item.rect) > Width(work) || Height(item.rect) > Height(work)) {
            return false;
        }
    }
    std::vector<WidgetPlacement> arranged;
    if (!SnapToGrid(*items, work, anchorId, &arranged)) {
        return false;
    }
    *items = std::move(arranged);
    return true;
}

POINT SnapWidgetPositionToWorkArea(const RECT& widgetRect, const RECT& work, POINT position, int snapDistance) {
    POINT result = position;
    LONG width = Width(widgetRect);
    LONG height = Height(widgetRect);
    if (result.x >= work.left - snapDistance && result.x <= work.left + snapDistance) {
        result.x = work.left;
    } else if (result.x + width >= work.right - snapDistance && result.x + width <= work.right + snapDistance) {
        result.x = work.right - width;
    }
    if (result.y >= work.top - snapDistance && result.y <= work.top + snapDistance) {
        result.y = work.top;
    } else if (result.y + height >= work.bottom - snapDistance && result.y + height <= work.bottom + snapDistance) {
        result.y = work.bottom - height;
    }
    return result;
}

POINT PreserveWidgetWorkAreaAttachment(const RECT& widgetRect, const RECT& work, int newWidth, int newHeight, int snapDistance,
    bool* horizontalAttachment, bool* verticalAttachment) {
    bool left = widgetRect.left >= work.left - snapDistance && widgetRect.left <= work.left + snapDistance;
    bool right = widgetRect.right >= work.right - snapDistance && widgetRect.right <= work.right + snapDistance;
    bool top = widgetRect.top >= work.top - snapDistance && widgetRect.top <= work.top + snapDistance;
    bool bottom = widgetRect.bottom >= work.bottom - snapDistance && widgetRect.bottom <= work.bottom + snapDistance;
    if (horizontalAttachment != nullptr) {
        *horizontalAttachment = left || right;
    }
    if (verticalAttachment != nullptr) {
        *verticalAttachment = top || bottom;
    }
    POINT position = { widgetRect.left, widgetRect.top };
    if (left) {
        position.x = work.left;
    } else if (right) {
        position.x = work.right - newWidth;
    }
    if (top) {
        position.y = work.top;
    } else if (bottom) {
        position.y = work.bottom - newHeight;
    }
    return position;
}
