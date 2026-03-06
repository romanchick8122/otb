#pragma once

#include "core/ecs/component.h"

#include "raylib.h"

namespace otb
{
class ModelComponent : public Component
{
  public:
    ModelComponent(const char* file_path);

    ~ModelComponent() override;

  private:
    Model model;

    friend class MeshSystem;
};
}