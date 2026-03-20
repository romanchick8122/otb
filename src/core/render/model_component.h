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
    void set_forced_material_index(size_t);
    InternedString get_playing_animation() const;

  private:
    Asset<ModelAsset> asset;
    Transform model_space_collider;

    float animation_speed = 0;

    const ModelAsset::AnimationGraph::Transition* playing_transition = nullptr;
    float transition_time = 0;

    size_t playing_animation_index = std::string::npos;
    float animation_time = 0;
    bool looping_requested = false;

    size_t request_animation_index = std::string::npos;

    size_t forced_material_index = std::string::npos;

    friend class MeshSystem;
};
}