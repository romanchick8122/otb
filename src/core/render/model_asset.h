#pragma once

#include "core/asset/asset.h"

#include "raylib.h"

namespace otb
{
class ModelAsset : public AssetBase
{
  public:
    ModelAsset(InternedString asset_path);

    ~ModelAsset() override;

    Model model;
};
}