#pragma once

#include "core/asset/value_storage.h"

#include "raylib.h"

namespace otb
{
struct ValueStorageUtils
{
    static ValueStorage serialize(bool);
    static ValueStorage serialize(int);
    static ValueStorage serialize(float);
    static ValueStorage serialize(Vector3);
    static ValueStorage serialize(Quaternion);
    static ValueStorage serialize(const Transform&);

    template<class T>
    static T deserialize(const ValueStorage&);

    template<> bool deserialize<bool>(const ValueStorage&);
    template<> int deserialize<int>(const ValueStorage&);
    template<> float deserialize<float>(const ValueStorage&);
    template<> Vector3 deserialize<Vector3>(const ValueStorage&);
    template<> Quaternion deserialize<Quaternion>(const ValueStorage&);
    template<> Transform deserialize<Transform>(const ValueStorage&);
};
}