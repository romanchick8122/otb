#include "fan_control_button_component.h"

#include "core/asset/value_storage_utils.h"

namespace game
{
FanControlButtonComponent::FanControlButtonComponent(otb::InternedString _target_entity, bool _enabled)
    : target_entity(_target_entity)
    , enabled(_enabled)
{
}

namespace
{
    static const otb::InternedString TARGET_ENTITY_FIELD("target_entity");
    static const otb::InternedString ENABLED_FIELD("enabled");
}

otb::ValueStorage FanControlButtonComponent::serialize() const
{
    using namespace otb;
    return ValueStorage::DictType {
        { TARGET_ENTITY_FIELD, std::string(target_entity.c_str()) },
        { ENABLED_FIELD, ValueStorageUtils::serialize(enabled) },
    };
}

otb::Component* FanControlButtonComponent::deserialize(const otb::ValueStorage& vs)
{
    using namespace otb;
    OTB_ASSERT(std::holds_alternative<ValueStorage::DictType>(vs.storage));
    const auto& dict = std::get<ValueStorage::DictType>(vs.storage);
    const InternedString target(std::get<std::string>(dict.at(TARGET_ENTITY_FIELD).storage).c_str());
    const bool enabled = ValueStorageUtils::deserialize<bool>(dict.at(ENABLED_FIELD));
    return new FanControlButtonComponent(target, enabled);
}
}