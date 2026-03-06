#include "mesh_system.h"

#include "core/ecs/world.h"
#include "core/math/transform_utils.h"
#include "core/render/model_component.h"
#include "core/world/transform_component.h"

#include "raylib.h"
#include "raymath.h"

namespace otb
{
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

        DrawModelEx(model, transform_component->transform.translation, axis, angle / DEG2RAD, transform_component->transform.scale, WHITE);
    }
}
}