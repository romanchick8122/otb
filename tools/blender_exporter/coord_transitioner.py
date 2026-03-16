from mathutils import Vector

def blender_to_engine(input_vector):
    return Vector((input_vector.x, input_vector.z, -input_vector.y))

def engine_to_blender(input_vector):
    return Vector((input_vector.x, -input_vector.z, input_vector.y))

def vector_abs(input_vector):
    return Vector((abs(input_vector.x), abs(input_vector.y), abs(input_vector.z)))