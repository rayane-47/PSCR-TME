#pragma once
#include <cstddef>
template <typename T>
class Iterator
{
    size_t index;
    Iterator &operator++()
    {
        ++index;
        return *this;
    };
};