#pragma once

namespace otb
{
class World;
}

namespace game
{
struct HudSystem
{
    static void render_hud(otb::World*, float);
}; 
}
