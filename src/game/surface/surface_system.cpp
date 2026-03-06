#include "surface_system.h"

#include "core/ecs/world.h"
#include "core/math/transform_utils.h"
#include "core/world/physics/collision_component.h"
#include "core/world/transform_component.h"

#include "game/character/character_component.h"
#include "game/surface/surface_component.h"

#include "raylib.h"
#include "raymath.h"

#include <array>

namespace game
{
void SurfaceSystem::create_surface_colliders(otb::World* world)
{
    using namespace otb;

    CharacterComponent* character = nullptr;
    for (auto it = world->components_begin<CharacterComponent>(); it != world->components_end<CharacterComponent>(); ++it)
    {
        OTB_ASSERT(character == nullptr);
        character = &*it;
    }
    OTB_ASSERT(character != nullptr);

    for (auto it = world->components_begin<SurfaceComponent>(); it != world->components_end<SurfaceComponent>(); ++it)
    {
        if (!it->entity->has_component<CollisionComponent>())
        {
            const SurfaceComponent* surface_component = &*it;
            const TransformComponent* transform_component = it->entity->get_component<TransformComponent>();
            const auto test_fn = [surface_component, transform_component](const Ray& ray)
            {
                std::array<Vector3, 4> points {
                    Vector3{ -0.5, 0, -0.5 },
                    Vector3{ -0.5, 0, 0.5 },
                    Vector3{ 0.5, 0, 0.5 },
                    Vector3{ 0.5, 0, -0.5 },
                };

                for (Vector3& point : points)
                {
                    point = TransformUtils::apply_transform(transform_component->transform, point);
                }
                return GetRayCollisionQuad(ray, points[0], points[1], points[2], points[3]);
            };
            const auto callback_fn = [character, surface_component](Vector3 point)
            {
                character->is_on_surface = true;
            };

            it->entity->add_component(new CollisionComponent(test_fn, callback_fn));
        }
    }
}

void SurfaceSystem::debug_draw(otb::World* world, float)
{
    using namespace otb;

    Model plane = LoadModelFromMesh(GenMeshPlane(1, 1, 1, 1));
    for (auto it = world->components_begin<SurfaceComponent>(); it != world->components_end<SurfaceComponent>(); ++it)
    {
        plane.materials[0].maps[0].texture = it->asset->texture;
        const auto* transform_component = it->entity->get_component<TransformComponent>();
        OTB_ASSERT(transform_component);

        Vector3 axis;
        float angle;
        QuaternionToAxisAngle(transform_component->transform.rotation, &axis, &angle);

        DrawModelEx(plane, transform_component->transform.translation, axis, angle / DEG2RAD, transform_component->transform.scale, WHITE);
    }

    UnloadModel(plane);
}
}