#include "core/ecs/world.h"

#include "game/world_creator.h"

#include "raylib.h"

#include <chrono>

int main()
{
    using namespace otb;

    InitWindow(2000, 1000, "otb");
    SetTargetFPS(60);

    std::unique_ptr<World> world = game::create_world();

    std::chrono::high_resolution_clock clock;

    static const float target_fixed_frame_time = 1 / 30.f;
    static const uint32_t max_fixed_frames = 2;

    auto prev_time = clock.now();

    float accumulated_time = 0.0f;

    while (!WindowShouldClose())
    {
        const float frame_time = [&prev_time, &clock] {
            const auto current_time = clock.now();
            const auto time_delta = current_time - prev_time;
            prev_time = current_time;
            return std::chrono::nanoseconds(time_delta).count() / 1e9f;
        }();

        accumulated_time += frame_time;
        for (uint32_t i = 0; accumulated_time > 0.f && i < max_fixed_frames; ++i)
        {
            world->fixed_update();
            accumulated_time -= target_fixed_frame_time;
        }
        world->normal_update(frame_time);
    }
    CloseWindow();

    return 0;
}