#include "core/ecs/world.h"

#include "core/static_initialize.h"

#include "game/static_initialize.h"
#include "game/world_creator.h"

#include "raylib.h"

#include <array>

int main()
{
    using namespace otb;

    otb::run_static_initializer();
    game::run_static_initializer();

    static constexpr std::array<int, 2> DEFAULT_WINDOW_SIZE{800, 600};

    InitWindow(DEFAULT_WINDOW_SIZE[0], DEFAULT_WINDOW_SIZE[1], "otb");
    SetTargetFPS(60);

    std::unique_ptr<World> world = game::create_world();
    world->fixed_frame_time = 1 / 60.f;
    world->max_fixed_frames = 2;

    while (!WindowShouldClose())
    {
 		if (IsKeyPressed(KEY_ENTER) && (IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT)))
 		{
            ToggleBorderlessWindowed();
 		}

        world->update();
    }
    CloseWindow();

    return 0;
}