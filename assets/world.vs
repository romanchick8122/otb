!<DICT>
  entities: !<ARRAY>
    !<DICT>
      name: !<VALUE> _world
      components: !<DICT>
        CameraComponent: !<DICT>
          position: !<VALUE> 0 0 0
          target: !<VALUE> 0 0 0
          projection: !<VALUE> 0
          up: !<VALUE> 0 1 0
          fovy: !<VALUE> 90.000000
        BoxSingleComponent: !<DICT>
          gravity: !<VALUE> 9.8
          air_drag_coefficient: !<VALUE> 0.3
    !<DICT>
      name: !<VALUE> character
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> DYNAMIC
        ModelComponent: !<VALUE> /cube.glb
        TransformComponent: !<DICT>
          translation: !<VALUE> 0 1 0
          scale: !<VALUE> 0.5 0.5 0.5
          rotation: !<VALUE> 0 0 0
        CharacterComponent: !<DICT>
          camera_follow_offset: !<VALUE> 3.000000
          camera_follow_distance: !<VALUE> 7.000000
        InputReceiverComponent: !<VALUE> RUNTIME
    !<DICT>
      name: !<VALUE> pillar_0
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        TransformComponent: !<DICT>
          translation: !<VALUE> 10 5 0
          scale: !<VALUE> 1 10 1
          rotation: !<VALUE> 0 0 0
    !<DICT>
      name: !<VALUE> pillar_1
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        TransformComponent: !<DICT>
          translation: !<VALUE> -10 5 0
          scale: !<VALUE> 1 10 1
          rotation: !<VALUE> 0 0 0
    !<DICT>
      name: !<VALUE> pillar_2
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        TransformComponent: !<DICT>
          translation: !<VALUE> 0 5 10
          scale: !<VALUE> 1 10 1
          rotation: !<VALUE> 0 0 0
    !<DICT>
      name: !<VALUE> pillar_3
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        TransformComponent: !<DICT>
          translation: !<VALUE> 0 5 -10
          scale: !<VALUE> 1 10 1
          rotation: !<VALUE> 0 0 0
    !<DICT>
      name: !<VALUE> floor
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        TransformComponent: !<DICT>
          translation: !<VALUE> 0 0 0
          scale: !<VALUE> 30 1 30
          rotation: !<VALUE> 0 0 0
    !<DICT>
      name: !<VALUE> tb_1
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> DYNAMIC
        TransformComponent: !<DICT>
          translation: !<VALUE> 0 5 0
          scale: !<VALUE> 3 3 3
          rotation: !<VALUE> 0 0 0
    !<DICT>
      name: !<VALUE> tb_2
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> DYNAMIC
        TransformComponent: !<DICT>
          translation: !<VALUE> 0 9 0
          scale: !<VALUE> 2 2 2
          rotation: !<VALUE> 0 0 0