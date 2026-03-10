import bpy
from bpy.props import StringProperty
from bpy_extras.io_utils import ExportHelper
from bpy.types import Operator

bl_info = {
    "name": "OTB World exporter",
    "category": "Object",
}

class OTBWorldExportOperator(bpy.types.Operator, ExportHelper):
    bl_idname = "otb.world_export"
    bl_label = "OTB World Export"
    bl_options = {'REGISTER', 'UNDO'}
    filename_ext = ".vs"

    def execute(self, context):
        def write_entity_header(f, name):
            f.write(f"    !<DICT>\n")
            f.write(f"      name: !<VALUE> {name}\n")
            f.write(f"      components: !<DICT>\n")
        def write_box_component(f, type_letter):
            type = "STATIC" if type_letter == "S" else "DYNAMIC"
            f.write(f"        BoxComponent: !<DICT>\n")
            f.write(f"          type: !<VALUE> {type}\n")
        def write_transform(f, obj):
            f.write(f"        TransformComponent: !<DICT>\n")
            f.write(f"          translation: !<VALUE> {obj.location.x} {obj.location.z} {obj.location.y}\n")
            f.write(f"          rotation: !<VALUE> {obj.rotation_euler.x} {obj.rotation_euler.z} {obj.rotation_euler.y}\n")
            f.write(f"          scale: !<VALUE> {abs(obj.scale.x * 2)} {abs(obj.scale.z * 2)} {abs(obj.scale.y * 2)}\n")
        with open(self.filepath, "w") as f:
            for obj in bpy.data.objects:
                if obj.name[:4] == "OTB_":
                    write_entity_header(f, obj.name[6:])
                    write_box_component(f, obj.name[4])
                    write_transform(f, obj)
        
        return {'FINISHED'}

def menu_func(self, context):
    layout = self.layout
    layout.separator()
    layout.operator(OTBWorldExportOperator.bl_idname)

def register():
    bpy.utils.register_class(OTBWorldExportOperator)
    bpy.types.TOPBAR_MT_file_export.append(menu_func)

def unregister():
    bpy.utils.unregister_class(OTBWorldExportOperator)
    bpy.types.TOPBAR_MT_file_export.remove(menu_func)

if __name__ == "__main__":
    register()