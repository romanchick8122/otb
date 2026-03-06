#include "model_asset.h"

namespace otb
{
ModelAsset::ModelAsset(InternedString asset_path)
    : AssetBase(asset_path)
    , model(LoadModel(AssetUtils::get_asset_file_path(asset_path).c_str()))
{
}

ModelAsset::~ModelAsset()
{
    UnloadModel(model);
}
}