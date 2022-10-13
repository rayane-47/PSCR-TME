#pragma once
#include <cstddef>
template <typename T>
class Vector
{
    size_t alloc_sz;
    size_t sz;
    T *tab;

public:
    Vector(size_t init = 10) : alloc_sz(init), sz(0)
    {
        tab = new T[alloc_sz];
    }
    ~Vector()
    {
        delete[] tab;
    }
    T &operator[](const size_t index)
    {
        return tab[index];
    }
    const T &operator[](const size_t index) const
    {
        return tab[index];
    }
    void push_back(const T &val)
    {
        if (sz >= alloc_sz)
        {
            alloc_sz *= 2;
            T *tmp = new T[alloc_sz];
            for (size_t i(0); i < sz; ++i)
                tmp[i] = tab[i];
            delete[] tab;
            tab = tmp;
        }
        tab[sz++] = val;
    }

    typedef T *iterator;

    iterator begin() { return tab; }
    iterator end() { return tab + sz; }

    class Iterator
    {
        size_t index;
        Iterator &operator++()
        {
            ++index;
            return *this;
        };
    };
};