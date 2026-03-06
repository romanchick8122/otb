#include "core/ecs/world.h"

#include "core/static_initialize.h"

#include "game/world_creator.h"

#include "raylib.h"

int main()
{
    using namespace otb;

    otb::run_static_initializer();

    InitWindow(2000, 1000, "otb");
    SetTargetFPS(60);

    std::unique_ptr<World> world = game::create_world();
    world->fixed_frame_time = 1 / 60.f;
    world->max_fixed_frames = 2;

    int frame = 0;

    while (!WindowShouldClose())
    {
        world->update();
        frame++;

        if (frame == 100)
        {
            world->serialize().save({ OTB_ASSETS_DIRECTORY"/world.vs" });
        }
    }
    CloseWindow();

    return 0;
}