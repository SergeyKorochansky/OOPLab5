#ifndef UTILITY_H
#define UTILITY_H

namespace mystl
{
    template <typename T1, typename T2>
    struct pair
    {
        typedef T1 first_type;
        typedef T2 second_type;

        T1 first;
        T2 second;

        pair();
        pair(const T1& x);
        pair(const T1& x, const T2& y);

        template <typename U, typename V>
        pair(const pair<U, V> &p);
    };

    template <typename Pair>
    struct use_first
    {
        typedef typename Pair::first_type result_type;

        const result_type& operator()(const Pair& x) const
            { return x.first; }
    };

    template <typename Pair>
    struct use_second
    {
        typedef typename Pair::second_type result_type;

        const result_type& operator()(const Pair& x) const
            { return x.second; }
    };

    template <typename T1, typename T2>
    inline pair<T1, T2>::pair()
        : first(), second()
    {
        // Empty
    }


    template <typename T1, typename T2>
    inline pair<T1, T2>::pair(const T1& x)
        : first(x), second()
    {
        // Empty
    }


    template <typename T1, typename T2>
    inline pair<T1, T2>::pair(const T1& x, const T2& y)
        : first(x), second(y)
    {
        // Empty
    }


    template <typename T1, typename T2>
    template <typename U, typename V>
    inline pair<T1, T2>::pair(const pair<U, V>& p)
        : first(p.first), second(p.second)
    {
        // Empty
    }

    template <typename T1, typename T2>
    inline pair<T1, T2> make_pair(T1 a, T2 b)
    {
        return pair<T1, T2>(a, b);
    }

    template <typename T1, typename T2>
    inline pair<T1, T2> make_pair_ref(const T1& a, const T2& b)
    {
        return pair<T1, T2>(a, b);
    }

    template <typename T1, typename T2, typename T3, typename T4>
    struct four
    {
        typedef T1 first_type;
        typedef T2 second_type;
        typedef T3 third_type;
        typedef T4 fourth_type;

        T1 first;
        T2 second;
        T3 third;
        T4 fourth;

        four() : first(), second(), third(), fourth() {}
        four(const T1& a, const T2& b, const T3 &c, const T4 &d) : first(a), second(b), third(c), fourth(d) {}
        four(const four<T1, T2, T3, T4>& p) : first(p.first), second(p.second), third(p.third), fourth(p.fourth) {}
    };
}

#endif // UTILITY_H
