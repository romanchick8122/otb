#pragma once

#include <string>

namespace otb
{
class InternedString
{
  public:
    InternedString(const char*);

    static InternedString get_empty();

    const char* c_str() const;

    friend auto operator<=>(const InternedString& l, const InternedString& r)
    {
        return l.node <=> r.node;
    }

    friend bool operator==(const InternedString& l, const InternedString& r)
    {
        return l.node == r.node;
    }
  private:
    const void* node;
};
}

namespace std
{
template<>
struct hash<otb::InternedString>
{
    std::hash<const char*> impl;

    std::size_t operator()(const otb::InternedString& v) const noexcept
    {
        return impl(v.c_str());
    }
};
}