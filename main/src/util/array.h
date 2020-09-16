#pragma once

#include <cstdint>

#include "debug/assert.h"

namespace monster_hub {

template<typename Elem, size_t count>
struct Array
{
    Elem elems[count];

    constexpr Elem& operator [](size_t index);
    constexpr const Elem& operator [](size_t index) const;
};

template<typename Elem, size_t count>
constexpr Elem& Array<Elem, count>::operator [](size_t index)
{
    assert(index < count);

    return elems[index];
}

template<typename Elem, size_t count>
constexpr const Elem& Array<Elem, count>::operator [](size_t index) const
{
    assert(index < count);

    return elems[index];
}

template<typename Elem, size_t count>
constexpr size_t getCount(const Array<Elem, count>& array)
{
    return count;
}

template<typename Elem, size_t count>
constexpr Elem* begin(Array<Elem, count>& array)
{
    assert(array.elems != nullptr);

    return array.elems;
}

template<typename Elem, size_t count>
constexpr const Elem* begin(const Array<Elem, count>& array)
{
    assert(array.elems != nullptr);

    return array.elems;
}

template<typename Elem, size_t count>
constexpr Elem* end(Array<Elem, count>& array)
{
    assert(array.elems != nullptr);

    return array.elems + count;
}

template<typename Elem, size_t count>
constexpr const Elem* end(const Array<Elem, count>& array)
{
    assert(array.elems != nullptr);

    return array.elems + count;
}

} // namespace monster_hub

