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
    Vector2 secondary_analog_input;

    struct ActionQueue {
        std::vector<std::pair<otb::InternedString, float>> delays;
        void request(otb::InternedString action, float delay);
    } action_queue;
    std::unordered_set<otb::InternedString> extra_actions;

    struct ActionNames
    {
        static const otb::InternedString ability;
        static const otb::InternedString aim;
        static const otb::InternedString jump;
    };
};
}