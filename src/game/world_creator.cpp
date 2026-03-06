#include "world_creator.h"

#include "core/ecs/world.h"
#include "core/render/camera_component.h"
#include "core/render/mesh_system.h"
#include "core/render/model_component.h"
#include "core/render/render_control_system.h"
#include "core/world/transform_component.h"

#include "game/character/camera_system.h"
#include "game/character/input_system.h"

namespace game
{
std::unique_ptr<otb::World> create_world()
{
    using namespace otb;

    World* world = new World();
    ValueStorage vs;
    vs.load(OTB_ASSETS_DIRECTORY"/world.vs");
    world->deserialize(vs);

    world->add_fixed_system(InputSystem::collect_input_kb_mouse);
    world->add_fixed_system(InputSystem::apply_input);

    world->add_normal_system(CameraSystem::character_follow_camera);
    world->add_normal_system(RenderControlSystem::render_begin);
    world->add_normal_system(MeshSystem::render_meshes);
    world->add_normal_system(RenderControlSystem::render_end);

    return std::unique_ptr<World>(world);
}
}