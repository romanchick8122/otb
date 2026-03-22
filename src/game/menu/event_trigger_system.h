#pragma once

namespace otb
{
class World;
}

namespace game
{
struct EventTriggerSystem
{
static void fixed_update(otb::World*);
};
}