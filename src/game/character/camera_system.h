#pragma once

namespace otb
{
class World;
}

namespace game
{
struct CameraSystem
{
    static void character_follow_camera(otb::World*, float);
};
}