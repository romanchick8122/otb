#include "static_initialize.h"

#include "core/ecs/world.h"

#include "game/abilities/fan_control_button_component.h"
#include "game/abilities/fan_component.h"
#include "game/box/box_component.h"
#include "game/box/box_system.h"
#include "game/character/character_component.h"
#include "game/character/input_receiver_component.h"
#include "game/inventory/item_pickup_component.h"
#include "game/menu/event_trigger_component.h"
#include "game/menu/menu_button_component.h"
#include "game/menu/menu_layer_component.h"

namespace game
{
void run_static_initializer()
{
    REGISTER_COMPONENT_TYPE(BoxComponent);
    REGISTER_COMPONENT_TYPE(BoxSingleComponent);
    REGISTER_COMPONENT_TYPE(CharacterComponent);
    REGISTER_COMPONENT_TYPE(EventTriggerComponent);
    REGISTER_COMPONENT_TYPE(InputReceiverComponent);
    REGISTER_COMPONENT_TYPE(ItemPickupComponent);
    REGISTER_COMPONENT_TYPE(FanComponent);
    REGISTER_COMPONENT_TYPE(FanControlButtonComponent);
    REGISTER_COMPONENT_TYPE(MenuButtonComponent);
    REGISTER_COMPONENT_TYPE(MenuLayerComponent);
}
}