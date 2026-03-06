#pragma once

#include "core/asset/value_storage.h"

#include "raylib.h"

namespace otb
{
struct ValueStorageUtils
{
    static ValueStorage serialize(int);
    static ValueStorage serialize(float);
    static ValueStorage serialize(Vector3);

    template<class T>
    static T deserialize(const ValueStorage&);

    template<> int deserialize<int>(const ValueStorage&);
    template<> float deserialize<float>(const ValueStorage&);
    template<> Vector3 deserialize<Vector3>(const ValueStorage&);
};
}