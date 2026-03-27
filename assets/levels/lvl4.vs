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
          translation: !<VALUE> 12.006189346313477 10.940571784973145 -4.048144340515137
      name: !<VALUE> Man
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> DYNAMIC
        ModelComponent: !<VALUE> /models/boxes/carton_box.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 3.231015682220459 5.5 3.075855255126953
          translation: !<VALUE> 9.055551528930664 2.9939005374908447 11.49050521850586
      name: !<VALUE> OTB_D_Box
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> DYNAMIC
        ModelComponent: !<VALUE> /models/boxes/carton_box.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 3.231015682220459 2.5 3.075855255126953
          translation: !<VALUE> -32.47251510620117 1.344986915588379 16.89499282836914
      name: !<VALUE> OTB_D_Box.001
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> DYNAMIC
        ModelComponent: !<VALUE> /models/boxes/carton_box.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 3.231015682220459 0.5 3.075855255126953
          translation: !<VALUE> -11.880402565002441 0.34498703479766846 -5.394243240356445
      name: !<VALUE> OTB_D_Box.002
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> DYNAMIC
        ModelComponent: !<VALUE> /models/boxes/carton_box.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 2.674008369445801 2.75 3.075855255126953
          translation: !<VALUE> 1.357945442199707 15.480210304260254 -12.7822904586792
      name: !<VALUE> OTB_D_Box.003
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> DYNAMIC
        ModelComponent: !<VALUE> /models/boxes/carton_box.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 2.674008369445801 4.834209442138672 3.075855255126953
          translation: !<VALUE> 11.572920799255371 9.09100341796875 -16.18593978881836
      name: !<VALUE> OTB_D_Box.004
    !<DICT>
      components: !<DICT>
        ModelComponent: !<VALUE> /models/fan.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 1.8709033727645874 6.3256120681762695 6.7406182289123535
          translation: !<VALUE> -16.584392547607422 11.702363967895508 -2.5549261569976807
      name: !<VALUE> OTB_Fan1_Actual
    !<DICT>
      components: !<DICT>
        FanControlButtonComponent: !<DICT>
          animated_entities: !<VALUE> OTB_xFan1 OTB_Fan1_Actual
          enabled: !<VALUE> True
          target_entity: !<VALUE> OTB_xFan1
        ModelComponent: !<VALUE> /models/switch/button.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 0.8631871938705444 0.4535040259361267 0.557965099811554
          translation: !<VALUE> -42.20452117919922 17.295482635498047 -0.3177640438079834
      name: !<VALUE> OTB_Fan1_Button
    !<DICT>
      components: !<DICT>
        ModelComponent: !<VALUE> /models/fan.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 0.13052621483802795 0.9914448857307434
          scale: !<VALUE> 1.4493969678878784 4.900479793548584 5.221986770629883
          translation: !<VALUE> -38.13760757446289 8.155942916870117 -20.054723739624023
      name: !<VALUE> OTB_Fan2_Actual
    !<DICT>
      components: !<DICT>
        FanControlButtonComponent: !<DICT>
          animated_entities: !<VALUE> OTB_xFan2 OTB_Fan2_Actual
          enabled: !<VALUE> True
          target_entity: !<VALUE> OTB_xFan2
        ModelComponent: !<VALUE> /models/switch/button.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 0.8631871938705444 0.4535040259361267 0.557965099811554
          translation: !<VALUE> -42.20452117919922 17.295482635498047 0.7131295204162598
      name: !<VALUE> OTB_Fan2_Button
    !<DICT>
      components: !<DICT>
        ItemPickupComponent: !<VALUE> thread_n_needle
        ModelComponent: !<VALUE> /models/items/Needle_n_thread_icon.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 1.0085322856903076 0.9877188801765442 0.9601003527641296
          translation: !<VALUE> 3.7869834899902344 1.1004011631011963 7.04731559753418
      name: !<VALUE> OTB_Needle
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        ModelComponent: !<VALUE> /models/boxes/carton_box.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 21.92780113220215 8.471443176269531 6.424413681030273
          translation: !<VALUE> 5.666448593139648 4.330707550048828 -4.6482977867126465
      name: !<VALUE> OTB_S_Box
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        ModelComponent: !<VALUE> /models/boxes/carton_box.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 3.231015682220459 2.799999952316284 3.075855255126953
          translation: !<VALUE> 9.006623268127441 1.344986915588379 0.10725367069244385
      name: !<VALUE> OTB_S_Box.001
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        ModelComponent: !<VALUE> /models/boxes/carton_box.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 3.0110361576080322 7.858946323394775 20.59052848815918
          translation: !<VALUE> -3.791934013366699 4.024458885192871 8.859171867370605
      name: !<VALUE> OTB_S_Box.002
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        ModelComponent: !<VALUE> /models/boxes/carton_box.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 28.826663970947266 8.320433616638184 7.87945032119751
          translation: !<VALUE> -28.459815979003906 4.255202293395996 -2.4017975330352783
      name: !<VALUE> OTB_S_Box.003
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        ModelComponent: !<VALUE> /models/boxes/carton_box.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 3.0110361576080322 5.0 12.892623901367188
          translation: !<VALUE> -32.70267105102539 2.5949857234954834 7.9842376708984375
      name: !<VALUE> OTB_S_Box.004
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        ModelComponent: !<VALUE> /models/boxes/carton_box.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 24.905960083007812 8.57284164428711 3.2363955974578857
          translation: !<VALUE> -30.420166015625 12.706816673278809 -0.08027022331953049
      name: !<VALUE> OTB_S_Box.005
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        ModelComponent: !<VALUE> /models/boxes/carton_box.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 9.938597679138184 0.15745225548744202 4.0725226402282715
          translation: !<VALUE> -9.7813138961792 8.537200927734375 -4.158041000366211
      name: !<VALUE> OTB_S_Box.006
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        ModelComponent: !<VALUE> /models/boxes/carton_box.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 21.85773468017578 13.68111515045166 6.424413681030273
          translation: !<VALUE> 5.631415367126465 6.935544490814209 -11.089676856994629
      name: !<VALUE> OTB_S_Box.007
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        ModelComponent: !<VALUE> /models/boxes/carton_box.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 21.796831130981445 6.0 8.464152336120605
          translation: !<VALUE> 5.600963592529297 3.0949881076812744 -18.533958435058594
      name: !<VALUE> OTB_S_Box.008
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        ModelComponent: !<VALUE> /models/boxes/carton_box.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 13.320640563964844 5.5 5.265643119812012
          translation: !<VALUE> -36.065956115722656 2.844986915588379 -20.136438369750977
      name: !<VALUE> OTB_S_Box.009
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        ModelComponent: !<VALUE> /models/boxes/carton_box.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 13.320640563964844 3.0 2.7106542587280273
          translation: !<VALUE> -36.065956115722656 1.5949846506118774 -16.148290634155273
      name: !<VALUE> OTB_S_Box.010
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        EventTriggerComponent: !<VALUE> go_main_menu
        ModelComponent: !<VALUE> /models/boxes/carton_box.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 4.6187825202941895 2.5611724853515625 3.2363955974578857
          translation: !<VALUE> -40.56375503540039 9.725059509277344 -3.988650321960449
      name: !<VALUE> OTB_S_Box.011
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        ModelComponent: !<VALUE> /models/boxes/carton_box.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 55.8302116394043 0.15059685707092285 41.280025482177734
          translation: !<VALUE> -17.26849365234375 24.213003158569336 -4.9206695556640625
      name: !<VALUE> OTB_S_Ceiling
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        ModelComponent: !<VALUE> /models/boxes/carton_box.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 31.002225875854492 0.15059685707092285 42.2066535949707
          translation: !<VALUE> 1.222685694694519 0.01968848705291748 -1.7703876495361328
      name: !<VALUE> OTB_S_Floor
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        ModelComponent: !<VALUE> /models/boxes/carton_box.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 7.268657684326172 0.15059685707092285 22.53978157043457
          translation: !<VALUE> -17.91287612915039 0.01968848705291748 -11.58598518371582
      name: !<VALUE> OTB_S_Floor.002
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        ModelComponent: !<VALUE> /models/boxes/carton_box.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 21.210433959960938 0.15059685707092285 42.29644775390625
          translation: !<VALUE> -32.169677734375 0.01968848705291748 -1.6517560482025146
      name: !<VALUE> OTB_S_Floor.003
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        ModelComponent: !<VALUE> /models/boxes/carton_box.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 7.268657684326172 0.15059685707092285 19.748554229736328
          translation: !<VALUE> -17.91287612915039 0.01968848705291748 9.558182716369629
      name: !<VALUE> OTB_S_Sandpaper
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        ModelComponent: !<VALUE> /models/boxes/carton_box.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 59.712677001953125 25.137704849243164 9.942203521728516
          translation: !<VALUE> -13.237176895141602 11.568852424621582 24.30405044555664
      name: !<VALUE> OTB_S_Wall
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        ModelComponent: !<VALUE> /models/boxes/carton_box.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 59.788719177246094 25.137704849243164 9.942203521728516
          translation: !<VALUE> -13.199153900146484 11.568852424621582 -27.844816207885742
      name: !<VALUE> OTB_S_Wall.001
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        ModelComponent: !<VALUE> /models/boxes/carton_box.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 10.0 25.137704849243164 54.5
          translation: !<VALUE> -47.774898529052734 11.566166877746582 -5.490234375
      name: !<VALUE> OTB_S_Wall.002
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        ModelComponent: !<VALUE> /models/boxes/carton_box.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 10.0 25.137704849243164 54.5
          translation: !<VALUE> 21.723743438720703 11.566166877746582 -5.490234375
      name: !<VALUE> OTB_S_Wall.003
    !<DICT>
      components: !<DICT>
        FanComponent: !<VALUE> 12.0
        ModelComponent: !<VALUE> /models/spiral.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 17.620132446289062 6.138115882873535 13.734235763549805
          translation: !<VALUE> -6.521272659301758 11.930313110351562 -2.3967926502227783
      name: !<VALUE> OTB_xFan1
    !<DICT>
      components: !<DICT>
        FanComponent: !<VALUE> 30.0
        ModelComponent: !<VALUE> /models/spiral.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 0.13052621483802795 0.9914448857307434
          scale: !<VALUE> 28.092327117919922 6.50343656539917 5.014664173126221
          translation: !<VALUE> -23.942707061767578 11.900429725646973 -19.8521785736084
      name: !<VALUE> OTB_xFan2
