#pragma once

#include "core/ecs/component.h"

namespace game
{
class MenuButtonComponent : public otb::Component
{
  public:
    MenuButtonComponent(otb::InternedString);

    otb::ValueStorage serialize() const override;
    static otb::Component* deserialize(const otb::ValueStorage&);

    ~MenuButtonComponent() override = default;

    otb::InternedString on_click;
};
}