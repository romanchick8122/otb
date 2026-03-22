import bpy
from .vs import load
from bpy_extras.io_utils import ImportHelper
from .coord_transitioner import engine_to_blender, quaternion_engine_to_blender, vector_abs
from mathutils import Vector, Quaternion

class OTBWorldImportOperator(bpy.types.Operator, ImportHelper):
    bl_idname = "otb.world_import"
    bl_label = "OTB World Import"
    bl_options = {'REGISTER', 'UNDO'}
    filename_ext = ".vs"
    def execute(self, context):
        def get_transform(obj: dict, use_scale: bool)->dict:
            transform_component: dict = obj["components"]["TransformComponent"]
            translation = engine_to_blender(Vector(tuple(map(float, transform_component["translation"].split()))))
            rotation = quaternion_engine_to_blender(tuple(map(float, transform_component["rotation"].split())))
            result = {
                "location": translation,
                "rotation": rotation.to_euler()
            }
            if use_scale:
                result["scale"] = vector_abs(engine_to_blender(Vector(tuple(map(lambda x: float(x) / 2, transform_component["scale"].split())))))
            return result

        def load_extra_components(components: dict):
            if "ModelComponent" in components:
                context.object["model"] = components["ModelComponent"]
            if "FanComponent" in components:
                context.object["fan_power"] = float(components["FanComponent"])
            if "FanControlButtonComponent" in components:
                context.object["fan_control_button_for"] = components["FanControlButtonComponent"]["target_entity"]
                context.object["fan_control_button_state"] = components["FanControlButtonComponent"]["enabled"] == "True"
                context.object["fan_control_animated_entities"] = components["FanControlButtonComponent"]["animated_entities"]
            if "ItemPickupComponent" in components:
                context.object["item_pickup"] = components["ItemPickupComponent"]

        World = load(self.filepath)
        bpy.context.scene["_world"] = World["entities"][0]["components"]
        for obj in World["entities"]:
            if obj != World["entities"][0]:
                if obj["name"].lower() == "man":
                    bpy.ops.mesh.primitive_ico_sphere_add(**get_transform(obj, False))
                elif "CameraComponent" in obj["components"]:
                    bpy.ops.object.camera_add(**get_transform(obj, False))
                else:
                    bpy.ops.mesh.primitive_cube_add(**get_transform(obj, True))     
                load_extra_components(obj["components"])
                context.object.name = obj["name"]
        return {'FINISHED'}