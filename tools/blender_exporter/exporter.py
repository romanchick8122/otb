import bpy
from .vs import save
from bpy_extras.io_utils import ExportHelper
from .coord_transitioner import blender_to_engine, quaternion_blender_to_engine, vector_abs, engine_to_blender
from mathutils import Vector

class OTBWorldExportOperator(bpy.types.Operator, ExportHelper):
    bl_idname = "otb.world_export"
    bl_label = "OTB World Export"
    bl_options = {'REGISTER', 'UNDO'}
    filename_ext = ".vs"

    def execute(self, context):
        def get_extra_components(obj):
            result = {}
            if "model" in obj:
                result["ModelComponent"] = obj["model"]
            if "fan_power" in obj:
                result["FanComponent"] = str(obj["fan_power"])
            if "fan_control_button_for" in obj:
                result["FanControlButtonComponent"] = {
                    "target_entity": obj["fan_control_button_for"],
                    "enabled": str(obj["fan_control_button_state"]),
                    "animated_entities": obj["fan_control_animated_entities"],
                }
            return result

        def add_transfrom_component(obj, dimensions):
            components = get_extra_components(obj)
            translation = blender_to_engine(obj.location)
            rotation = quaternion_blender_to_engine(obj.rotation_euler.to_quaternion())
            print(rotation)
            scale = vector_abs(blender_to_engine(dimensions))
            components["TransformComponent"] = {
                "translation": f"{translation.x} {translation.y} {translation.z}",
                "rotation": f"{rotation[0]} {rotation[1]} {rotation[2]} {rotation[3]}",
                "scale": f"{scale.x} {scale.y} {scale.z}"
            }
            return components
        def add_char_components(obj):
            character_dimensions = engine_to_blender(Vector((3.3333001136779785, 1.4919999837875366, 3.3333001136779785)))
            components = add_transfrom_component(obj, character_dimensions)
            components["BoxComponent"] = {"type":"DYNAMIC"}
            components["ModelComponent"] = {
                "path":"/models/BuggyBug.glb",
                "model_space_collider":{
                    "translation": "0 -0.78175 0",
                    "rotation": "0.0 0.0 0.0",
                    "scale": "0.28 0.67 0.28"
                }
            }
            components["CharacterComponent"] = {
                "camera_follow_offset":"3.000000",
                "camera_follow_distance":"7.000000"
            }
            components["InputReceiverComponent"] = "RUNTIME"
            return components
        def add_box_components(obj):
            components = add_transfrom_component(obj, obj.dimensions)
            if obj.name[4] == "S":
                components["BoxComponent"] = {"type":"STATIC"}
            elif obj.name[4] == "D":
                components["BoxComponent"] = {"type":"DYNAMIC"}
            return components
        def add_camera_component(obj):
            components = add_transfrom_component(obj, obj.dimensions)
            target = blender_to_engine(obj.rotation_quaternion @ Vector((0,0,-1)) + obj.location)
            up = blender_to_engine(obj.rotation_quaternion @ Vector((0,1,0)))
            position = blender_to_engine(obj.location)
            components["CameraComponent"] = {
                "fovy":"90.000000",
                "position":f"{position.x} {position.y} {position.z}",
                "projection":"0",
                "target":f"{target.x} {target.y} {target.z}",
                "up":f"{up.x} {up.y} {up.z}"
            }
            return components
        
        
        World = {"entities":[]}
        if bpy.context.scene.get("_world") is not None:
            World["entities"].append({
                "name": "_world",
                "components": bpy.context.scene["_world"].to_dict()
            })
        else:
            World["entities"].append({
            "name": "_world",
            "components":{
                "CameraComponent":{
                    "position": "0 0 0",
                    "target": "0 0 0",
                    "projection": "0",
                    "up": "0 1 0",
                    "fovy": "90.000000"
                },
                "BoxSingleComponent":{
                    "gravity": "9.8",
                    "air_drag_coefficient": "0.3"
                }
            }
            })
        
        for obj in bpy.data.objects:
            c = {
                "object":obj,
                "selected_objects":list(bpy.data.objects),
                "selected_editable_objects":list(bpy.data.objects)
            }
            with bpy.context.temp_override(**c):
                bpy.ops.object.origin_set(type="ORIGIN_GEOMETRY")
            if obj.name[:3] == "OTB":
                World["entities"].append({"name":obj.name, "components": add_box_components(obj)})
            elif obj.name.lower() == "man": 
                World["entities"].append({"name":obj.name, "components": add_char_components(obj)})
            elif obj.type == "CAMERA":
                World["entities"].append({"name":obj.name, "components": add_camera_component(obj)})
        save(World,self.filepath)
        return {'FINISHED'}