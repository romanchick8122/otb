#pragma once

#include "core/asset/asset.h"

#include <raylib.h>

namespace otb
{
class TextureAsset : public AssetBase
{
  public:
    TextureAsset(InternedString);

    ~TextureAsset() override;

    Texture2D texture;
};
}