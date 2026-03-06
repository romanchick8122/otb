#include "asset.h"

#include <string>

namespace otb
{
AssetBase::AssetBase(InternedString asset_path)
    : path(asset_path)
{
}

std::string AssetUtils::get_asset_file_path(InternedString asset_path)
{
    static std::string data;
    data = OTB_ASSETS_DIRECTORY;
    data += asset_path.c_str();
    return data;
}
}