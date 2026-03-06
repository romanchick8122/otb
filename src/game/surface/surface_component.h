#pragma once

#include "core/ecs/component.h"

#include "game/surface/surface_asset.h"

namespace game
{
class SurfaceComponent : public otb::Component
{
  public:
    otb::ValueStorage serialize() const;
    static Component* deserialize(const otb::ValueStorage&);

  private:
    otb::Asset<SurfaceAsset> asset;

    friend class SurfaceSystem;
};
}