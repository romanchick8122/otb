#include "core/assert.h"

namespace otb
{
template<class T>
class World::ComponentIterator
{
  private:
    friend class World;

    std::vector<ComponentPtr>*  v;
    size_t pos;

    ComponentIterator(std::vector<ComponentPtr>* _v, size_t _pos)
        : v(_v)
        , pos(_pos)
    {
        if (v != nullptr)
            skip_bad();
    };

    friend bool operator==(const ComponentIterator<T>& l, const ComponentIterator<T>& r)
    {
        return l.v == r.v && (l.v == nullptr || (l.pos >= l.v->size() && r.pos >= r.v->size()) || (l.pos == r.pos));
    }

    void skip_bad()
    {
        while(pos < v->size() && (*v)[pos].expired())
        {
            swap((*v)[pos], v->back());
            v->pop_back();
        }
    }
  public:
    ComponentIterator<T>& operator++()
    {
        OTB_ASSERT(pos < v->size());
        ++pos;
        skip_bad();
        return *this;
    }

    T& operator*()
    {
        Component* component = (*v)[pos].lock().get();
        OTB_ASSERT(component != nullptr);
        return *component_cast<T*>(component);
    }

    T* operator->()
    {
        return &operator*();
    }
};

template<class T>
World::ComponentIterator<T> World::components_begin()
{
    std::type_index tid(typeid(T));
    if (const auto it = components.find(tid);
        it != components.end())
    {
        return ComponentIterator<T>(&it->second, 0);
    }
    return ComponentIterator<T>(nullptr, 0);
}

template<class T>
World::ComponentIterator<T> World::components_end()
{
    std::type_index tid(typeid(T));
    if (const auto it = components.find(tid);
        it != components.end())
    {
        return ComponentIterator<T>(&it->second, -1uz);
    }
    return ComponentIterator<T>(nullptr, 0);
}
}

namespace std
{
template<class T>
struct iterator_traits<otb::World::ComponentIterator<T>>
{
    using iterator_category = forward_iterator_tag;
};
}