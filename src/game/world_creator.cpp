#include "world_creator.h"

#include "core/ecs/world.h"
#include "core/render/camera_component.h"
#include "core/render/mesh_system.h"
#include "core/render/model_component.h"
#include "core/render/render_control_system.h"
#include "core/world/transform_component.h"

#include "game/abilities/box_attachment_system.h"
#include "game/box/box_system.h"
#include "game/character/character_system.h"
#include "game/character/input_system.h"
#include "game/surface/surface_system.h"

namespace game
{
std::unique_ptr<otb::World> create_world()
{
    using namespace otb;

    World* world = new World();
    ValueStorage vs;
    vs.load(OTB_ASSETS_DIRECTORY"/world.vs");
    world->deserialize(vs);

    // -------- FIXED --------
    world->add_fixed_system(BoxSystem::create_components);

    world->add_fixed_system(InputSystem::collect_input_kb_mouse);
    world->add_fixed_system(InputSystem::apply_input);

    world->add_fixed_system(BoxAttachmentSystem::process_ability_activation);

    world->add_fixed_system(BoxAttachmentSystem::process_ability);

    world->add_fixed_system(BoxSystem::find_collision_chain);
    world->add_fixed_system(BoxSystem::push_back_chain);
    world->add_fixed_system(BoxSystem::update_chain);
    
    world->add_fixed_system(BoxSystem::update_from_velocity);

    // -------- NORMAL -------
    world->add_normal_system(CharacterSystem::character_follow_camera);
    world->add_normal_system(RenderControlSystem::render_begin);
    world->add_normal_system(MeshSystem::render_meshes);
    world->add_normal_system(BoxAttachmentSystem::debug_draw);
    world->add_normal_system(RenderControlSystem::render_end);

    return std::unique_ptr<World>(world);
}
}