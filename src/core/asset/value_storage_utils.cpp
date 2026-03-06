#include "value_storage_utils.h"

#include "core/assert.h"

#include <sstream>

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
    std::stringstream ss;
    ss << v.x << " " << v.y << " " << v.z;
    return ss.str();
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
    OTB_ASSERT(std::holds_alternative<std::string>(vs.storage));
    std::stringstream ss(std::get<std::string>(vs.storage));
    Vector3 result;
    ss >> result.x >> result.y >> result.z;
    return result;
}
}