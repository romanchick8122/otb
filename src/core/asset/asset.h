#pragma once

#include "core/interned_string.h"

#include <memory>
#include <unordered_map>

namespace otb
{
class AssetBase
{
  public:
    AssetBase(InternedString);

    virtual ~AssetBase() = default;

    InternedString path;
};

template<class T, std::enable_if_t<std::is_base_of_v<AssetBase, T> && std::is_constructible_v<T, InternedString>, int> = 0>
using Asset = std::shared_ptr<T>;

struct AssetUtils
{
    static std::string get_asset_file_path(InternedString asset_path);

    template<class T>
    static Asset<T> get_asset(InternedString path)
    {
        static std::unordered_map<InternedString, std::weak_ptr<T>> storage;

        if (const auto it = storage.find(path);
            it != storage.end()) [[likely]]
        {
            if (it->second.expired()) [[unlikely]]
            {
                storage.erase(path);
            }
            else
            {
                return it->second.lock();
            }
        }

        Asset<T> result = std::make_shared<T>(path);
        storage.emplace(path, std::weak_ptr<T>(result));
        return result;
    }
};
}