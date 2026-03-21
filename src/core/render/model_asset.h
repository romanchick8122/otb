#pragma once

#include "core/asset/asset.h"

#include <raylib.h>

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
    size_t animation_count;

    struct AnimationGraph
    {
        struct Transition
        {
            size_t target;
            float transition_time;
        };
        std::vector<std::vector<Transition>> animation_transitions;
        struct DirectionEntry
        {
            const Transition* transition;
            size_t path_length;
        };
        std::vector<std::vector<DirectionEntry>> directions;
    } anim_graph;

    std::unordered_map<otb::InternedString, size_t> animation_lookup;
    std::vector<otb::InternedString> animation_names;
};
}