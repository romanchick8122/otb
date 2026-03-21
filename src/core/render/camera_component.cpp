#include "camera_component.h"

#include "core/asset/value_storage_utils.h"

namespace
{
static const otb::InternedString POSITION_FIELD { "position" };
static const otb::InternedString TARGET_FIELD { "target" };
static const otb::InternedString UP_FIELD { "up" };
static const otb::InternedString FOVY_FIELD { "fovy" };
static const otb::InternedString PROJECITON_FIELD { "projection" };
}

namespace otb
{
CameraComponent::CameraComponent()
{
    camera.position = { 5.0f, 5.0f, 5.0f }; // Camera position
    camera.target = { 0.0f, 2.0f, 0.0f };   // Camera looking at point
    camera.up = { 0.0f, 1.0f, 0.0f };       // Camera up vector (rotation towards target)
    camera.fovy = 90.0f;                             // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;          // Camera projection type
}

ValueStorage CameraComponent::serialize() const
{
    return ValueStorage::DictType{
        { POSITION_FIELD, ValueStorageUtils::serialize(camera.position) },
        { TARGET_FIELD, ValueStorageUtils::serialize(camera.target) },
        { UP_FIELD, ValueStorageUtils::serialize(camera.up) },
        { FOVY_FIELD, ValueStorageUtils::serialize(camera.fovy) },
        { PROJECITON_FIELD, ValueStorageUtils::serialize(camera.projection) },
    };
}

Component* CameraComponent::deserialize(const ValueStorage& vs)
{
    OTB_ASSERT(std::holds_alternative<ValueStorage::DictType>(vs.storage));
    const auto& dict = std::get<ValueStorage::DictType>(vs.storage);

    auto* result = new CameraComponent();

    result->camera.position = ValueStorageUtils::deserialize<Vector3>(dict.at(POSITION_FIELD));
    result->camera.target = ValueStorageUtils::deserialize<Vector3>(dict.at(TARGET_FIELD));
    result->camera.up = ValueStorageUtils::deserialize<Vector3>(dict.at(UP_FIELD));
    result->camera.fovy = ValueStorageUtils::deserialize<float>(dict.at(FOVY_FIELD));
    result->camera.projection = ValueStorageUtils::deserialize<int>(dict.at(PROJECITON_FIELD));

    return result;
}
}