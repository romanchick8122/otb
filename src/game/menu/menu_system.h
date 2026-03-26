#pragma once

namespace otb
{
class World;
}

namespace game
{
struct MenuSystem
{
static void init(otb::World*);

static void reset_curstor(otb::World*);
static void collect_events(otb::World*);
static void subworld_update_fixed(otb::World*);
static void collect_subworld_events(otb::World*);
static void process_events(otb::World*);

static void render_menu(otb::World*, float);
static void subworld_update(otb::World*, float);
};
}