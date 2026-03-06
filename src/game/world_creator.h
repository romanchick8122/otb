#pragma once

#include <memory>

namespace otb
{
class World;
}

namespace game
{
std::unique_ptr<otb::World> create_world();
}