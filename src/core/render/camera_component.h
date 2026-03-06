#pragma once

#include "core/ecs/component.h"

#include "raylib.h"

namespace otb
{
class CameraComponent : public Component
{
  public:
    CameraComponent();

    ~CameraComponent() override = default;
  private:
    Camera camera { 0 };

    friend class RenderControlSystem;
};
}