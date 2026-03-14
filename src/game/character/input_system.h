#pragma once

namespace otb
{
class World;
}

namespace game
{
struct InputSystem
{
    static void clear_input(otb::World*);
    static void collect_input_kb_mouse(otb::World*);
    static void update_action_queue(otb::World*);
    static void apply_input(otb::World*);
};
}