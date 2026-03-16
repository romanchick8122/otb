import bpy
from .vs import load
from bpy_extras.io_utils import ImportHelper
from .coord_transitioner import engine_to_blender, vector_abs
from mathutils import Vector

class OTBWorldImportOperator(bpy.types.Operator, ImportHelper):
    bl_idname = "otb.world_import"
    bl_label = "OTB World Import"
    bl_options = {'REGISTER', 'UNDO'}
    filename_ext = ".vs"
    def execute(self, context):
        World = load(self.filepath)
        bpy.context.scene["_world"] = World["entities"][0]["components"]
        for obj in World["entities"]:
            if obj != World["entities"][0]:
                if obj["name"].lower() == "man":
                    translation_str = obj["components"]["TransformComponent"]["translation"].split()
                    translation = engine_to_blender(Vector((float(translation_str[0]), float(translation_str[1]), float(translation_str[2]))))
                    bpy.ops.mesh.primitive_ico_sphere_add(
                        location = translation,
                    )
                elif "CameraComponent" in obj["components"]:
                    translation_str = obj["components"]["TransformComponent"]["translation"].split()
                    translation = engine_to_blender(Vector((float(translation_str[0]), float(translation_str[1]), float(translation_str[2]))))
                    rotation_str = obj["components"]["TransformComponent"]["rotation"].split()
                    rotation = engine_to_blender(Vector((float(rotation_str[0]), float(rotation_str[1]), float(rotation_str[2]))))
                    bpy.ops.object.camera_add(
                        location = translation,
                        rotation = rotation
                    )
                else:
                    translation_str = obj["components"]["TransformComponent"]["translation"].split()
                    translation = engine_to_blender(Vector((float(translation_str[0]), float(translation_str[1]), float(translation_str[2]))))
                    rotation_str = obj["components"]["TransformComponent"]["rotation"].split()
                    rotation = engine_to_blender(Vector((float(rotation_str[0]), float(rotation_str[1]), float(rotation_str[2]))))
                    scale_str = obj["components"]["TransformComponent"]["scale"].split()
                    scale = vector_abs(engine_to_blender(Vector((float(scale_str[0])/2, float(scale_str[1])/2, float(scale_str[2])/2))))
                    bpy.ops.mesh.primitive_cube_add(
                    location = translation,
                    scale = scale,
                    rotation = rotation
                    )     
                context.object["model"] = obj["components"]["ModelComponent"]
                context.object.name = obj["name"]
        return {'FINISHED'}