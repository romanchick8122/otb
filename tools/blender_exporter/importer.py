import bpy
from .vs import save,load
from bpy_extras.io_utils import ImportHelper

class OTBWorldImportOperator(bpy.types.Operator, ImportHelper):
    bl_idname = "otb.world_import"
    bl_label = "OTB World Import"
    bl_options = {'REGISTER', 'UNDO'}
    filename_ext = ".vs"
    def execute(self, context):
        World = load(self.filepath)
        for obj in World["entities"]:
            if obj != World["entities"][0]:
                translation = obj["components"]["TransformComponent"]["translation"].split()
                scale = obj["components"]["TransformComponent"]["scale"].split()
                rotation = obj["components"]["TransformComponent"]["rotation"].split()
                bpy.ops.mesh.primitive_cube_add(
                    location = (-float(translation[0]),float(translation[2]),float(translation[1])),
                    scale = (float(scale[0])/2, float(scale[2])/2, float(scale[1])/2),
                    rotation = (float(rotation[0]), float(rotation[2]), float(rotation[1]))
                )     
                context.object["model"] = obj["components"]["ModelComponent"]
                context.object.name = obj["name"]
        print(World)
        return {'FINISHED'}