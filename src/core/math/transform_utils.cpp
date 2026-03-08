#include "transform_utils.h"

#include "core/assert.h"

#include "raymath.h"

namespace otb
{
Matrix TransformUtils::get_transform_matrix(const Transform& transform)
{
    Vector3 x = Vector3RotateByQuaternion(Vector3{transform.scale.x, 0, 0}, transform.rotation);
    Vector3 y = Vector3RotateByQuaternion(Vector3{0, transform.scale.y, 0}, transform.rotation);
    Vector3 z = Vector3RotateByQuaternion(Vector3{0, 0, transform.scale.z}, transform.rotation);

    const Vector3& t = transform.translation;
    
    return Matrix
    {
        x.x, y.x, z.x, t.x,
        x.y, y.y, z.y, t.y,
        x.z, y.z, z.z, t.z,
        0, 0, 0, 1
    };
}

Vector3 TransformUtils::apply_transform(const Transform& transform, const Vector3& point)
{
    return transform.translation + Vector3RotateByQuaternion(Vector3Multiply(point, transform.scale), transform.rotation);
}

Vector3 TransformUtils::apply_inverse_transform(const Transform& transform, const Vector3& point)
{
    return Vector3Divide(Vector3RotateByQuaternion((point - transform.translation), QuaternionInvert(transform.rotation)), transform.scale);
}

BoundingBox TransformUtils::get_box(const Transform& transform)
{
    OTB_ASSERT(transform.rotation == QuaternionIdentity());
    return {
        transform.translation - transform.scale / 2.f,
        transform.translation + transform.scale / 2.f,
    };
}
}