#include "model_asset.h"

#include "core/assert.h"
#include "core/asset/value_storage_utils.h"

#include <algorithm>
#include <iterator>

namespace otb
{
namespace
{
void load_anim_graph(ModelAsset& model, ValueStorage agvs)
{
    OTB_ASSERT(std::holds_alternative<ValueStorage::DictType>(agvs.storage));
    model.anim_graph.animation_transitions.resize(model.animation_count);
    for (const auto& [k, v] : std::get<ValueStorage::DictType>(agvs.storage))
    {
        const size_t model_i = model.animation_lookup[k];
        std::vector<ModelAsset::AnimationGraph::Transition>& transitions_vector = model.anim_graph.animation_transitions[model_i];
        OTB_ASSERT(std::holds_alternative<ValueStorage::DictType>(v.storage));
        const auto& tvs = std::get<ValueStorage::DictType>(v.storage);
        transitions_vector.reserve(tvs.size());
        std::transform(tvs.begin(), tvs.end(), std::back_inserter(transitions_vector), [&model](const std::pair<InternedString, ValueStorage>& vvs) {
            const float blend_time = ValueStorageUtils::deserialize<float>(vvs.second);
            OTB_ASSERT(model.animation_lookup.find(vvs.first) != model.animation_lookup.end());
            return ModelAsset::AnimationGraph::Transition{ model.animation_lookup[vvs.first], blend_time };
        });
    }

    auto& agd = model.anim_graph.directions;
    agd.resize(model.animation_count);
    for (size_t i = 0; i < model.animation_count; ++i)
    {
        agd[i].resize(model.animation_count);
        for (size_t j = 0; j < model.animation_count; ++j)
        {
            agd[i][j] = {
                .transition = nullptr,
                .path_length = i == j ? 0 : std::string::npos / 2,
            };
        }
    }
    for (size_t i = 0; i < model.animation_count; ++i)
    {
        for (const auto& transition : model.anim_graph.animation_transitions[i])
        {
            agd[i][transition.target] = {
                .transition = &transition,
                .path_length = 1,
            };
        }
    }
    for (size_t k = 0; k < model.animation_count; ++k)
    {
        for (size_t i = 0; i < model.animation_count; ++i)
        {
            if (i == k)
            {
                continue;
            }
            for (size_t j = 0; j < model.animation_count; ++j)
            {
                if (j == k || j == i)
                {
                    continue;
                }
                const size_t candidate_length = agd[i][k].path_length + agd[k][j].path_length;
                if (agd[i][j].path_length > candidate_length)
                {
                    agd[i][j] = {
                        .transition = agd[i][k].transition,
                        .path_length = candidate_length,
                    };
                }
            }
        }
    }
}
}

ModelAsset::ModelAsset(InternedString asset_path)
    : AssetBase(asset_path)
    , model(LoadModel(AssetUtils::get_asset_file_path(asset_path).c_str()))
{
    int anim_count_raw = 0;
    animations = LoadModelAnimations(AssetUtils::get_asset_file_path(asset_path).c_str(), &anim_count_raw);
    if (animations != nullptr)
    {
        animation_count = anim_count_raw;
        animation_names.reserve(animation_count);

        for (int anim_index = 0; anim_index < animation_count; ++anim_index)
        {
            animation_names.emplace_back(animations[anim_index].name);
            animation_lookup.emplace(animation_names.back(), anim_index);
        }
        ValueStorage agvs;
        agvs.load(AssetUtils::get_asset_file_path(AssetUtils::get_sibling_asset(asset_path, ".ag")).c_str());
        load_anim_graph(*this, agvs);

    }
}

ModelAsset::~ModelAsset()
{
    UnloadModel(model);
}
}