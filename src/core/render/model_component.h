#pragma once

#include "core/ecs/component.h"
#include "core/interned_string.h"
#include "core/render/model_asset.h"

#include "raylib.h"

namespace otb
{
class ModelComponent : public Component
{
  public:
    ModelComponent(InternedString asset_path);

    ValueStorage serialize() const override;
    static Component* deserialize(const ValueStorage&);

    void request_animation(InternedString, bool);
    void set_animation_speed(float);

  private:
    Asset<ModelAsset> asset;
    Transform model_space_collider;

    float animation_speed = 0;

    size_t requested_animation_index = std::string::npos;
    float animation_time = 0;
    bool looping_requested = false;

    friend class MeshSystem;
};
}