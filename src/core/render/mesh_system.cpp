#include "mesh_system.h"

#include "core/ecs/world.h"
#include "core/math/transform_utils.h"
#include "core/render/model_component.h"
#include "core/world/transform_component.h"

#include <raylib.h>
#include <raymath.h>

#include <iostream>

namespace otb
{
void MeshSystem::update_animations(World* world, float dt)
{
    for (auto it = world->components_begin<ModelComponent>(); it != world->components_end<ModelComponent>(); ++it)
    {
        if (it->playing_animation_index == std::string::npos)
        {
            continue;
        }

        const auto request_next_transition = [&]
        {
            it->playing_animation_index = it->playing_transition->target;
            it->animation_time = 0;
            it->playing_transition = nullptr;
            it->transition_time = 0;
            if (it->playing_animation_index != it->request_animation_index)
            {
                it->playing_transition = it->asset->anim_graph.directions[it->playing_animation_index][it->request_animation_index].transition;
            }
        };

        // In transition
        if (it->playing_transition != nullptr && it->playing_transition->transition_time > 0)
        {
            it->transition_time += dt;
            if (it->transition_time > it->playing_transition->transition_time)
            {
                request_next_transition();
            }
            // Don't update if we started in transition
            continue;
        }
        OTB_ASSERT(it->playing_transition == nullptr || it->playing_transition->transition_time < 0);

        const ModelAnimation& anim = it->asset->animations[it->playing_animation_index];
        // Note - using default animation speed for all animations excpet the final one
        it->animation_time += ((it->playing_animation_index == it->request_animation_index) ? it->animation_speed : 60) * dt;
        if (it->animation_time >= static_cast<float>(anim.keyframeCount - 1) || it->animation_time < 0.f)
        {
            if (it->playing_transition != nullptr)
            {
                request_next_transition();
                continue;
            }
            if (it->looping_requested)
            {
                if (it->animation_time < 0)
                {
                    it->animation_time += static_cast<float>(anim.keyframeCount);
                }
                else
                {
                    it->animation_time -= static_cast<float>(anim.keyframeCount);
                }
            }
            else
            {
                it->animation_time = 0.f;
                it->playing_animation_index = std::string::npos;
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

        if (it->playing_animation_index != std::string::npos)
        {
            if (it->playing_transition != nullptr && it->playing_transition->transition_time > 0)
            {
                UpdateModelAnimationEx(
                    model,
                    it->asset->animations[it->playing_animation_index],
                    it->animation_time,
                    it->asset->animations[it->playing_transition->target],
                    it->transition_time,
                    it->transition_time / it->playing_transition->transition_time
                );
            }
            else
            {
                UpdateModelAnimation(model, it->asset->animations[it->playing_animation_index], it->animation_time);
            }
        }

        const Vector3 translation = transform_component->transform.translation + it->model_space_collider.translation;
        const Vector3 scale = transform_component->transform.scale * it->model_space_collider.scale;

        if (it->forced_material_index == std::string::npos)
        {
            DrawModelEx(
                model,
                translation,
                axis,
                angle / DEG2RAD,
                scale,
                WHITE);
        }
        else
        {
            const Matrix scale_matrix = MatrixScale(scale.x, scale.y, scale.z);
            const Matrix rotation_matrix = QuaternionToMatrix(transform_component->transform.rotation);
            const Matrix translation_matrix = MatrixTranslate(translation.x, translation.y, translation.z);
            const Matrix transform_matrix = ((scale_matrix * rotation_matrix) * translation_matrix);

            for (int i = 0; i < model.meshCount; ++i)
            {
                DrawMesh(model.meshes[i], model.materials[it->forced_material_index], transform_matrix);
            }
        }
    }
}
}