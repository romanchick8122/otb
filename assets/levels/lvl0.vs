!<DICT>
  entities: !<ARRAY>
    !<DICT>
      components: !<DICT>
        BoxSingleComponent: !<DICT>
          air_drag_coefficient: !<VALUE> 0.9
          gravity: !<VALUE> 50
        CameraComponent: !<DICT>
          fovy: !<VALUE> 90.000000
          position: !<VALUE> 0 0 0
          projection: !<VALUE> 0
          target: !<VALUE> 0 0 0
          up: !<VALUE> 0 1 0
      name: !<VALUE> _world
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> DYNAMIC
        CharacterComponent: !<DICT>
          camera_follow_distance: !<VALUE> 7.000000
          camera_follow_offset: !<VALUE> 3.000000
        InputReceiverComponent: !<VALUE> RUNTIME
        ModelComponent: !<DICT>
          model_space_collider: !<DICT>
            rotation: !<VALUE> 0.0 0.0 0.0
            scale: !<VALUE> 0.28 0.67 0.28
            translation: !<VALUE> 0 -0.78175 0
          path: !<VALUE> /models/BuggyBug.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 3.3333001136779785 1.4919999837875366 3.3333001136779785
          translation: !<VALUE> 5.0183210372924805 2.1640355587005615 -10.711065292358398
      name: !<VALUE> Man
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> DYNAMIC
        ModelComponent: !<VALUE> /models/boxes/carton_box.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 3.0 2.799999952316284 3.0
          translation: !<VALUE> 0.7476077079772949 2.4000000953674316 1.4825825691223145
      name: !<VALUE> OTB_D_Box1
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> DYNAMIC
        ModelComponent: !<VALUE> /models/boxes/carton_box.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 2.0 2.799999952316284 2.0
          translation: !<VALUE> -11.694589614868164 11.0118408203125 -0.10886716842651367
      name: !<VALUE> OTB_D_Box2
    !<DICT>
      components: !<DICT>
        EventTriggerComponent: !<VALUE> go_level.lvl1
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 4.346735000610352 2.297194719314575 3.9993796348571777
          translation: !<VALUE> -12.826632499694824 14.148599624633789 11.875978469848633
      name: !<VALUE> OTB_Finish
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        ModelComponent: !<VALUE> /models/boxes/carton_box.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 7.0 12.0 7.0
          translation: !<VALUE> -11.5 7.0 11.5
      name: !<VALUE> OTB_S_Box1
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        ModelComponent: !<VALUE> /models/boxes/carton_box.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 7.0 8.399999618530273 7.0
          translation: !<VALUE> -11.5 5.199997901916504 -2.555440902709961
      name: !<VALUE> OTB_S_Box2
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        ModelComponent: !<VALUE> /models/boxes/carton_box.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 7.0 5.599999904632568 7.0
          translation: !<VALUE> -11.5 3.8000001907348633 -11.5
      name: !<VALUE> OTB_S_Box3
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        ModelComponent: !<VALUE> /models/boxes/carton_box.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 7.0 6.918736457824707 7.0
          translation: !<VALUE> -11.5 4.459368705749512 4.484895706176758
      name: !<VALUE> OTB_S_Box4
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        ModelComponent: !<VALUE> /models/boxes/carton_box.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 24.430700302124023 2.0 30.0
          translation: !<VALUE> -2.7846455574035645 20.0 -0.0
      name: !<VALUE> OTB_S_Ceiling
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        ModelComponent: !<VALUE> /models/boxes/carton_box.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 24.430700302124023 2.0 30.0
          translation: !<VALUE> -2.7846453189849854 0.0 -0.0
      name: !<VALUE> OTB_S_Floor
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        ModelComponent: !<VALUE> /models/boxes/carton_box.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 10.0 20.0 30.0
          translation: !<VALUE> -20.0 9.0 -1.9073486328125e-06
      name: !<VALUE> OTB_S_Wall
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        ModelComponent: !<VALUE> /models/boxes/carton_box.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 10.0 20.0 30.0
          translation: !<VALUE> 14.430700302124023 9.0 -1.9073486328125e-06
      name: !<VALUE> OTB_S_Wall.001
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        ModelComponent: !<VALUE> /models/boxes/carton_box.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 30.0 20.0 20.0
          translation: !<VALUE> -2.786472797393799 9.0 -25.0
      name: !<VALUE> OTB_S_Wall.002
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        ModelComponent: !<VALUE> /models/boxes/carton_box.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 30.0 20.0 20.0
          translation: !<VALUE> -2.7864725589752197 9.0 25.0
      name: !<VALUE> OTB_S_Wall.003
