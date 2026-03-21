#pragma once

#include <raylib.h>

namespace otb
{
struct MathUtils
{
    static bool is_inside_ranges(const Vector2&, const Vector2&);
    static bool has_intersection_ranges(const Vector2&, const Vector2&);
    static bool is_point_inside_range(const Vector2&, float);
    static bool is_point_inside_range_safe(Vector2, float);
};
}