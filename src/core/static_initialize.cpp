#include "static_initialize.h"

#include "core/ecs/world.h"

#include "core/render/camera_component.h"
#include "core/render/model_component.h"
#include "core/world/transform_component.h"

namespace otb
{
void run_static_initializer()
{
    REGISTER_COMPONENT_TYPE(CameraComponent);
    REGISTER_COMPONENT_TYPE(ModelComponent);
    REGISTER_COMPONENT_TYPE(TransformComponent);
}
}