#pragma once

#include "core/ecs/component.h"

#include <raylib.h>

namespace game
{  
class BoxComponent;
struct BoxAttachmentAbilityComponent : public otb::Component
{
    ~BoxAttachmentAbilityComponent() = default;

    BoxComponent* attached_box = nullptr;
    Vector3 local_space_attachment_position = {};
    bool pulling = false;

    bool can_attach_if_shot = false;
};
}