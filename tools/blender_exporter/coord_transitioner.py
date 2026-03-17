from mathutils import Vector, Quaternion

def blender_to_engine(input_vector):
    return Vector((input_vector.x, input_vector.z, -input_vector.y))

def engine_to_blender(input_vector):
    return Vector((input_vector.x, -input_vector.z, input_vector.y))

def quaternion_blender_to_engine(quaternion_b):
    return (quaternion_b.x, quaternion_b.z, -quaternion_b.y, quaternion_b.w)

def quaternion_engine_to_blender(vector_e):
    return Quaternion((vector_e[3], vector_e[0], -vector_e[2], vector_e[1]))

def vector_abs(input_vector):
    return Vector((abs(input_vector.x), abs(input_vector.y), abs(input_vector.z)))