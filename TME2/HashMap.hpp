#pragma once
#include <stddef.h>
#include <iostream>
#include <vector>
#include <forward_list>
#include <functional>
template <typename K, typename V>
class HashMap
{
    class Entry
    {
    public:
        const K key;
        V value;
    };
    typedef std::vector<std::forward_list<Entry>> bruckets_t;
    bruckets_t buckets;

public:
    HashMap(size_t init = 100)
    {
        buckets.reserve(init);
        for (size_t i(0); i < init; ++i)
        {
            buckets.push_back(std::forward_list<Entry>());
        }
    }
    ~HashMap()
    {
        buckets.clear();
    }

    V &operator[](const K &key)
    {
        size_t h = std::hash<K>{}(key) % buckets.size();
        auto it = find_if(buckets[h].begin(), buckets[h].end(), [&](const auto &entry)
                          { return entry.key == key; });
        if (it == buckets[h].end())
        {
            buckets[h].push_front(Entry{key, V()});
            return buckets[h].front().value;
        }
        return (*it).value;
    }

    bool find(const K &key)
    {
        size_t h = std::hash<K>()(key);
        std::forward_list<Entry> bucket = buckets[h % buckets.size()];
        auto end = bucket.end();
        for (auto it = bucket.begin(); it != end; ++it)
        {
            if ((*it).key == key)
                return true;
        }
        return false;
    }
};
