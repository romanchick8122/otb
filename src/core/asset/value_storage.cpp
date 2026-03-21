#include "value_storage.h"

#include "core/assert.h"

#include <fstream>
#include <optional>

namespace otb
{
namespace
{
ValueStorage load_impl(std::fstream& source)
{
    std::vector<InternedString> keys;
    std::vector<ValueStorage> temporary;

    const auto finish_value = [&]
    {
        OTB_ASSERT(temporary.size() >= 2);
        ValueStorage& add_to = temporary[temporary.size() - 2];

        if (auto array_ptr = std::get_if<ValueStorage::ArrayType>(&add_to.storage))
        {
            array_ptr->emplace_back(std::move(temporary.back()));
            temporary.pop_back();
        }
        else if (auto dict_ptr = std::get_if<ValueStorage::DictType>(&add_to.storage))
        {
            OTB_ASSERT(keys.size() > 0);
            dict_ptr->emplace(keys.back(), std::move(temporary.back()));
            keys.pop_back();
            temporary.pop_back();
        }
        else
        {
            OTB_ASSERT(false);
        }
        
    };

    const auto process_value = [&](const std::string_view& view)
    {
        if (view.starts_with("!<ARRAY>"))
        {
            temporary.emplace_back(ValueStorage::ArrayType{});
        }
        else if (view.starts_with("!<DICT>"))
        {
            temporary.emplace_back(ValueStorage::DictType{});
        }
        else if (view.starts_with("!<VALUE>"))
        {
            temporary.emplace_back(std::string(view.data() + 9));
            finish_value();
        }
        else
        {
            OTB_ASSERT(false);
        }
    };

    bool preprocessed = false;

    std::string line;
    while (std::getline(source, line))
    {
        size_t i = 0;
        while (line[i] == ' ')
        {
            ++i;
        }
        OTB_ASSERT(i % 2 == 0);
        const size_t depth = i / 2;
        OTB_ASSERT(depth <= temporary.size());

        std::string_view line_view(line.c_str() + depth * 2);
        if (line_view.starts_with("//"))
        {
            continue;
        }

        while (depth < temporary.size())
        {
            finish_value();
        }

        if (!preprocessed)
        {
            preprocessed = true;
            process_value(line_view);
        }
        else if (std::holds_alternative<ValueStorage::ArrayType>(temporary.back().storage))
        {
            process_value(line_view);
        }
        else if (std::holds_alternative<ValueStorage::DictType>(temporary.back().storage))
        {
            size_t key_idx = line_view.find(':');
            line[depth * 2 + key_idx] = 0;
            keys.emplace_back(line_view.data());
            process_value(std::string_view(line_view.data() + key_idx + 2));
        }
        else
        {
            OTB_ASSERT(false);
        }
    }

    while (temporary.size() > 1)
    {
        finish_value();
    }
    OTB_ASSERT(temporary.size() == 1);
    return temporary.back();
}
void save_to(std::fstream& target, const ValueStorage& v, size_t depth, std::optional<const char*> key)
{
    OTB_ASSERT(depth > 0 || std::holds_alternative<ValueStorage::DictType>(v.storage));

    std::string prefix(2 * depth, ' ');
    target << prefix;
    if (key.has_value())
    {
        target << *key << ": ";
    }

    if (const auto arr_ptr = std::get_if<ValueStorage::ArrayType>(&v.storage))
    {
        target << "!<ARRAY>\n";
        for (const auto& vs : *arr_ptr)
        {
            save_to(target, vs, depth + 1, std::nullopt);
        }
    }
    else if (const auto dict_ptr = std::get_if<ValueStorage::DictType>(&v.storage))
    {
        target << "!<DICT>\n";
        for (const auto& [k, v] : *dict_ptr)
        {
            save_to(target, v, depth + 1, k.c_str());
        }
    }
    else if (const auto str_ptr = std::get_if<std::string>(&v.storage))
    {
        target << "!<VALUE> " << *str_ptr << "\n";
    }
    else
    {
        OTB_ASSERT(false);
    }
}
}

ValueStorage::ValueStorage()
    : storage()
{
}

ValueStorage::ValueStorage(ValueStorage::ArrayType&& arr)
    : storage(std::move(arr))
{
}

ValueStorage::ValueStorage(ValueStorage::DictType&& dict)
    : storage(std::move(dict))
{
}

ValueStorage::ValueStorage(std::string&& str)
    : storage(std::move(str))
{
}

void ValueStorage::load(InternedString file_path)
{
    std::fstream source{ file_path.c_str(), std::fstream::in };
    *this = otb::load_impl(source);
}

void ValueStorage::save(InternedString file_path) const
{
    std::fstream target{ file_path.c_str(), std::fstream::out | std::fstream::trunc };
    otb::save_to(target, *this, 0, std::nullopt);
}
}