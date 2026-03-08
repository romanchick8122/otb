#include "character_system.h"

#include "core/ecs/world.h"
#include "core/render/camera_component.h"
#include "core/world/physics/velocity_component.h"
#include "core/world/transform_component.h"

#include "game/character/character_component.h"

#include "raymath.h"

namespace game
{
void CharacterSystem::character_follow_camera(otb::World* world, float)
{
    using namespace otb;

    CharacterComponent* character = nullptr;
    for (auto it = world->components_begin<CharacterComponent>(); it != world->components_end<CharacterComponent>(); ++it)
    {
        OTB_ASSERT(character == nullptr);
        character = &*it;
    }

    const Transform& character_transform = character->entity->get_component<TransformComponent>()->transform;

    CameraComponent* camera = world->get_world_entity()->get_component<otb::CameraComponent>();

    Vector3 desired_position =
        character_transform.translation +
        Vector3RotateByQuaternion({-1, 0, 0}, character_transform.rotation) * character->camera_follow_distance +
        Vector3{0, character->camera_follow_offset, 0};
    
    camera->camera.position = (camera->camera.position + desired_position) / 2.f;
    camera->camera.target = character_transform.translation;
}
}