#ifndef SPECIALLIST_H
#define SPECIALLIST_H

#define USE_MYSTL 1

#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>

#if USE_MYSTL
    #include "MYSTL/map.h"
    #include "MYSTL/list.h"
    using mystl::less;
    using mystl::map;
    using mystl::list;
    using mystl::pair;
    using mystl::four;
#else
    #include <map>
    #include <list>
    #include "MYSTL/utility.h"
    using std::less;
    using std::pair;
    using std::map;
    using std::list;
    using mystl::four;
#endif

template <typename Name, typename Number, typename Compare = less<Name> >
class SpecialList
{
public:
    typedef four<Name, Number, long double, Number> special_four;
    typedef pair<Name, Number> special_pair;

    typedef list<Number> special_list;
    typedef map<Name, special_list, Compare> special_map;

    class iterator
    {
    public:
        iterator() {}

        iterator(const iterator &other)
        {
            mapIterator = other.mapIterator;
        }

        iterator(const typename special_map::iterator &mIterator)
        {
            mapIterator = mIterator;
        }

        ~iterator() {}

        iterator& operator=(const iterator &other)
        {
            auto tmp = iterator(other);
            swap(tmp);
            return *this;
        }

        bool operator==(const iterator &other) const
        {
            return mapIterator == other.mapIterator;
        }
        bool operator!=(const iterator &other) const
        {
            return mapIterator != other.mapIterator;
        }

        iterator& operator++()
        {
            mapIterator++;
            return *this;
        }

        iterator& operator++(int)
        {
            mapIterator++;
            return *this;
        }

        special_four operator*() const
        {
            return prepareTuple();
        }

        special_four* operator->() const
        {
            return &prepareTuple();
        }

    private:
        special_four prepareTuple() const
        {
            mapIterator->second.sort();
            auto count = mapIterator->second.size();
            Number sum = 0;
            int i = 0;
            int middleIndex = (count % 2) ? count/2 : count/2 + 1;
            Number median;
            for(auto it = mapIterator->second.begin(); it != mapIterator->second.end(); it++, i++)
            {
                sum += *it;
                if(i == middleIndex)
                    median = *it;
            }
            long double mean = (double)sum / count;
            return special_four(mapIterator->first, sum, mean, median);
        }

        typename special_map::iterator mapIterator;
    };

    SpecialList() { }

    SpecialList(const SpecialList &other)
    {
        values = other.values;
    }

    ~SpecialList()
    {
    }

    SpecialList& operator=(const SpecialList &other)
    {
        SpecialList tmp(other);
        swap(tmp);
        return *this;
    }

    bool operator==(const SpecialList &other) const
    {
        return values == other.values;
    }

    bool operator!=(const SpecialList &other) const
    {
        return values != other.values;
    }

    iterator begin()
    {
        return iterator(values.begin());
    }

    iterator end()
    {
        return iterator(values.end());
    }

    void swap(const SpecialList &swapped)
    {
        values.swap(swapped.values);
    }

    typename
    special_map::size_type size()
    {
        return values.size();
    }

    typename
    special_map::size_type max_size()
    {
        return values.max_size();
    }

    bool empty()
    {

        return values.empty();
    }

    SpecialList &operator<<(const special_pair &pair)
    {
        if(values.find(pair.first) == values.end())
            values[pair.first] = special_list(1, pair.second);
        else
            values[pair.first].push_front(pair.second);
        return *this;
    }

    friend std::istream &operator>>(std::istream &stream, SpecialList &specialList)
    {
        Name name;
        Number number;
        stream >> name >> number;
        specialList << special_pair(name, number);
        return stream;
    }

    friend std::ostream &operator<<(std::ostream &stream, SpecialList &specialList)
    {
        for(auto const &i: specialList)
        {
        stream << "name: " << i.first
             << " total: " << i.second
             << " mean: " << i.third
             << " median: " << i.fourth
             << std::endl;
        }
        return stream;
    }

protected:
     special_map values;
};

#endif // SPECIALLIST_H
