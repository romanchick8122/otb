#include "character_component.h"

#include "core/asset/value_storage_utils.h"

namespace game
{
namespace
{
    static const otb::InternedString CAMERA_FOLLOW_DISATNCE_FIELD { "camera_follow_distance" };
    static const otb::InternedString CAMERA_FOLLOW_OFFSET_FIELD { "camera_follow_offset" };
}

otb::ValueStorage CharacterComponent::serialize() const
{
    using namespace otb;

    return ValueStorage::DictType {
        { CAMERA_FOLLOW_DISATNCE_FIELD, ValueStorageUtils::serialize(camera_follow_distance) },
        { CAMERA_FOLLOW_OFFSET_FIELD, ValueStorageUtils::serialize(camera_follow_offset) },
    };
}

otb::Component* CharacterComponent::deserialize(const otb::ValueStorage& vs)
{
    using namespace otb;

    OTB_ASSERT(std::holds_alternative<ValueStorage::DictType>(vs.storage));
    const auto& dict = std::get<ValueStorage::DictType>(vs.storage);

    const auto result = new CharacterComponent();
    result->camera_follow_distance = ValueStorageUtils::deserialize<float>(dict.at(CAMERA_FOLLOW_DISATNCE_FIELD));
    result->camera_follow_offset = ValueStorageUtils::deserialize<float>(dict.at(CAMERA_FOLLOW_OFFSET_FIELD));
    return result;
}
}