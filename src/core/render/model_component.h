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

  private:
    Asset<ModelAsset> asset;

    friend class MeshSystem;
};
}