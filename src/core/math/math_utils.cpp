#include "math_utils.h"

#include <raymath.h>

#include <compare>
#include <utility>

namespace otb
{
bool MathUtils::is_inside_ranges(const Vector2& inner, const Vector2& outer)
{
    return inner.x >= outer.x && inner.y <= outer.y;
}

bool MathUtils::has_intersection_ranges(const Vector2& l, const Vector2& r)
{
    if (is_inside_ranges(l, r) || is_inside_ranges(r, l))
    {
        return true;
    }
    if (l.x < r.x)
        return l.y >= r.x;
    return r.y >= l.x;
}

bool MathUtils::is_point_inside_range(const Vector2& range, float p)
{
    return p > range.x && p < range.y;
}

bool MathUtils::is_point_inside_range_safe(Vector2 range, float p)
{
    if (range.x > range.y)
        std::swap(range.x, range.y);
    return MathUtils::is_point_inside_range(range, p);
}

Quaternion MathUtils::get_rotation_from_to(Vector3 from, Vector3 to)
{
    if (Vector3Equals(from * -1.f, to)) [[unlikely]]
    {
        return QuaternionFromAxisAngle({0, 1, 0}, PI);
    }
    return QuaternionFromVector3ToVector3(from, to);
}
}