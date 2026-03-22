#include "ui_utils.h"

#include <raymath.h>

namespace otb
{
Vector2 UIUtils::get_screen_size()
{
    return Vector2{static_cast<float>(GetRenderWidth()), static_cast<float>(GetRenderHeight())};
}

Vector2 UIUtils::normalized_to_screen(const Vector2 v)
{
    return (v + Vector2{1.f, 1.f}) / 2.f * get_screen_size();
}

Rectangle UIUtils::normalized_to_screen(const Rectangle& rect)
{
    const Vector2 norm_min { rect.x, rect.y };
    const Vector2 norm_max = norm_min + Vector2{ rect.width, rect.height };
    const Vector2 screen_min = normalized_to_screen(norm_min);
    const Vector2 screen_max = normalized_to_screen(norm_max);
    return rect_from_min_max(screen_min, screen_max);
}

Rectangle UIUtils::rect_from_min_max(const Vector2 min, const Vector2 max)
{
    const Vector2 size = max - min;
    return Rectangle {
        .x = min.x,
        .y = min.y,
        .width = size.x,
        .height = size.y,
    };
}

float UIUtils::get_norm_target_width(const Vector2 reference, const float target_height)
{
    const Vector2 screen_size = get_screen_size();
    return target_height * screen_size.y / screen_size.x * reference.x / reference.y;
}

Rectangle UIUtils::get_texture_rect(const Texture2D& texture)
{
    return {
        .x = 0,
        .y = 0,
        .width = static_cast<float>(texture.width),
        .height = static_cast<float>(texture.height),
    };
}
}