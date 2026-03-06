#pragma once

#include "raylib.h"

namespace otb
{
class TransformUtils
{
  public:
    static Matrix get_transform_matrix(const Transform&);
};
}