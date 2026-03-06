#include "surface_asset.h"

namespace game
{
SurfaceAsset::SurfaceAsset(otb::InternedString asset_path)
    : AssetBase(asset_path)
    , image(LoadImage(otb::AssetUtils::get_asset_file_path(asset_path).c_str()))
    , texture(LoadTextureFromImage(image))
{
}

SurfaceAsset::~SurfaceAsset()
{
    UnloadTexture(texture);
    UnloadImage(image);
}
}