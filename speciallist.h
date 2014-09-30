#ifndef SPECIALLIST_H
#define SPECIALLIST_H

#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <tuple>
#include <vector>
#include <forward_list>
#include <algorithm>

template <typename Name, typename Number, typename Compare = std::less<Name> >
class SpecialList
{
public:
    typedef typename std::tuple<Name, Number, long double, long double> tuple;
    typedef typename std::map<Name, std::forward_list<Number>, Compare> map;

    class iterator
    {
    public:
        iterator() {}

        iterator(const iterator &other)
        {
            mapIterator = other.mapIterator;
        }

        iterator(const typename map::iterator &mIterator)
        {
            mapIterator = mIterator;
        }

        ~iterator() {}

        iterator& operator=(const iterator &other)
        {
//            iterator(other);
//            swap(tmp);
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

        tuple operator*() const
        {
            return prepareTuple();
        }

        tuple* operator->() const
        {
            return &prepareTuple();
        }

    private:
        tuple prepareTuple() const
        {
            std::vector<int> numbers{ mapIterator->second.cbegin(), mapIterator->second.cend() };
            std::sort(numbers.begin(), numbers.end());
            Number sum = 0;
            for(auto i = numbers.begin(); i != numbers.end(); i++)
                sum += *i;
            long double mean = (double)sum / numbers.size();
            long double median;
            if(numbers.size() % 2 == 0)
                median = (numbers[numbers.size() / 2] + numbers[numbers.size() / 2 + 1]) / 2.0;
            else
                median = numbers[numbers.size() / 2];
            return std::make_tuple(mapIterator->first, sum, mean, median);
        }

        typename map::iterator mapIterator;
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
    map::size_type size()
    {
        return values.size();
    }

    typename
    map::size_type max_size()
    {
        return values.max_size();
    }

    bool empty()
    {

        return values.empty();
    }

    SpecialList &operator<<(const std::pair<Name, Number> &pair)
    {
        if(values.find(pair.first) == values.end())
            values[pair.first] = std::forward_list<Number>(1, pair.second);
        else
            values[pair.first].push_front(pair.second);
        return *this;
    }

    friend std::istream &operator>>(std::istream &stream, SpecialList &specialList)
    {
        Name name;
        Number number;
        stream >> name >> number;
        specialList << std::make_pair(name, number);
        return stream;
    }

    friend std::ostream &operator<<(std::ostream &stream, SpecialList &specialList)
    {
        for(auto const &i: specialList)
        {
        stream << "name: " << std::get<0>(i)
             << " total: " << std::get<1>(i)
             << " mean: " << std::get<2>(i)
             << " median: " << std::get<3>(i)
             << std::endl;
        }
        return stream;
    }

protected:
     map values;
};

#endif // SPECIALLIST_H
