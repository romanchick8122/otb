import bpy
from .vs import save,load
from .exporter import OTBWorldExportOperator
from .importer import OTBWorldImportOperator
bl_info = {
    "name": "OTB World exporter2",
    "category": "Object",
}
def menu_func_exporter(self, context):
    layout = self.layout
    layout.separator()
    layout.operator(OTBWorldExportOperator.bl_idname)

def menu_func_importer(self, context):
    layout = self.layout
    layout.separator()
    layout.operator(OTBWorldImportOperator.bl_idname)
    
def register():
    bpy.utils.register_class(OTBWorldExportOperator)
    bpy.types.TOPBAR_MT_file_export.append(menu_func_exporter)
    bpy.utils.register_class(OTBWorldImportOperator)
    bpy.types.TOPBAR_MT_file_import.append(menu_func_importer)

def unregister():
    bpy.utils.unregister_class(OTBWorldExportOperator)
    bpy.types.TOPBAR_MT_file_export.remove(menu_func_exporter)
    bpy.utils.unregister_class(OTBWorldImportOperator)
    bpy.types.TOPBAR_MT_file_import.remove(menu_func_importer)

if __name__ == "__main__":
    register()