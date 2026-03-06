#pragma once

#include "core/asset/asset.h"

#include "raylib.h"

namespace game
{
class SurfaceAsset : public otb::AssetBase
{
  public:
    SurfaceAsset(otb::InternedString);

    ~SurfaceAsset() override;

  private:
    Image image;
    Texture2D texture;

    friend class SurfaceSystem;
};
}