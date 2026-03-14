#include "asset.h"

#include "core/assert.h"

#include <string>

namespace otb
{
AssetBase::AssetBase(InternedString asset_path)
    : path(asset_path)
{
}

InternedString AssetUtils::get_sibling_asset(InternedString asset_path, const std::string& ext)
{
    std::string result = asset_path.c_str();
    const size_t ext_point = result.rfind('.');
    OTB_ASSERT(ext_point != std::string::npos);
    result.resize(ext_point);
    result += ext;
    return InternedString(result.c_str());
}

std::string AssetUtils::get_asset_file_path(InternedString asset_path)
{
    static std::string data;
    data = OTB_ASSETS_DIRECTORY;
    data += asset_path.c_str();
    return data;
}
}