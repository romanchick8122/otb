#include "model_component.h"

namespace otb
{
ModelComponent::ModelComponent(InternedString asset_path)
    : asset(AssetUtils::get_asset<ModelAsset>(asset_path))
{
}

ValueStorage ModelComponent::serialize() const
{
    return std::string(asset->path.c_str());
}

Component* ModelComponent::deserialize(const ValueStorage& vs)
{
    const auto str_ptr = std::get_if<std::string>(&vs.storage);
    OTB_ASSERT(str_ptr != nullptr);

    return new ModelComponent(InternedString{str_ptr->c_str()});
}
}