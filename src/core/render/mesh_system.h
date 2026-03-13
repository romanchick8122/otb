#pragma once

namespace otb
{
class World;

struct MeshSystem
{
static void update_animations(World*, float);
static void render_meshes(World*, float);
};
}