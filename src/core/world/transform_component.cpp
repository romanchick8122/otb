#include "transform_component.h"

#include "core/asset/value_storage_utils.h"

#include "raymath.h"

namespace
{
static const otb::InternedString TRANSLATION_FIELD { "translation" };
static const otb::InternedString ROTATION_FIELD { "rotation" };
static const otb::InternedString SCALE_FIELD { "scale" };
}

namespace otb
{
ValueStorage TransformComponent::serialize() const
{
    return ValueStorage::DictType {
        { TRANSLATION_FIELD, ValueStorageUtils::serialize(transform.translation) },
        { ROTATION_FIELD, ValueStorageUtils::serialize(QuaternionToEuler(transform.rotation)) },
        { SCALE_FIELD, ValueStorageUtils::serialize(transform.scale) },
    };
}

Component* TransformComponent::deserialize(const ValueStorage& vs)
{
    OTB_ASSERT(std::holds_alternative<ValueStorage::DictType>(vs.storage));
    const auto& dict = std::get<ValueStorage::DictType>(vs.storage);

    TransformComponent* result = new TransformComponent();

    result->transform.translation = ValueStorageUtils::deserialize<Vector3>(dict.at(TRANSLATION_FIELD));
    const Vector3 rot_euler = ValueStorageUtils::deserialize<Vector3>(dict.at(ROTATION_FIELD));
    result->transform.rotation = QuaternionFromEuler(rot_euler.x, rot_euler.y, rot_euler.z);
    result->transform.scale = ValueStorageUtils::deserialize<Vector3>(dict.at(SCALE_FIELD));

    return result;
}
}