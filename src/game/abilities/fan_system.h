#pragma once

namespace otb
{
class World;
}

namespace game
{
struct FanSystem
{
    static void apply_velocity(otb::World*);
};
}