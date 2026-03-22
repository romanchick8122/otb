#include "world_creator.h"

#include "core/ecs/world.h"
#include "core/render/camera_component.h"
#include "core/render/mesh_system.h"
#include "core/render/model_component.h"
#include "core/render/render_control_system.h"
#include "core/world/transform_component.h"

#include "game/abilities/box_attachment_system.h"
#include "game/abilities/fan_system.h"
#include "game/box/box_system.h"
#include "game/character/character_system.h"
#include "game/character/input_system.h"
#include "game/inventory/inventory_system.h"
#include "game/menu/menu_system.h"
#include "game/ui/hud_system.h"

namespace game
{
std::unique_ptr<otb::World> create_world(otb::InternedString world_asset)
{
    using namespace otb;

    World* world = new World();
    ValueStorage vs;
    vs.load(AssetUtils::get_asset_file_path(world_asset).c_str());
    world->deserialize(vs);

    // -------- INITIAL ------
    BoxSystem::create_components(world);
    FanSystem::init(world);
    InventorySystem::init(world);

    // -------- FIXED --------
    world->add_fixed_system(InputSystem::clear_input);
    world->add_fixed_system(InputSystem::collect_input_kb_mouse);
    world->add_fixed_system(InputSystem::update_action_queue);
    world->add_fixed_system(InputSystem::apply_input);

    world->add_fixed_system(FanSystem::apply_velocity);
    world->add_fixed_system(BoxAttachmentSystem::process_ability_activation);

    world->add_fixed_system(BoxAttachmentSystem::process_ability);

    world->add_fixed_system(BoxSystem::find_collision_chain);
    world->add_fixed_system(BoxSystem::find_active_pushing);
    world->add_fixed_system(BoxSystem::push_back_chain);
    world->add_fixed_system(BoxSystem::update_chain);
    
    world->add_fixed_system(BoxSystem::update_from_velocity);
    world->add_fixed_system(FanSystem::update_controllers);

    world->add_fixed_system(CharacterSystem::update_state);

    world->add_fixed_system(BoxSystem::late_update_velocity);
    // -------- NORMAL -------
    world->add_normal_system(MeshSystem::update_animations);
    world->add_normal_system(CharacterSystem::update_camera);

    world->add_normal_system(RenderControlSystem::render_begin);

    world->add_normal_system(MeshSystem::render_meshes);
    world->add_normal_system(BoxAttachmentSystem::debug_draw);

    world->add_normal_system(RenderControlSystem::render_stop_3d_start_2d);

    world->add_normal_system(HudSystem::render_hud);

    world->add_normal_system(RenderControlSystem::render_end);

    world->fixed_frame_time = 1 / 60.f;
    world->max_fixed_frames = 2;

    return std::unique_ptr<World>(world);
}
std::unique_ptr<otb::World> create_menu_world()
{
    using namespace otb;

    World* world = new World();
    ValueStorage vs;
    vs.load(AssetUtils::get_asset_file_path(InternedString("/menu_world.vs")).c_str());
    world->deserialize(vs);

    // -------- INITIAL ------
    MenuSystem::init(world);

    // -------- FIXED --------
    world->add_fixed_system(MenuSystem::collect_events);
    world->add_fixed_system(MenuSystem::subworld_update_fixed);

    world->add_fixed_system(MenuSystem::process_events);

    // -------- NORMAL -------
    world->add_normal_system(MenuSystem::render_menu);
    world->add_normal_system(MenuSystem::subworld_update);

    world->fixed_frame_time = 1 / 60.f;
    world->max_fixed_frames = 2;
    
    return std::unique_ptr<World>(world);
}
}