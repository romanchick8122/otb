#include "value_storage_utils.h"

#include "core/assert.h"

#include "raymath.h"

#include <sstream>

namespace otb
{
namespace
{
static const otb::InternedString TRANSLATION_FIELD { "translation" };
static const otb::InternedString ROTATION_FIELD { "rotation" };
static const otb::InternedString SCALE_FIELD { "scale" };
}

ValueStorage ValueStorageUtils::serialize(bool v)
{
    return std::string(v ? "True" : "False");
}

ValueStorage ValueStorageUtils::serialize(int v)
{
    return std::to_string(v);
}

ValueStorage ValueStorageUtils::serialize(size_t v)
{
    return std::to_string(v);
}

ValueStorage ValueStorageUtils::serialize(float v)
{
    return std::to_string(v);
}

ValueStorage ValueStorageUtils::serialize(Vector2 v)
{
    std::stringstream ss;
    ss << v.x << " " << v.y;
    return ss.str();
}

ValueStorage ValueStorageUtils::serialize(Vector3 v)
{
    std::stringstream ss;
    ss << v.x << " " << v.y << " " << v.z;
    return ss.str();
}

ValueStorage ValueStorageUtils::serialize(Quaternion v)
{
    std::stringstream ss;
    ss << v.x << " " << v.y << " " << v.z << " " << v.w;
    return ss.str();
}

ValueStorage ValueStorageUtils::serialize(const Transform& transform)
{
    return ValueStorage::DictType {
        { TRANSLATION_FIELD, ValueStorageUtils::serialize(transform.translation) },
        { ROTATION_FIELD, ValueStorageUtils::serialize(QuaternionToEuler(transform.rotation)) },
        { SCALE_FIELD, ValueStorageUtils::serialize(transform.scale) },
    };
}

template<> bool ValueStorageUtils::deserialize<bool>(const ValueStorage& vs)
{
    OTB_ASSERT(std::holds_alternative<std::string>(vs.storage));
    return std::get<std::string>(vs.storage)[0] == 'T';
}

template<> int ValueStorageUtils::deserialize<int>(const ValueStorage& vs)
{
    OTB_ASSERT(std::holds_alternative<std::string>(vs.storage));
    return std::stoi(std::get<std::string>(vs.storage));
}

template<> size_t ValueStorageUtils::deserialize<size_t>(const ValueStorage& vs)
{
    OTB_ASSERT(std::holds_alternative<std::string>(vs.storage));
    size_t result = 0;
    sscanf_s(std::get<std::string>(vs.storage).c_str(), "%zu", &result);
    return result;
}

template<> float ValueStorageUtils::deserialize<float>(const ValueStorage& vs)
{
    OTB_ASSERT(std::holds_alternative<std::string>(vs.storage));
    return std::stof(std::get<std::string>(vs.storage));
}

template<> Vector2 ValueStorageUtils::deserialize<Vector2>(const ValueStorage& vs)
{
    OTB_ASSERT(std::holds_alternative<std::string>(vs.storage));
    std::stringstream ss(std::get<std::string>(vs.storage));
    Vector2 result;
    ss >> result.x >> result.y;
    return result;
}

template<> Vector3 ValueStorageUtils::deserialize<Vector3>(const ValueStorage& vs)
{
    OTB_ASSERT(std::holds_alternative<std::string>(vs.storage));
    std::stringstream ss(std::get<std::string>(vs.storage));
    Vector3 result;
    ss >> result.x >> result.y >> result.z;
    return result;
}

template<> Quaternion ValueStorageUtils::deserialize<Quaternion>(const ValueStorage& vs)
{
    OTB_ASSERT(std::holds_alternative<std::string>(vs.storage));
    std::stringstream ss(std::get<std::string>(vs.storage));
    Quaternion result;
    ss >> result.x >> result.y >> result.z >> result.w;
    return result;
}

template<> Transform ValueStorageUtils::deserialize<Transform>(const ValueStorage& vs)
{
    OTB_ASSERT(std::holds_alternative<ValueStorage::DictType>(vs.storage));
    const auto& dict = std::get<ValueStorage::DictType>(vs.storage);

    Transform result;

    result.translation = ValueStorageUtils::deserialize<Vector3>(dict.at(TRANSLATION_FIELD));
    const std::string& rv = std::get<std::string>(dict.at(ROTATION_FIELD).storage);
    if (std::count(rv.begin(), rv.end(), ' ') == 2)
    {
        const Vector3 rot_euler = ValueStorageUtils::deserialize<Vector3>(dict.at(ROTATION_FIELD));
        result.rotation = QuaternionFromEuler(rot_euler.x, rot_euler.y, rot_euler.z);
    }
    else
    {
        result.rotation = ValueStorageUtils::deserialize<Quaternion>(dict.at(ROTATION_FIELD));
    }
    result.scale = ValueStorageUtils::deserialize<Vector3>(dict.at(SCALE_FIELD));

    return result;
}
}