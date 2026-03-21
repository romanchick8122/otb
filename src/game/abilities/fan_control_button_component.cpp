#include "fan_control_button_component.h"

#include "core/asset/value_storage_utils.h"
#include "core/ecs/entity.h"

#include <sstream>

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
    static const otb::InternedString ANIMATED_ENTITIES_FIELD("animated_entities");
}

otb::ValueStorage FanControlButtonComponent::serialize() const
{
    using namespace otb;
    std::stringstream ss;
    for (const Entity* entity : animated_entities)
    {
        ss << entity->name.c_str() << " ";
    }
    return ValueStorage::DictType {
        { TARGET_ENTITY_FIELD, std::string(target_entity.c_str()) },
        { ENABLED_FIELD, ValueStorageUtils::serialize(enabled) },
        { ANIMATED_ENTITIES_FIELD, ss.str() },
    };
}

otb::Component* FanControlButtonComponent::deserialize(const otb::ValueStorage& vs)
{
    using namespace otb;
    OTB_ASSERT(std::holds_alternative<ValueStorage::DictType>(vs.storage));
    const auto& dict = std::get<ValueStorage::DictType>(vs.storage);
    const InternedString target(std::get<std::string>(dict.at(TARGET_ENTITY_FIELD).storage).c_str());
    const bool enabled = ValueStorageUtils::deserialize<bool>(dict.at(ENABLED_FIELD));

    auto* result = new FanControlButtonComponent(target, enabled);

    std::stringstream ss(std::get<std::string>(dict.at(ANIMATED_ENTITIES_FIELD).storage));
    std::string name = {};
    while (ss >> name)
    {
        result->animated_entities_names.emplace_back(name.c_str());
    }

    return result;
}
}