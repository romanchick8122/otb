#pragma once

namespace otb
{
class World;
}

namespace game
{
struct FanSystem
{
    static void init(otb::World*);
    static void update_controllers(otb::World*);
    static void update_fan_visibility(otb::World*);
    static void apply_velocity(otb::World*);
};
}