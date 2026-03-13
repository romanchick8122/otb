#pragma once

#include "core/asset/asset.h"

#include "raylib.h"

#include <unordered_map>

namespace otb
{
class ModelAsset : public AssetBase
{
  public:
    ModelAsset(InternedString asset_path);

    ~ModelAsset() override;

    Model model;
    ModelAnimation* animations;
    int animation_count;

    std::unordered_map<otb::InternedString, int> animation_lookup;
};
}