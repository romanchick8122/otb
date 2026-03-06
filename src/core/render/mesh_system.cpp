#include "mesh_system.h"

#include "core/ecs/world.h"
#include "core/math/transform_utils.h"
#include "core/render/model_component.h"
#include "core/world/transform_component.h"

#include "raylib.h"

namespace otb
{
void MeshSystem::render_meshes(World* world, float)
{
    for (auto it = world->components_begin<ModelComponent>(); it != world->components_end<ModelComponent>(); ++it)
    {
        const TransformComponent* transform_component = it->entity->get_component<TransformComponent>();
        OTB_ASSERT(transform_component != nullptr);

        const Model& model = it->asset->model;
        for (int i = 0; i < model.meshCount; i++)
            DrawMesh(model.meshes[i], model.materials[0], TransformUtils::get_transform_matrix(transform_component->transform));
    }
}
}