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
        CameraComponent: !<DICT>
          fovy: !<VALUE> 90.000000
          position: !<VALUE> 7.358891487121582 4.958309173583984 6.925790786743164
          projection: !<VALUE> 0
          target: !<VALUE> 7.358891487121582 3.9583091735839844 6.925790786743164
          up: !<VALUE> 0.0 0.0 -1.0
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.483536034822464 0.33687159419059753 -0.20870360732078552 0.7804827094078064
          scale: !<VALUE> 0.0 0.0 0.0
          translation: !<VALUE> 7.358891487121582 4.958309173583984 6.925790786743164
      name: !<VALUE> Camera
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
          translation: !<VALUE> -5.921206138737034e-07 2.533938407897949 22.18668556213379
      name: !<VALUE> Man
    !<DICT>
      components: !<DICT>
        ModelComponent: !<VALUE> /models/switch/base.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 1.0 1.0 1.0
          translation: !<VALUE> 0.0 0.0 -0.0
      name: !<VALUE> OTB_base
    !<DICT>
      components: !<DICT>
        ModelComponent: !<VALUE> /models/lvl2/wire.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 1.0 1.0 1.0
          translation: !<VALUE> 0.0 0.0 -0.0
      name: !<VALUE> OTB_CORD
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> DYNAMIC
        ModelComponent: !<VALUE> /models/boxes/matches.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 4.90187406539917 1.4752453565597534 7.866957187652588
          translation: !<VALUE> -1.1034724712371826 1.0394484996795654 28.224214553833008
      name: !<VALUE> OTB_D_Cube
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> DYNAMIC
        ModelComponent: !<VALUE> /models/boxes/matches.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 4.90187406539917 1.5 7.866957187652588
          translation: !<VALUE> -27.714357376098633 2.289898157119751 -4.390817642211914
      name: !<VALUE> OTB_D_Cube.001
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> DYNAMIC
        ModelComponent: !<VALUE> /models/boxes/small_box.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 3.0 4.5 3.0
          translation: !<VALUE> -13.109856605529785 10.911173820495605 -1.091238260269165
      name: !<VALUE> OTB_D_Cube.002
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> DYNAMIC
        ModelComponent: !<VALUE> /models/boxes/matches.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 3.5878705978393555 1.5 5.3212666511535645
          translation: !<VALUE> 11.778280258178711 2.7616288661956787 -16.651287078857422
      name: !<VALUE> OTB_D_Cube.003
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> DYNAMIC
        ModelComponent: !<VALUE> /models/boxes/small_box.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 3.1506922245025635 2.0 2.985222578048706
          translation: !<VALUE> 21.16033172607422 8.654022216796875 -16.143898010253906
      name: !<VALUE> OTB_D_Cube.004
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> DYNAMIC
        ModelComponent: !<VALUE> /models/boxes/small_box.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 2.355715036392212 3.5 5.3212666511535645
          translation: !<VALUE> 0.6278378963470459 17.119264602661133 1.0114870071411133
      name: !<VALUE> OTB_D_Cube.005
    !<DICT>
      components: !<DICT>
        ModelComponent: !<VALUE> /models/fan.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 1.5454311608209537e-08 1.5454309831852697e-08 0.7071067094802856 0.7071068286895752
          scale: !<VALUE> 1.0634679794311523 4.776233196258545 4.776233196258545
          translation: !<VALUE> -11.830204010009766 1.9221932888031006 -23.570858001708984
      name: !<VALUE> OTB_Fan1_Actual
    !<DICT>
      components: !<DICT>
        ModelComponent: !<VALUE> /models/fan.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.7071068286895752 -0.0 0.7071067094802856
          scale: !<VALUE> 2.7193734645843506 10.023104667663574 10.023104667663574
          translation: !<VALUE> 11.450272560119629 6.493407249450684 12.271513938903809
      name: !<VALUE> OTB_Fan2_Actual
    !<DICT>
      components: !<DICT>
        ModelComponent: !<VALUE> /models/fan.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 1.5454311608209537e-08 1.5454309831852697e-08 0.7071067094802856 0.7071068286895752
          scale: !<VALUE> 1.0634679794311523 4.776233196258545 4.776233196258545
          translation: !<VALUE> 21.82823944091797 1.9114056825637817 26.056774139404297
      name: !<VALUE> OTB_Fan3_Actual
    !<DICT>
      components: !<DICT>
        EventTriggerComponent: !<VALUE> go_level.lvl4
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 5.18156623840332 5.425079822540283 5.640209197998047
          translation: !<VALUE> -20.309329986572266 22.451505661010742 -23.40315055847168
      name: !<VALUE> OTB_Finish
    !<DICT>
      components: !<DICT>
        ItemPickupComponent: !<VALUE> thread_n_needle
        ModelComponent: !<VALUE> /models/items/Needle_n_thread_icon.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 2.0 2.0 2.0
          translation: !<VALUE> -8.481849670410156 -1.4981775283813477 26.074331283569336
      name: !<VALUE> OTB_PICKUP_THREAD_N_NEEDLE
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        ModelComponent: !<VALUE> askdalksdjlkasjdlk
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 5.489627361297607 2.0 17.127792358398438
          translation: !<VALUE> 29.145593643188477 1.819007396697998 -17.85097312927246
      name: !<VALUE> OTB_S_base
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        ModelComponent: !<VALUE> /models/boxes/carton_box.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 43.48884963989258 3.6164968013763428 5.405669689178467
          translation: !<VALUE> -10.471124649047852 -0.6899298429489136 16.433303833007812
      name: !<VALUE> OTB_S_Cube
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        ModelComponent: !<VALUE> /models/boxes/carton_box.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 16.385650634765625 2.799999952316284 14.220690727233887
          translation: !<VALUE> 3.0886545181274414 -1.0981742143630981 26.24648666381836
      name: !<VALUE> OTB_S_Cube.001
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        ModelComponent: !<VALUE> /models/boxes/carton_box.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 27.198802947998047 8.871175765991211 5.405669689178467
          translation: !<VALUE> -2.401879072189331 5.553906440734863 16.295717239379883
      name: !<VALUE> OTB_S_Cube.002
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        ModelComponent: !<VALUE> /models/boxes/carton_box.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 16.090669631958008 3.299999952316284 5.405669689178467
          translation: !<VALUE> -24.1071720123291 2.7683169841766357 16.295717239379883
      name: !<VALUE> OTB_S_Cube.003
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        ModelComponent: !<VALUE> /models/boxes/carton_box.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 13.384998321533203 2.799999952316284 14.220690727233887
          translation: !<VALUE> -25.440385818481445 -1.0981775522232056 26.246484756469727
      name: !<VALUE> OTB_S_Cube.004
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        ModelComponent: !<VALUE> /models/boxes/carton_box.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 13.674839973449707 2.799999952316284 4.47540283203125
          translation: !<VALUE> -11.910998344421387 -1.0981775522232056 31.122970581054688
      name: !<VALUE> OTB_S_Cube.005
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        ModelComponent: !<VALUE> /models/boxes/carton_box.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 13.67056655883789 2.799999952316284 4.47540283203125
          translation: !<VALUE> -11.908863067626953 -1.0981742143630981 21.289459228515625
      name: !<VALUE> OTB_S_Cube.006
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        ModelComponent: !<VALUE> /models/boxes/outter_box2.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 64.16529846191406 3.616497039794922 59.58012390136719
          translation: !<VALUE> -0.016928672790527344 -4.306426048278809 3.566769599914551
      name: !<VALUE> OTB_S_Cube.007
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        ModelComponent: !<VALUE> /models/boxes/carton_box.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 5.622338771820068 6.0 17.06407928466797
          translation: !<VALUE> -13.17337703704834 4.379225254058838 -5.225949287414551
      name: !<VALUE> OTB_S_Cube.008
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        ModelComponent: !<VALUE> /models/boxes/kettle_box.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 17.871089935302734 18.620651245117188 12.641786575317383
          translation: !<VALUE> -23.19725799560547 10.428644180297852 -20.078882217407227
      name: !<VALUE> OTB_S_Cube.009
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        ModelComponent: !<VALUE> /models/boxes/helpfull_box.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 12.592639923095703 13.726179122924805 27.315637588500977
          translation: !<VALUE> -4.021785736083984 8.242317199707031 -0.06493616104125977
      name: !<VALUE> OTB_S_Cube.010
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        ModelComponent: !<VALUE> /models/boxes/spaghetti.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 2.8386056423187256 5.300000190734863 15.753560066223145
          translation: !<VALUE> 3.7032546997070312 4.0292253494262695 -18.2536563873291
      name: !<VALUE> OTB_S_Cube.011
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        ModelComponent: !<VALUE> /models/boxes/carton_box.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 2.277301788330078 2.5 4.6314005851745605
          translation: !<VALUE> 1.145309567451477 2.6292271614074707 -18.234926223754883
      name: !<VALUE> OTB_S_Cube.012
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        FanControlButtonComponent: !<DICT>
          animated_entities: !<VALUE> OTB_Fan2_Actual OTB_ZFan_2
          enabled: !<VALUE> True
          target_entity: !<VALUE> OTB_ZFan_2
        ModelComponent: !<VALUE> /models/switch/button.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 2.8386056423187256 1.222349762916565 2.596999406814575
          translation: !<VALUE> 29.404298782348633 2.5062012672424316 -18.098413467407227
      name: !<VALUE> OTB_S_Cube.013
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        ModelComponent: !<VALUE> /models/boxes/carton_box.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 4.604527950286865 6.0 29.949893951416016
          translation: !<VALUE> 21.324462890625 4.379220962524414 -11.155489921569824
      name: !<VALUE> OTB_S_Cube.014
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        ModelComponent: !<VALUE> /models/boxes/carton_box.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 7.714158058166504 12.377275466918945 19.752056121826172
          translation: !<VALUE> 15.054347038269043 3.8008570671081543 23.468910217285156
      name: !<VALUE> OTB_S_Cube.016
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        ModelComponent: !<VALUE> /models/boxes/carton_box.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 13.195989608764648 4.300000190734863 5.405669689178467
          translation: !<VALUE> 25.509418487548828 3.317549467086792 16.295717239379883
      name: !<VALUE> OTB_S_Cube.017
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        ModelComponent: !<VALUE> /models/boxes/carton_box.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 2.799999952316284 1.5809727907180786 3.200000047683716
          translation: !<VALUE> 29.423229217529297 2.1697115898132324 20.59855079650879
      name: !<VALUE> OTB_S_Cube.018
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        FanControlButtonComponent: !<DICT>
          animated_entities: !<VALUE> OTB_Fan3_Actual OTB_ZFan_3
          enabled: !<VALUE> False
          target_entity: !<VALUE> OTB_ZFan_3
        ModelComponent: !<VALUE> /models/switch/button.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 2.8386056423187256 1.222349762916565 2.596999406814575
          translation: !<VALUE> 29.404298782348633 2.4956393241882324 -12.929746627807617
      name: !<VALUE> OTB_S_Cube.019
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        FanControlButtonComponent: !<DICT>
          animated_entities: !<VALUE> OTB_Fan1_Actual OTB_ZFan_1
          enabled: !<VALUE> False
          target_entity: !<VALUE> OTB_ZFan_1
        ModelComponent: !<VALUE> /models/switch/button.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 2.8386056423187256 1.222349762916565 2.596999406814575
          translation: !<VALUE> 29.404298782348633 2.5344269275665283 -23.191722869873047
      name: !<VALUE> OTB_S_Cube.020
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 4.776233673095703 1.0634689331054688 4.776233196258545
          translation: !<VALUE> -11.830204010009766 1.9221932888031006 -23.570858001708984
      name: !<VALUE> OTB_S_Fan1_Collision
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 10.023104667663574 10.023104667663574 2.7193751335144043
          translation: !<VALUE> 11.450272560119629 6.493407249450684 12.271513938903809
      name: !<VALUE> OTB_S_Fan2_Collision
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 4.776233673095703 1.0634689331054688 4.776233196258545
          translation: !<VALUE> 21.82823944091797 1.9114056825637817 26.056774139404297
      name: !<VALUE> OTB_S_Fan3_Collision
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        ModelComponent: !<VALUE> /models/boxes/carton_box.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 64.27928161621094 0.26090753078460693 39.87057876586914
          translation: !<VALUE> 0.0 1.2487714290618896 -6.3853349685668945
      name: !<VALUE> OTB_S_Floor
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        ModelComponent: !<VALUE> /models/boxes/carton_box.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 13.222034454345703 0.26090753078460693 19.77829933166504
          translation: !<VALUE> 25.522445678710938 1.2487714290618896 23.439104080200195
      name: !<VALUE> OTB_S_Floor.001
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        ModelComponent: !<VALUE> /models/boxes/outter_box2.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 64.27928161621094 0.26090753078460693 59.93773651123047
          translation: !<VALUE> 0.0 39.16487121582031 3.648240327835083
      name: !<VALUE> OTB_S_Floor.002
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        ModelComponent: !<VALUE> /models/boxes/outter_box2.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 17.67894744873047 39.6783332824707 59.93773651123047
          translation: !<VALUE> 40.94187927246094 19.55443000793457 3.648240327835083
      name: !<VALUE> OTB_S_Floor.003
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        ModelComponent: !<VALUE> /models/boxes/outter_box2.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 19.153884887695312 39.6783332824707 59.93773651123047
          translation: !<VALUE> -41.69329833984375 19.55443000793457 3.648240327835083
      name: !<VALUE> OTB_S_Floor.004
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        ModelComponent: !<VALUE> /models/boxes/outter_box2.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 67.3547592163086 42.629302978515625 16.00344467163086
          translation: !<VALUE> -0.632573127746582 19.55443000793457 41.61882400512695
      name: !<VALUE> OTB_S_Floor.005
    !<DICT>
      components: !<DICT>
        BoxComponent: !<DICT>
          type: !<VALUE> STATIC
        ModelComponent: !<VALUE> /models/boxes/outter_box2.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.0 -0.0 1.0
          scale: !<VALUE> 67.3547592163086 42.629302978515625 17.577280044555664
          translation: !<VALUE> -0.6326074600219727 19.55443000793457 -35.10926055908203
      name: !<VALUE> OTB_S_Floor.006
    !<DICT>
      components: !<DICT>
        FanComponent: !<VALUE> 60.0
        ModelComponent: !<VALUE> /models/spiral.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.5000006556510925 0.5000005960464478 0.49999934434890747 0.49999937415122986
          scale: !<VALUE> 20.60651397705078 5.300000190734863 4.675706386566162
          translation: !<VALUE> -11.721636772155762 12.077731132507324 -23.430734634399414
      name: !<VALUE> OTB_ZFan_1
    !<DICT>
      components: !<DICT>
        FanComponent: !<VALUE> 12.0
        ModelComponent: !<VALUE> /models/spiral.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.0 0.7071068286895752 -0.0 0.7071067094802856
          scale: !<VALUE> 13.115518569946289 13.100000381469727 13.100000381469727
          translation: !<VALUE> 11.676254272460938 6.3644232749938965 4.551912784576416
      name: !<VALUE> OTB_ZFan_2
    !<DICT>
      components: !<DICT>
        FanComponent: !<VALUE> 60.0
        ModelComponent: !<VALUE> /models/spiral.glb
        TransformComponent: !<DICT>
          rotation: !<VALUE> 0.5000006556510925 0.5000005960464478 0.49999934434890747 0.49999937415122986
          scale: !<VALUE> 10.148107528686523 5.300000190734863 4.675706386566162
          translation: !<VALUE> 21.400217056274414 6.742220878601074 26.13370704650879
      name: !<VALUE> OTB_ZFan_3
