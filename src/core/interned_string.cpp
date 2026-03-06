#include "interned_string.h"

#include <memory>
#include <unordered_map>

namespace
{
    struct LookupTree
    {
        std::unordered_map<char, std::unique_ptr<LookupTree>> children;
        std::string value;

        LookupTree* search(const char* data, const char* original)
        {
            if (*data == 0)
            {
                if (value.empty())
                {
                    value = original;
                }
                return this;
            }

            auto it = children.find(*data);
            if (it == children.end())
            {
                it = children.emplace(*data, std::make_unique<LookupTree>()).first;
            }

            return it->second->search(data + 1, original);
        }
    };

    LookupTree* search(const char* data)
    {
        static LookupTree root;
        return root.search(data, data);
    }
}

namespace otb
{
InternedString::InternedString(const char* data)
    : node(static_cast<void*>(search(data)))
{
}

InternedString InternedString::get_empty()
{
    static const InternedString empty {""};
    return empty;
}

const char* InternedString::c_str() const
{
    return static_cast<const LookupTree*>(node)->value.c_str();
}
}