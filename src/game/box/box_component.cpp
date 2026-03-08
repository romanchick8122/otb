#include "box_component.h"

namespace game
{
namespace
{
static const otb::InternedString TYPE_FIELD("type");

static const otb::InternedString BoxType_STATIC("STATIC");
static const otb::InternedString BoxType_DYNAMIC("DYNAMIC");

static const std::unordered_map<BoxComponent::BoxType, otb::InternedString> ser_map {
    { BoxComponent::BoxType::STATIC, BoxType_STATIC },
    { BoxComponent::BoxType::DYNAMIC, BoxType_DYNAMIC },
};
static const std::unordered_map<otb::InternedString, BoxComponent::BoxType> deser_map {
    { BoxType_STATIC, BoxComponent::BoxType::STATIC },
    { BoxType_DYNAMIC, BoxComponent::BoxType::DYNAMIC },
};
}

otb::ValueStorage BoxComponent::serialize() const
{
    using namespace otb;
    return ValueStorage::DictType {
        { TYPE_FIELD, std::string(ser_map.at(type).c_str()) },
    };
}

otb::Component* BoxComponent::deserialize(const otb::ValueStorage& vs)
{
    using namespace otb;
    OTB_ASSERT(std::holds_alternative<ValueStorage::DictType>(vs.storage));
    const auto& dict = std::get<ValueStorage::DictType>(vs.storage);

    BoxComponent* result = new BoxComponent();
    result->type = deser_map.at(InternedString(std::get<std::string>(dict.at(TYPE_FIELD).storage).c_str()));
    return result;
}
}