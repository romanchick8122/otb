#pragma once

#include <raylib.h>

namespace otb
{
struct UIUtils
{
static Vector2 get_screen_size();

static Vector2 normalized_to_screen(const Vector2);
static Rectangle normalized_to_screen(const Rectangle&);

static Rectangle rect_from_min_max(const Vector2 min, const Vector2 max);

static float get_norm_target_width(const Vector2 reference, const float target_height);

static Rectangle get_texture_rect(const Texture2D& texture);
};
}