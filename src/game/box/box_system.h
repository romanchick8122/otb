#pragma once

#include "core/ecs/component.h"

#include "raylib.h"

namespace otb
{
class World;
class TransformComponent;
}

namespace game
{
struct BoxSystem
{
    static void create_components(otb::World*);
    static void find_collision_chain(otb::World*);
    static void update_chain(otb::World*);
    static void update_from_velocity(otb::World*);
};

class BoxSingleComponent : public otb::Component
{
  public:
    otb::ValueStorage serialize() const override;
    static otb::Component* deserialize(const otb::ValueStorage&);

    float gravity = 9.8f;
    float air_drag_coefficient = .8f; // With no other forces, after 1s velocity will be multiplied by this value

    ~BoxSingleComponent() override = default;

  private:
    struct Entry
    {
        otb::Entity* entity;
        Vector3 displacement;
        otb::TransformComponent* transform_component;
    };

    std::vector<Entry> chain; 

    friend class BoxSystem;
};
}