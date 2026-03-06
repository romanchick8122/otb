#pragma once

namespace otb
{
class World;
}

namespace game
{
struct InputSystem
{
    static void collect_input_kb_mouse(otb::World*);

    static void apply_input(otb::World*);
};
}