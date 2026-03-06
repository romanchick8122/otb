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
    !<DICT>
      name: !<VALUE> character
      components: !<DICT>
        ModelComponent: !<VALUE> /cube.glb
        TransformComponent: !<DICT>
          translation: !<VALUE> 0 1 0
          scale: !<VALUE> 0.1 0.1 0.1
          rotation: !<VALUE> 0 0 0
        CharacterComponent: !<DICT>
          camera_follow_offset: !<VALUE> 3.000000
          camera_follow_distance: !<VALUE> 7.000000
        InputReceiverComponent: !<VALUE> RUNTIME
    !<DICT>
      name: !<VALUE> pillar_0
      components: !<DICT>
        ModelComponent: !<VALUE> /cube.glb
        TransformComponent: !<DICT>
          translation: !<VALUE> 10 0 0
          scale: !<VALUE> 1 10 1
          rotation: !<VALUE> 0 0 0
    !<DICT>
      name: !<VALUE> pillar_1
      components: !<DICT>
        ModelComponent: !<VALUE> /cube.glb
        TransformComponent: !<DICT>
          translation: !<VALUE> -10 0 0
          scale: !<VALUE> 1 10 1
          rotation: !<VALUE> 0 0 0
    !<DICT>
      name: !<VALUE> pillar_2
      components: !<DICT>
        ModelComponent: !<VALUE> /cube.glb
        TransformComponent: !<DICT>
          translation: !<VALUE> 0 0 10
          scale: !<VALUE> 1 10 1
          rotation: !<VALUE> 0 0 0
    !<DICT>
      name: !<VALUE> pillar_3
      components: !<DICT>
        ModelComponent: !<VALUE> /cube.glb
        TransformComponent: !<DICT>
          translation: !<VALUE> 0 0 -10
          scale: !<VALUE> 1 10 1
          rotation: !<VALUE> 0 0 0
    !<DICT>
      name: !<VALUE> floor
      components: !<DICT>
        SurfaceComponent: !<DICT>
          asset_path: !<VALUE> /white.png
        TransformComponent: !<DICT>
          translation: !<VALUE> 0 0 0
          scale: !<VALUE> 30 1 30
          rotation: !<VALUE> 0 0 0