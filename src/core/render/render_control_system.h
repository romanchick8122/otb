#pragma once

namespace otb
{
class World;

struct RenderControlSystem
{
    static void render_begin(World*, float);
    static void render_stop_3d_start_2d(World*, float);
    static void render_end(World*, float);
};
}