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
    OTB_ASSERT(asset->animation_lookup.find(animation_name) != asset->animation_lookup.end());
    if (asset->anim_graph.animation_transitions.empty() || playing_animation_index == std::string::npos)
    {
        playing_animation_index = asset->animation_lookup[animation_name];
    }
    else
    {
        const size_t animation_target = asset->animation_lookup[animation_name];
        if (request_animation_index != animation_target)
        {
            playing_transition = asset->anim_graph.directions[playing_animation_index][animation_target].transition;
            transition_time = 0;
        }
        request_animation_index = animation_target;
    }
    looping_requested = request_looping;
}

void ModelComponent::set_animation_speed(float speed)
{
    animation_speed = speed;
}

void ModelComponent::set_forced_material_index(size_t index)
{
    forced_material_index = index;
}

InternedString ModelComponent::get_playing_animation() const
{
    if (playing_animation_index == std::string::npos)
    {
        return InternedString::get_empty();
    }
    return asset->animation_names[playing_animation_index];
}
}