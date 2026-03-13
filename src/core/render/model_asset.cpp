#include "model_asset.h"

namespace otb
{
ModelAsset::ModelAsset(InternedString asset_path)
    : AssetBase(asset_path)
    , model(LoadModel(AssetUtils::get_asset_file_path(asset_path).c_str()))
{
    animations = LoadModelAnimations(AssetUtils::get_asset_file_path(asset_path).c_str(), &animation_count);

    for (int anim_index = 0; anim_index < animation_count; ++anim_index)
    {
        animation_lookup.emplace(animations[anim_index].name, anim_index);
    }
}

ModelAsset::~ModelAsset()
{
    UnloadModel(model);
}
}