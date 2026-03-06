#include "value_storage_utils.h"

#include "core/assert.h"

namespace otb
{
ValueStorage ValueStorageUtils::serialize(int v)
{
    return std::to_string(v);
}

ValueStorage ValueStorageUtils::serialize(float v)
{
    return std::to_string(v);
}

ValueStorage ValueStorageUtils::serialize(Vector3 v)
{
    return ValueStorage::ArrayType{{ serialize(v.x), serialize(v.y), serialize(v.z) }};
}

template<> int ValueStorageUtils::deserialize<int>(const ValueStorage& vs)
{
    OTB_ASSERT(std::holds_alternative<std::string>(vs.storage));
    return std::stoi(std::get<std::string>(vs.storage));
}

template<> float ValueStorageUtils::deserialize<float>(const ValueStorage& vs)
{
    OTB_ASSERT(std::holds_alternative<std::string>(vs.storage));
    return std::stof(std::get<std::string>(vs.storage));
}

template<> Vector3 ValueStorageUtils::deserialize<Vector3>(const ValueStorage& vs)
{
    OTB_ASSERT(std::holds_alternative<ValueStorage::ArrayType>(vs.storage));
    const auto& arr = std::get<ValueStorage::ArrayType>(vs.storage);
    OTB_ASSERT(arr.size() == 3);
    return { deserialize<float>(arr[0]), deserialize<float>(arr[1]), deserialize<float>(arr[2]) };
}
}