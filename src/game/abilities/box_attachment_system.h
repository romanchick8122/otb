#pragma once

namespace otb
{
class World;
}

namespace game
{
struct BoxAttachmentSystem
{
    static void process_ability_activation(otb::World*);
    static void process_ability(otb::World*);
    static void debug_draw(otb::World*, float);
};
}