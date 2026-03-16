import bpy
from .vs import save,load
from bpy_extras.io_utils import ExportHelper

class OTBWorldExportOperator(bpy.types.Operator, ExportHelper):
    bl_idname = "otb.world_export"
    bl_label = "OTB World Export"
    bl_options = {'REGISTER', 'UNDO'}
    filename_ext = ".vs"

    def execute(self, context):
        def add_transfrom_component(obj):
            components = {}
            components["TransformComponent"] = {
                "translation": f"{-obj.location.x} {obj.location.z} {obj.location.y}",
                "rotation": f"{obj.rotation_euler.x} {obj.rotation_euler.z} {obj.rotation_euler.y}",
                "scale": f"{obj.dimensions.x} {obj.dimensions.z} {obj.dimensions.y}"
            }
            return components
        def add_char_components(obj):
            components = {}
            components["TransformComponent"] = {
                "translation": f"{-obj.location.x} {obj.location.z} {obj.location.y}",
                "rotation": f"{obj.rotation_euler.x} {obj.rotation_euler.z} {obj.rotation_euler.y}",
                "scale": "3.3333001136779785 1.4919999837875366 3.3333001136779785"
            }
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
            components = add_transfrom_component(obj)
            if obj.name[4] == "S":
                components["BoxComponent"] = {"type":"STATIC"}
            else: components["BoxComponent"] = {"type":"DYNAMIC"}
            if obj.get("model") is None:
                components["ModelComponent"] = "/cube.glb"
            else: components["ModelComponent"] = obj.get("model")
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
            with bpy.context.temp_override(object=obj):
                bpy.ops.object.origin_set(type="ORIGIN_GEOMETRY")
            if obj.name[:3] == "OTB":
                World["entities"].append({"name":obj.name, "components": add_box_components(obj)})
            elif obj.name.lower() == "man": 
               World["entities"].append({"name":obj.name, "components": add_char_components(obj)})       
        save(World,self.filepath)
        return {'FINISHED'}