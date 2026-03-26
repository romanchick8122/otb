#pragma once

namespace otb
{
class World;
}

namespace game
{
struct CharacterSystem
{
    static void update_camera(otb::World*, float);
    static void update_camera_fixed(otb::World*);
    static void update_state(otb::World*);
};
}