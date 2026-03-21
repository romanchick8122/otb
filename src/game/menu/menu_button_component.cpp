#include "menu_button_component.h"

namespace game
{
MenuButtonComponent::MenuButtonComponent(otb::InternedString v)
    : on_click(v)
{
}

otb::ValueStorage MenuButtonComponent::serialize() const
{
    return std::string(on_click.c_str());
}

otb::Component* MenuButtonComponent::deserialize(const otb::ValueStorage& vs)
{
    return new MenuButtonComponent(otb::InternedString(std::get<std::string>(vs.storage).c_str()));
}
}