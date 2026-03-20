#pragma once

#include "core/ecs/component.h"
#include "core/render/texture_asset.h"

namespace game
{
class MenuLayerComponent : public otb::Component
{
  public:
    otb::ValueStorage serialize() const override;
    static otb::Component* deserialize(const otb::ValueStorage&);

    ~MenuLayerComponent() override = default;

    Rectangle get_screen_space_rect() const;

    otb::Asset<otb::TextureAsset> texture;
    size_t z_order = 0;

    Vector2 position;
    float target_height = 0;

    Vector2 texture_size_override;
};
}