#include "model_component.h"

#include "core/asset/value_storage_utils.h"

#include "raymath.h"

namespace otb
{
ModelComponent::ModelComponent(InternedString asset_path)
    : asset(AssetUtils::get_asset<ModelAsset>(asset_path))
    , model_space_collider(Transform{
        .translation = {},
        .rotation = QuaternionIdentity(),
        .scale = {1, 1, 1},
    })
{
}

namespace
{
    static const InternedString PATH_FIELD("path");
    static const InternedString MODEL_SPACE_COLLIDER_FIELD("model_space_collider");
}

ValueStorage ModelComponent::serialize() const
{
    return std::string(asset->path.c_str());
}

Component* ModelComponent::deserialize(const ValueStorage& vs)
{
    if (const auto* str = std::get_if<std::string>(&vs.storage))
    {
        const auto result = new ModelComponent(InternedString(str->c_str()));
        result->model_space_collider = {
            .translation = {0, 0, 0},
            .rotation = QuaternionIdentity(),
            .scale = {1, 1, 1},
        };
        return result;
    }
    else if (const auto* dict = std::get_if<ValueStorage::DictType>(&vs.storage))
    {
        const auto result = new ModelComponent(InternedString(std::get<std::string>(dict->at(PATH_FIELD).storage).c_str()));
        result->model_space_collider = ValueStorageUtils::deserialize<Transform>(dict->at(MODEL_SPACE_COLLIDER_FIELD));
        return result;
    }
    else 
    {
        OTB_ASSERT(false);
        return nullptr;
    }
}

void ModelComponent::request_animation(InternedString animation_name, bool request_looping)
{
    requested_animation_index = asset->animation_lookup[animation_name];
    looping_requested = request_looping;
}

void ModelComponent::set_animation_speed(float speed)
{
    animation_speed = speed;
}
}