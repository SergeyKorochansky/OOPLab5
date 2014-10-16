#ifndef SPECIALLIST_H
#define SPECIALLIST_H

#define USE_MYSTL 1

#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>

#include "utility.h"

#if USE_MYSTL
    #include "map.h"
    #include "sorted_list.h"
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
    using std::pair;
    using mystl::four;
#endif

template <typename Name, typename Number, typename Compare = std::less<Name> >
class special_list
{
public:
    typedef four<Name, Number, long double, long double> special_four;
    typedef pair<Name, Number> special_pair;

    typedef list<Number> integer_list;
    typedef map<Name, integer_list, Compare> special_map;

    class iterator
    {
    public:
        iterator() {}
        iterator(const iterator &other) : mapIterator(other.mapIterator) {}
        iterator(const typename special_map::iterator &mIterator) : mapIterator(mIterator) {}
        ~iterator() {}

        iterator& operator=(const iterator &other)
        {
            auto tmp = iterator(other);
            swap(tmp);
            return *this;
        }

        bool operator==(const iterator &other) const
        { return mapIterator == other.mapIterator; }

        bool operator!=(const iterator &other) const
        { return mapIterator != other.mapIterator; }

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
        { return prepareTuple(); }

        special_four* operator->() const
        { return &prepareTuple(); }

    protected:
        special_four prepareTuple() const
        {
            #ifndef USE_MYSTL
                mapIterator->second.sort();
            #endif
            auto count = mapIterator->second.size();
            Number sum = 0;
            int i = 0;
            bool isEven = ((count % 2) == 0);
            int middleIndex = count/2;
            long double median;
            for (auto it = mapIterator->second.begin(); it != mapIterator->second.end(); it++, i++)
            {
                sum += *it;
                if (i == middleIndex)
                {
                    if (isEven)
                    {
                        long double first = *it;
                        long double second = *std::next(it);
                        median = (first + second) / 2;
                    }
                    else
                        median = *it;

                }
            }
            long double mean = (double)sum / count;
            return special_four(mapIterator->first, sum, mean, median);
        }

        typename special_map::iterator mapIterator;
    };

    special_list() {}
    special_list(const special_list &other) : values(other.values) {}
    virtual ~special_list() {}

    special_list& operator=(const special_list &other)
    {
        special_list tmp(other);
        swap(tmp);
        return *this;
    }

    bool operator==(const special_list &other) const
    { return values == other.values; }

    bool operator!=(const special_list &other) const
    { return values != other.values; }

    iterator begin()
    { return iterator(values.begin()); }

    iterator end()
    { return iterator(values.end()); }

    void swap(const special_list &swapped)
    { values.swap(swapped.values); }

    typename
    special_map::size_type size()
    { return values.size(); }

    typename
    special_map::size_type max_size()
    {
        return values.max_size();
    }

    bool empty()
    {  return values.empty(); }

    special_list &operator<<(const special_pair &pair)
    {
        if(values.find(pair.first) == values.end())
            values[pair.first] = integer_list(1, pair.second);
        else
            values[pair.first].push_front(pair.second);
        return *this;
    }

    friend std::istream &operator>>(std::istream &stream, special_list &specialList)
    {
        Name name;
        Number number;
        stream >> name >> number;
        specialList << special_pair(name, number);
        return stream;
    }

    friend std::ostream &operator<<(std::ostream &stream, special_list &specialList)
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
