#pragma once

#include "core/ecs/component.h"

#include <raylib.h>

namespace otb
{
class VelocityComponent : public otb::Component
{
  public:
    Vector3 velocity;
    bool apply_gravity = false;
};
}