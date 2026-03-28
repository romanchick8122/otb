#include "core/ecs/world.h"

#include "core/static_initialize.h"

#include "game/static_initialize.h"
#include "game/world_creator.h"

#include "sound/sound_engine.h"

#include <raylib.h>

#include <array>

#ifndef _DEBUG
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

int main()
{
    using namespace otb;

    otb::run_static_initializer();
    game::run_static_initializer();

    static constexpr std::array<int, 2> DEFAULT_WINDOW_SIZE{800, 600};

    SoundEngine* sound_engine = SoundEngine::instance();
    sound_engine->load_bank("main.bnk");

    SetConfigFlags(FLAG_VSYNC_HINT);
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(DEFAULT_WINDOW_SIZE[0], DEFAULT_WINDOW_SIZE[1], "otb");
    SetTargetFPS(60);

    #if !defined(OTB_DEBUG)
        ToggleBorderlessWindowed();
    #endif

    std::unique_ptr<World> world = game::create_menu_world();

    while (!WindowShouldClose())
    {
        #if defined(OTB_DEBUG)
            if (IsKeyPressed(KEY_ENTER) && (IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT)))
            {
                ToggleBorderlessWindowed();
            }
        #endif
        world->update();
        sound_engine->update();
    }
    CloseWindow();

    return 0;
}