#pragma once
#include <cstddef>

class Iterator
{
    size_t index;
    Iterator &operator++()
    {
        ++index;
        return *this;
    };
};
