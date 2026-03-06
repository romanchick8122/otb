#pragma once

namespace otb
{
class World;

struct RenderControlSystem
{
    static void render_begin(World*, float);
    static void render_end(World*, float);
};
}