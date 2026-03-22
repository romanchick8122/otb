#include "asset.h"

#include "windows.h"

#include <filesystem>

namespace otb
{
std::string AssetUtils::get_asset_file_path(InternedString asset_path)
{
    static std::string assets_root = []
    {
        #if defined(OTB_DEBUG)
        return OTB_ASSETS_DIRECTORY;
        #else
        char buffer[1024];
        GetModuleFileName(NULL, buffer, 1024);
        const auto root = std::filesystem::path(std::string(buffer)).parent_path();
        return root.string() + OTB_ASSETS_DIRECTORY;
        #endif
    }();
    return assets_root + asset_path.c_str();
}
}