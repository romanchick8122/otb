#include "texture_asset.h"

namespace otb
{
TextureAsset::TextureAsset(InternedString asset_path)
    : AssetBase(asset_path)
    , texture(LoadTexture(AssetUtils::get_asset_file_path(asset_path).c_str()))
{
}

TextureAsset::~TextureAsset()
{
    UnloadTexture(texture);
}
}