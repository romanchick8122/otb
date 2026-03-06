#include "world_creator.h"

#include "core/ecs/world.h"
#include "core/render/camera_component.h"
#include "core/render/mesh_system.h"
#include "core/render/model_component.h"
#include "core/render/render_control_system.h"
#include "core/world/transform_component.h"

#include "raylib.h"
#include "raymath.h"

namespace game
{
std::unique_ptr<otb::World> create_world()
{
    using namespace otb;

    World* world = new World();
    ValueStorage vs;
    vs.load(OTB_ASSETS_DIRECTORY"/world.vs");
    world->deserialize(vs);

    world->add_normal_system(RenderControlSystem::render_begin);
    world->add_normal_system(MeshSystem::render_meshes);
    world->add_normal_system(RenderControlSystem::render_end);

    return std::unique_ptr<World>(world);
}
}