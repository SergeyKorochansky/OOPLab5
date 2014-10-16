#ifndef SORTED_LIST_H
#define SORTED_LIST_H

#include <cstddef>
#include <iterator>
#include <functional>
#include <algorithm>
#include <type_traits>

namespace mystl {

    template< typename Type, typename Compare = std::less<Type>, typename Allocator = std::allocator<Type> >
    class sorted_list
    {
    protected:
        class node_base
        {
            node_base *next;
            node_base *prev;
        };

        class node : node_base
        {
            Type data;
        };

        class iterator
        {
        public:
            typedef iterator                        _self;
            typedef Type                            value_type;
            typedef ptrdiff_t                       difference_type;
            typedef Type*                           pointer;
            typedef Type&                           reference;
            typedef std::bidirectional_iterator_tag	iterator_category;

            explicit iterator(node_base *node);
            bool operator==(const _self &i) const;
            bool operator!=(const _self &i) const;
            reference operator* () const;
            pointer operator-> () const;
            _self& operator++ ();
            _self operator++ (int);
            _self& operator-- ();
            _self operator-- (int);

        protected:
            node_base *node;
        };

        class const_iterator
        {
        public:
            typedef const_iterator                 _self;
            typedef Type                            value_type;
            typedef ptrdiff_t                       difference_type;
            typedef Type*                           pointer;
            typedef Type&                           reference;
            typedef std::bidirectional_iterator_tag	iterator_category;

            explicit const_iterator(const node_base *node);
            const_iterator(const iterator &i);
            bool operator==(const _self &i) const;
            bool operator!=(const _self &i) const;
            reference operator* () const;
            pointer operator-> () const;
            _self& operator++ ();
            _self operator++ (int);
            _self& operator-- ();
            _self operator-- (int);

        protected:
            const node_base *node;
        };

        typedef typename Allocator::template rebind<node>::other    node_allocator;

    public:
        typedef Type                                    value_type;
        typedef Allocator                               allocator_type;
        typedef typename Allocator::reference           reference;
        typedef typename Allocator::const_reference     const_reference;
        typedef typename Allocator::pointer             pointer;
        typedef typename Allocator::const_pointer       const_pointer;
        typedef std::reverse_iterator<iterator>         reverse_iterator;
        typedef std::reverse_iterator<const_iterator>   const_reverse_iterator;
        typedef ptrdiff_t                               difference_type;
        typedef size_t                                  size_type;


        explicit sorted_list(const Allocator &a = Allocator());
        explicit sorted_list(size_type n, const Type &x = Type());

        template <typename InputIterator>
        sorted_list(InputIterator first, InputIterator last, const Allocator& a = Allocator());

        sorted_list(const sorted_list &other);
        ~sorted_list();

        sorted_list &operator= (const sorted_list& other);

        template <typename InputIterator>
        void assign(InputIterator first, InputIterator last);

        void assign(size_type n, const Type& x);

        allocator_type get_allocator() const;

        iterator begin() noexcept;
        const_iterator cbegin() const noexcept;
        iterator end() noexcept;
        const_iterator end() const noexcept;

        reverse_iterator rbegin() const noexcept;
        const_reverse_iterator crbegin() const noexcept;
        reverse_iterator rend() noexcept;
        const_reverse_iterator rend() const noexcept;

        bool empty() const noexcept;
        size_type size() const noexcept;
        size_type max_size() const noexcept;
        void resize(size_type sz, Type x = Type());

        reference front();
        const_reference front() const;
        reference back();
        const_reference back() const;

        void push_front(const Type& x);
        void pop_front();
        void push_back(const Type& x);
        void pop_back();
        iterator insert(iterator pos, const Type& x);
        void insert(iterator pos, size_type n, const Type& x);

        template <typename InputIterator>
        void insert(iterator pos, InputIterator first, InputIterator last);

        iterator erase(iterator pos);
        iterator erase(iterator first, iterator last);
        void swap(sorted_list& other);
        void clear() noexcept;
        void splice(iterator pos, sorted_list& other);
        void splice(iterator pos, sorted_list& other, iterator i);
        void splice(iterator pos, sorted_list& other, iterator first, iterator last);

        void remove(const Type& x);

        template <typename Predicate>
        void remove_if(Predicate pred);

        void unique();
        template <typename BinaryPredicate>
        void unique(BinaryPredicate binary_pred);

        void merge(sorted_list& other);

    protected:
        node* _createNode(const Type& x);
        void _destroyNode(node* node);
        node_base* _insert(node_base* pos, const Type& x);
        void __init();
        node_allocator &__getNodeAllocator();
        const node_allocator &__getNodeAllocator() const;
        Allocator __getTypeAllocator() const;

        template <typename Integer>
        void __init_from_range(Integer n, Integer x, std::true_type);

        template <typename InputIterator>
        void __init_from_range(InputIterator first, InputIterator last, std::false_type);

        void __fill_init(size_type n, const Type &x);
        void __checkAllocators(sorted_list &other);

        void __transfer(iterator _pos, iterator _first, iterator _last);
        void __swap(sorted_list &other);
    };

    template <typename Type, typename Compare, typename Allocator>
    bool operator== (sorted_list<Type, Compare, Allocator> &x, sorted_list<Type, Compare, Allocator> &y)
    {
        typedef typename sorted_list<Type, Compare, Allocator>::const_iterator const_iterator;
        const_iterator i1 = x.begin(), end1 = x.end();
        const_iterator i2 = y.begin(), end2 = y.end();
        while (i1 != end1 && i2 != end2 && *i1 == *i2)
        {
            ++i1;
            ++i2;
        }
        return i1 == end1 && i2 == end2;
    }

    template <typename Type, typename Compare, typename Allocator>
    bool operator<(sorted_list<Type, Compare, Allocator> &x, sorted_list<Type, Compare, Allocator> &y)
    {
        return std::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
    }

    template <typename Type, typename Compare, typename Allocator>
    bool operator!=(sorted_list<Type, Compare, Allocator> &x, sorted_list<Type, Compare, Allocator> &y)
    {
        return !(x == y);
    }

    template <typename Type, typename Compare, typename Allocator>
    bool operator>(sorted_list<Type, Compare, Allocator> &x, sorted_list<Type, Compare, Allocator> &y)
    {
        return y < x;
    }

    template <typename Type, typename Compare, typename Allocator>
    bool operator<=(sorted_list<Type, Compare, Allocator> &x, sorted_list<Type, Compare, Allocator> &y)
    {
        return !(y < x);
    }

    template <typename Type, typename Compare, typename Allocator>
    bool operator>=(sorted_list<Type, Compare, Allocator> &x, sorted_list<Type, Compare, Allocator> &y)
    {
        return !(x < y);
    }

    template <typename Type, typename Compare, typename Allocator>
    void swap(sorted_list<Type, Compare, Allocator> &x, sorted_list<Type, Compare, Allocator> &y)
    {
        x.swap(y);
    }

}

#endif // SORTED_LIST_H
