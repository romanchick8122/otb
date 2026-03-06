#include "mesh_system.h"

#include "core/ecs/world.h"
#include "core/render/model_component.h"

#include "raylib.h"

namespace otb
{
void MeshSystem::render_meshes(World* world, float)
{
    for (auto it = world->components_begin<ModelComponent>(); it != world->components_end<ModelComponent>(); ++it)
    {
        const Model& model = it->model;
        for (int i = 0; i < model.meshCount; i++)
            DrawMesh(model.meshes[i], model.materials[1], model.transform);
    }
}
}