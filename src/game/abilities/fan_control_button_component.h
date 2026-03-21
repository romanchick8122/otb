#pragma once

#include "core/ecs/component.h"

namespace game
{
class FanControlButtonComponent final : public otb::Component
{
  public:
    FanControlButtonComponent(otb::InternedString, bool);

    otb::ValueStorage serialize() const override;
    static otb::Component* deserialize(const otb::ValueStorage&);

    ~FanControlButtonComponent() override = default;

    otb::InternedString target_entity;
    std::vector<otb::InternedString> animated_entities_names;
    std::vector<otb::Entity*> animated_entities;
    bool enabled = false;

    bool prev_frame_pressed = false;
};
}