#include "render_control_system.h"

#include "core/assert.h"
#include "core/ecs/entity.h"
#include "core/ecs/world.h"
#include "core/render/camera_component.h"

#include "raylib.h"

namespace otb
{
void RenderControlSystem::render_begin(World* world, float)
{
    BeginDrawing();
    ClearBackground(BLACK);

    CameraComponent* camera = world->get_world_entity()->get_component<CameraComponent>();
    OTB_ASSERT(camera != nullptr);

    BeginMode3D(camera->camera);
}

void RenderControlSystem::render_end(World*, float)
{
    EndMode3D();
    EndDrawing();
}
}