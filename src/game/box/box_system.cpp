#include "box_system.h"

#include "core/asset/value_storage_utils.h"
#include "core/ecs/world.h"
#include "core/math/math_utils.h"
#include "core/render/model_component.h"
#include "core/world/physics/velocity_component.h"
#include "core/world/transform_component.h"

#include "game/box/box_component.h"
#include "game/character/character_component.h"

#include "raymath.h"

namespace game
{
namespace
{
    static constexpr float eps = 0.00001f;
}

void BoxSystem::create_components(otb::World* world)
{
    using namespace otb;

    static const InternedString debug_cube_asset("/cube.glb");

    for (auto it = world->components_begin<BoxComponent>(); it != world->components_end<BoxComponent>(); ++it)
    {
        if (!it->entity->has_component<ModelComponent>())
        {
            it->entity->add_component(new ModelComponent(debug_cube_asset));
        }
        if (!it->entity->has_component<VelocityComponent>())
        {
            it->entity->add_component(new VelocityComponent());
        }
    }
}

void BoxSystem::update_from_velocity(otb::World* world)
{
    using namespace otb;

    BoxSingleComponent* box_sc = world->get_world_entity()->get_component<BoxSingleComponent>();

    const Vector3 gravity { 0, -box_sc->gravity * world->fixed_frame_time, 0};
    const float velocity_multiplier = pow(box_sc->air_drag_coefficient, world->fixed_frame_time);

    for (auto it = world->components_begin<BoxComponent>(); it != world->components_end<BoxComponent>(); ++it)
    {
        if (it->type != BoxComponent::BoxType::DYNAMIC)
        {
            continue;
        }
        VelocityComponent* box_velocity = it->entity->get_component<VelocityComponent>();
        box_velocity->velocity += gravity;

        TransformComponent* box_transform = it->entity->get_component<TransformComponent>();
        const Vector3 box_min = box_transform->transform.translation - box_transform->transform.scale / 2.f;
        const Vector3 box_max = box_transform->transform.translation + box_transform->transform.scale / 2.f;

        float max_collided_y = std::numeric_limits<float>::lowest();

        for (auto collide_it = world->components_begin<BoxComponent>(); collide_it != world->components_end<BoxComponent>(); ++collide_it)
        {
            const TransformComponent* collide_transform = collide_it->entity->get_component<TransformComponent>();
            const Vector3 collide_min = collide_transform->transform.translation - collide_transform->transform.scale / 2.f;
            const Vector3 collide_max = collide_transform->transform.translation + collide_transform->transform.scale / 2.f;

            const bool x_intersect = MathUtils::has_intersection_ranges({box_min.x, box_max.x}, {collide_min.x, collide_max.x});
            const bool z_intersect = MathUtils::has_intersection_ranges({box_min.z, box_max.z}, {collide_min.z, collide_max.z});
            if (!x_intersect || !z_intersect) [[likely]]
            {
                continue;
            }
            const Vector2 y_movement = { box_min.y, box_min.y + box_velocity->velocity.y * world->fixed_frame_time };
            if (!MathUtils::has_intersection_ranges(y_movement, { collide_max.y, collide_max.y }))
            {
                continue;
            }

            max_collided_y = std::max(max_collided_y, collide_max.y);
        }
        if (max_collided_y != std::numeric_limits<float>::lowest())
        {
            box_transform->transform.translation.y = max_collided_y + box_transform->transform.scale.y / 2.f + eps;
            box_velocity->velocity.y = 0;
        }
        box_transform->transform.translation += box_velocity->velocity * world->fixed_frame_time;
        box_velocity->velocity.y *= velocity_multiplier;
    }
}

void BoxSystem::late_update_velocity(otb::World* world)
{
    for (auto it = world->components_begin<BoxComponent>(); it != world->components_end<BoxComponent>(); ++it)
    {
        if (auto* vc = it->entity->get_component<otb::VelocityComponent>();
            vc != nullptr)
        {
            vc->velocity.x = vc->velocity.z = 0;
        }
    }
}

void BoxSystem::find_collision_chain(otb::World* world)
{
    using namespace otb;

    BoxSingleComponent* box_sc = world->get_world_entity()->get_component<BoxSingleComponent>();
    OTB_ASSERT(box_sc != nullptr);

    const CharacterComponent* character_sc = &*world->components_begin<CharacterComponent>();

    box_sc->chain.emplace_back(BoxSingleComponent::Entry{
        .entity = character_sc->entity,
        .displacement = character_sc->entity->get_component<VelocityComponent>()->velocity * world->fixed_frame_time,
        .transform_component = character_sc->entity->get_component<TransformComponent>(),
        .parent_index = std::string::npos,
    });
    box_sc->chain.back().displacement.y = 0; // Gravity is processed separately

    // Attachment requested components
    {
        for (BoxComponent* attached_component : box_sc->attached_components)
        {
            box_sc->chain.emplace_back(BoxSingleComponent::Entry{
                .entity = attached_component->entity,
                .displacement = box_sc->chain[0].displacement,
                .transform_component = attached_component->entity->get_component<TransformComponent>(),
                .parent_index = 0,
            });
        }
        box_sc->attached_components.clear();
    }

    static constexpr auto sign = [](const float v) {
        if (v < eps && v > -eps)
            return 0;
        if (v < 0)
            return -1;
        return 1;
    };

    // Sweeep all cubes
    for (size_t unprocessed_i = 0; unprocessed_i < box_sc->chain.size(); ++unprocessed_i)
    {
        BoxSingleComponent::Entry& last = box_sc->chain[unprocessed_i];
        const float x_sign = sign(last.displacement.x);
        const float z_sign = sign(last.displacement.z);
        const float x_from = last.transform_component->transform.translation.x + x_sign * last.transform_component->transform.scale.x / 2.f;
        const float z_from = last.transform_component->transform.translation.z + z_sign * last.transform_component->transform.scale.z / 2.f;
        const float x_to = x_from + last.displacement.x;
        const float z_to = z_from + last.displacement.z;
        const Vector3 box_min = last.transform_component->transform.translation - last.transform_component->transform.scale / 2.f;
        const Vector3 box_max = last.transform_component->transform.translation + last.transform_component->transform.scale / 2.f;
        const Entity* last_entity = last.entity;

        for (auto it = world->components_begin<BoxComponent>(); it != world->components_end<BoxComponent>(); ++it)
        {
            if (it->entity == last_entity)
            {
                continue;
            }

            TransformComponent* candidate_transform = it->entity->get_component<TransformComponent>();
            const Vector3 candidate_min = candidate_transform->transform.translation - candidate_transform->transform.scale / 2.f;
            const Vector3 candidate_max = candidate_transform->transform.translation + candidate_transform->transform.scale / 2.f;
            if (candidate_min.y >= box_max.y || candidate_max.y <= box_min.y)
            {
                continue;
            }

            const float edge_x = x_sign > 0 ? candidate_min.x : candidate_max.x;
            const float edge_z = z_sign > 0 ? candidate_min.z : candidate_max.z;

            const bool problematic_x = MathUtils::is_point_inside_range_safe({x_from, x_to}, edge_x) &&
                                       MathUtils::has_intersection_ranges({box_min.z, box_max.z}, {candidate_min.z, candidate_max.z});
            const bool problematic_z = MathUtils::is_point_inside_range_safe({z_from, z_to}, edge_z) &&
                                       MathUtils::has_intersection_ranges({box_min.x, box_max.x}, {candidate_min.x, candidate_max.x});

            if (!problematic_x && !problematic_z)
            {
                continue;
            }

            float displacement_x = problematic_x ? (x_to - edge_x) + x_sign * eps : 0;
            float displacement_z = problematic_z ? (z_to - edge_z) + z_sign * eps : 0;

            box_sc->chain.emplace_back(BoxSingleComponent::Entry{
                .entity = it->entity,
                .displacement = {displacement_x, 0, displacement_z},
                .transform_component = candidate_transform,
                .parent_index = unprocessed_i,
            });
        }
    }
}

void BoxSystem::push_back_chain(otb::World* world)
{
    using namespace otb;

    BoxSingleComponent* box_sc = world->get_world_entity()->get_component<BoxSingleComponent>();
    OTB_ASSERT(box_sc != nullptr);

    box_sc->chain[0].displacement = {}; // Character is moved by velocity

    if (box_sc->chain.size() <= 1)
    {
        return; // Nothing is pushed
    }

    bool block_x = false;
    bool block_z = false;

    for (size_t i = 0; i < box_sc->chain.size(); ++i)
    {
        if (box_sc->chain[i].parent_index != std::string::npos && box_sc->chain[box_sc->chain[i].parent_index].filtered)
        {
            box_sc->chain[i].filtered = true;
            continue;
        }

        if (box_sc->chain[i].entity->get_component<BoxComponent>()->type == BoxComponent::BoxType::STATIC)
        {
            for (size_t pb = box_sc->chain[i].parent_index; pb != std::string::npos; pb = box_sc->chain[pb].parent_index)
            {
                box_sc->chain[pb].displacement -= box_sc->chain[i].displacement;
            }
            block_x |= box_sc->chain[i].displacement.x != 0;
            block_z |= box_sc->chain[i].displacement.z != 0;
            box_sc->chain[i].displacement = {};
            box_sc->chain[i].filtered = true;
        }
    }
}

void BoxSystem::update_chain(otb::World* world)
{
    using namespace otb;

    BoxSingleComponent* box_sc = world->get_world_entity()->get_component<BoxSingleComponent>();

    for (BoxSingleComponent::Entry& e : box_sc->chain)
    {
        e.entity->get_component<otb::TransformComponent>()->transform.translation += e.displacement;
    }

    box_sc->chain.clear();
}

namespace
{
    static const otb::InternedString GRAVITY_FIELD("gravity");
    static const otb::InternedString AIR_DRAG_COEFFICIENT_FIELD("air_drag_coefficient");
}

otb::ValueStorage BoxSingleComponent::serialize() const
{
    using namespace otb;
    return ValueStorage::DictType {
        { GRAVITY_FIELD, ValueStorageUtils::serialize(gravity) },
        { AIR_DRAG_COEFFICIENT_FIELD, ValueStorageUtils::serialize(air_drag_coefficient) },
    };
}

otb::Component* BoxSingleComponent::deserialize(const otb::ValueStorage& vs)
{
    using namespace otb;
    OTB_ASSERT(std::holds_alternative<ValueStorage::DictType>(vs.storage));
    const auto& dict = std::get<ValueStorage::DictType>(vs.storage);

    BoxSingleComponent* result = new BoxSingleComponent();
    result->gravity = ValueStorageUtils::deserialize<float>(dict.at(GRAVITY_FIELD));
    result->air_drag_coefficient = ValueStorageUtils::deserialize<float>(dict.at(AIR_DRAG_COEFFICIENT_FIELD));
    return result;
}

void BoxSingleComponent::request_one_frame_attachment(BoxComponent* other_box)
{
    attached_components.emplace_back(other_box);
}
}