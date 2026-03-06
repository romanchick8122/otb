#pragma once

#include "core/interned_string.h"

#include <string>
#include <variant>
#include <vector>
#include <unordered_map>

namespace otb
{
struct ValueStorage
{
public:
    using ArrayType = std::vector<ValueStorage>;
    using DictType = std::unordered_map<InternedString, ValueStorage>;

    using StorageType = std::variant<std::monostate, ArrayType, DictType, std::string>;
    StorageType storage;

    ValueStorage();
    ValueStorage(ArrayType&&);
    ValueStorage(DictType&&);
    ValueStorage(std::string&&);

    void load(InternedString file_path);
    void save(InternedString file_path) const;
};
}