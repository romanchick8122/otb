#pragma once

namespace otb
{
class World;
}

namespace game
{
struct SurfaceSystem
{
    static void create_surface_colliders(otb::World*);
    static void reattach_characters(otb::World*);
    static void debug_draw(otb::World*, float);
};
}