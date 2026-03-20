#pragma once

#include "core/interned_string.h"

#include <memory>

namespace otb
{
class World;
}

namespace game
{
std::unique_ptr<otb::World> create_world(otb::InternedString);
std::unique_ptr<otb::World> create_menu_world();
}