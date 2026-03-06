#pragma once

#include "core/ecs/component.h"

#include "raylib.h"

#include <unordered_set>

namespace game
{
class InputReceiverComponent : public otb::Component
{
  public:
    otb::ValueStorage serialize() const override;
    static Component* deserialize(const otb::ValueStorage&);

    ~InputReceiverComponent() override = default;

    Vector2 analog_input;
    float rotation_input;

    std::unordered_set<otb::InternedString> extra_actions;

    struct ActionNames
    {
        static const otb::InternedString jump;
    };
};
}