!<DICT>
  entities: !<ARRAY>
    !<DICT>
      components: !<DICT>
      name: !<VALUE> _world
    !<DICT>
      components: !<DICT>
        MenuLayerComponent: !<DICT>
          texture: !<VALUE> /ui/main_menu_test.png
          z_order: !<VALUE> 0
          position: !<VALUE> 0 0
          target_height: !<VALUE> 2
          group: !<VALUE> main_menu
      name: !<VALUE> main_menu
    !<DICT>
      components: !<DICT>
        MenuLayerComponent: !<DICT>
          texture: !<VALUE> /transparent.png
          z_order: !<VALUE> 1
          position: !<VALUE> 0 -0.1
          target_height: !<VALUE> 0.237
          texture_size_override: !<VALUE> 400 128
          group: !<VALUE> main_menu
        MenuButtonComponent: !<VALUE> go_level.lvl1
      name: !<VALUE> lvl1_button
    !<DICT>
      components: !<DICT>
        MenuLayerComponent: !<DICT>
          texture: !<VALUE> /transparent.png
          z_order: !<VALUE> 1
          position: !<VALUE> 0 0.276
          target_height: !<VALUE> 0.237
          texture_size_override: !<VALUE> 400 128
          group: !<VALUE> main_menu
        MenuButtonComponent: !<VALUE> go_level.lvl2
      name: !<VALUE> lvl2_button