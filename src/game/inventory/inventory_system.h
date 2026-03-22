#pragma once

namespace otb
{
class World;
}

namespace game
{
struct InventorySystem
{
    static void init(otb::World*);
    static void process_item_pickup(otb::World*);
    static void process_hud(otb::World*);
};
}