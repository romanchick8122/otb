#include "surface_component.h"

namespace game
{
namespace
{
    static const otb::InternedString ASSET_PATH_FIELD { "asset_path" };
}

otb::ValueStorage SurfaceComponent::serialize() const
{
    using namespace otb;

    return ValueStorage::DictType {
        { ASSET_PATH_FIELD, std::string(asset->path.c_str()) },
    };
}

otb::Component* SurfaceComponent::deserialize(const otb::ValueStorage& vs)
{
    using namespace otb;

    OTB_ASSERT(std::holds_alternative<ValueStorage::DictType>(vs.storage));
    const auto& dict = std::get<ValueStorage::DictType>(vs.storage);

    SurfaceComponent* result = new SurfaceComponent();
    result->asset = AssetUtils::get_asset<SurfaceAsset>({ std::get<std::string>(dict.at(ASSET_PATH_FIELD).storage).c_str() });
    return result;
}
}