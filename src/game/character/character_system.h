#pragma once

namespace otb
{
class World;
}

namespace game
{
struct CharacterSystem
{
    static void character_follow_camera(otb::World*, float);
};
}