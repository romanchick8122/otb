#include "mesh_system.h"

#include "core/ecs/world.h"
#include "core/math/transform_utils.h"
#include "core/render/model_component.h"
#include "core/world/transform_component.h"

#include "raylib.h"
#include "raymath.h"

namespace otb
{
void MeshSystem::update_animations(World* world, float dt)
{
    for (auto it = world->components_begin<ModelComponent>(); it != world->components_end<ModelComponent>(); ++it)
    {
        if (it->requested_animation_index == std::string::npos)
        {
            continue;
        }
        const ModelAnimation& anim = it->asset->animations[it->requested_animation_index];
        it->animation_time += it->animation_speed * dt;
        if (it->animation_time >= anim.keyframeCount || it->animation_time < 0.f)
        {
            if (it->looping_requested)
            {
                if (it->animation_time < 0)
                {
                    it->animation_time += anim.keyframeCount;
                }
                else
                {
                    it->animation_time -= anim.keyframeCount;
                }
            }
            else
            {
                it->animation_time = 0.f;
                it->requested_animation_index = std::string::npos;
            }
        }
    }
}

void MeshSystem::render_meshes(World* world, float)
{
    for (auto it = world->components_begin<ModelComponent>(); it != world->components_end<ModelComponent>(); ++it)
    {
        const TransformComponent* transform_component = it->entity->get_component<TransformComponent>();
        OTB_ASSERT(transform_component != nullptr);

        const Model& model = it->asset->model;
        Vector3 axis;
        float angle;

        QuaternionToAxisAngle(transform_component->transform.rotation, &axis, &angle);

        if (it->model_space_collider.translation.y != 0) {
            int x = 0;
            ++x;
        }

        if (it->requested_animation_index != std::string::npos)
        {
            UpdateModelAnimation(model, it->asset->animations[it->requested_animation_index], it->animation_time);
        }

        DrawModelEx(
            model,
            transform_component->transform.translation + it->model_space_collider.translation,
            axis,
            angle / DEG2RAD,
            transform_component->transform.scale * it->model_space_collider.scale,
            WHITE);
    }
}
}