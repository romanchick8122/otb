#pragma once

#include "raylib.h"

namespace otb
{
class TransformUtils
{
  public:
    static Matrix get_transform_matrix(const Transform&);
    static Vector3 apply_transform(const Transform&, const Vector3&);
    static Vector3 apply_inverse_transform(const Transform&, const Vector3&);

    static BoundingBox get_box(const Transform&);
};
}