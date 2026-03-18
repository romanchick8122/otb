#pragma once

#include "core/ecs/component.h"

namespace game
{
struct BoxComponent : public otb::Component
{
  public:
    otb::ValueStorage serialize() const override;
    static otb::Component* deserialize(const otb::ValueStorage&);

    enum class BoxType {
        STATIC,
        DYNAMIC,
    } type;
    
    ~BoxComponent() override = default;

    // Runtime
    BoxComponent* rests_on;
};
}