#include "world_creator.h"

#include "core/ecs/world.h"

#include "core/render/camera_component.h"
#include "core/render/mesh_system.h"
#include "core/render/model_component.h"
#include "core/render/render_control_system.h"

#include "raylib.h"

namespace game
{
std::unique_ptr<otb::World> create_world()
{
    using namespace otb;

    World* world = new World();

    world->get_world_entity()->add_component(new CameraComponent());
    world->add_entity()->add_component(new ModelComponent(OTB_ASSETS_DIRECTORY"/cube.glb"));

    world->add_normal_system(RenderControlSystem::render_begin);
    world->add_normal_system(MeshSystem::render_meshes);
    world->add_normal_system(RenderControlSystem::render_end);

    return std::unique_ptr<World>(world);
}
}