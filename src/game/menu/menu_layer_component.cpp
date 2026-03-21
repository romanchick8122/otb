#include "menu_layer_component.h"

#include "core/asset/value_storage_utils.h"

#include <raymath.h>

namespace game
{
namespace
{
    static const otb::InternedString TEXTURE_FIELD("texture");
    static const otb::InternedString Z_ORDER_FIELD("z_order");
    static const otb::InternedString POSITION_FIELD("position");
    static const otb::InternedString TARGET_HEIGHT_FIELD("target_height");
    static const otb::InternedString TEXTURE_SIZE_OVERRIDE_FIELD("texture_size_override");
}

otb::ValueStorage MenuLayerComponent::serialize() const
{
    using namespace otb;
    return ValueStorage::DictType {
        { TEXTURE_FIELD, std::string(texture->path.c_str()) },
        { Z_ORDER_FIELD, ValueStorageUtils::serialize(z_order) },
        { POSITION_FIELD, ValueStorageUtils::serialize(position) },
        { TARGET_HEIGHT_FIELD, ValueStorageUtils::serialize(position) },
        { TEXTURE_SIZE_OVERRIDE_FIELD, ValueStorageUtils::serialize(texture_size_override) },
    };
}

otb::Component* MenuLayerComponent::deserialize(const otb::ValueStorage& vs)
{
    using namespace otb;

    OTB_ASSERT(std::holds_alternative<ValueStorage::DictType>(vs.storage));
    const auto& dict = std::get<ValueStorage::DictType>(vs.storage);
    auto* result = new MenuLayerComponent();

    result->texture = AssetUtils::get_asset<TextureAsset>(InternedString(std::get<std::string>(dict.at(TEXTURE_FIELD).storage).c_str()));
    result->z_order = ValueStorageUtils::deserialize<size_t>(dict.at(Z_ORDER_FIELD));
    result->position = ValueStorageUtils::deserialize<Vector2>(dict.at(POSITION_FIELD));
    result->target_height = ValueStorageUtils::deserialize<float>(dict.at(TARGET_HEIGHT_FIELD));

    if (auto it = dict.find(TEXTURE_SIZE_OVERRIDE_FIELD);
        it != dict.end())
    {
        result->texture_size_override = ValueStorageUtils::deserialize<Vector2>(it->second);
    }
    else
    {
        result->texture_size_override = { static_cast<float>(result->texture->texture.width), static_cast<float>(result->texture->texture.height) };
    }

    return result;
}
namespace
{
Vector2 get_screen_size()
{
    return Vector2{static_cast<float>(GetRenderWidth()), static_cast<float>(GetRenderHeight())};
}

Vector2 normalized_to_screen(const Vector2 v)
{
    return (v + Vector2{1.f, 1.f}) / 2.f * get_screen_size();
}
}
Rectangle MenuLayerComponent::get_screen_space_rect() const
{
    const Vector2 screen_size = get_screen_size();
    const float target_width = target_height * screen_size.y / screen_size.x * texture_size_override.x / texture_size_override.y;
    const Vector2 offset { target_width, target_height };
    const Vector2 pos_min = normalized_to_screen(position - offset / 2);
    const Vector2 pos_max = normalized_to_screen(position + offset / 2);
    const Vector2 screen_space_size = pos_max - pos_min;
    return { pos_min.x, pos_min.y, screen_space_size.x, screen_space_size.y };
}
}