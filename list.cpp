#include "list.h"

template <typename Object>
List<Object>::List()
{
    header = new ListNode<Object>;
}

template <typename Object>
List<Object>::List(const List<Object> &rhs)
{
    header = new ListNode<Object>;
    *this = rhs;
}

template <typename Object>
List<Object>::~List()
{
    makeEmpty( );
    delete header;
}

template <typename Object>
bool List<Object>::isEmpty() const
{
    return header->next == nullptr;
}

template <typename Object>
void List<Object>::makeEmpty()
{
    while(!isEmpty())
        remove(first().retrieve());
}

template <typename Object>
ListItr<Object> List<Object>::zeroth() const
{
    return ListItr<Object>(header);
}

template <typename Object>
ListItr<Object> List<Object>::first() const
{
    return ListItr<Object>(header->next);
}

// Insert item x after p
template <typename Object>
void List<Object>::insert(const Object &x, const ListItr<Object> &p)
{
    if(p.current != nullptr)
        p.current->next = new ListNode<Object>(x, p.current->next);
}

// Return iterator corresponding to the first node containing an item x.
// Iterator isPastEnd if item is not found.
template <typename Object>
ListItr<Object> List<Object>::find(const Object &x) const
{
    ListNode<Object> *itr = header->next;
    while(itr != nullptr && itr->element != x)
        itr = itr->next;
    return ListItr<Object>(itr);
}

// Return iterator prior to the first node containing an item x.
template <typename Object>
ListItr<Object> List<Object>::findPrevious(const Object &x) const
{
    ListNode<Object> *itr = header;
    while(itr->next != nullptr && itr->next->element != x)
        itr = itr->next;
    return ListItr<Object>(itr);
}

// Remove first occurrence of an item x
template <typename Object>
void List<Object>::remove(const Object &x)
{
    ListItr<Object> p = findPrevious(x);
    if(p.current->next != nullptr)
    {
        ListNode<Object> *oldNode = p.current->next;
        p.current->next = p.current->next->next; // Bypass deleted node
        delete oldNode;
    }
}

// Deep copy of linked lists.
template <typename Object>
const List<Object> & List<Object>::operator=(const List<Object> &rhs)
{
    ListItr<Object> ritr = rhs.first();
    ListItr<Object> itr = zeroth();
    if(this != &rhs)
    {
        makeEmpty( );
        for(; !ritr.isPastEnd(); ritr.advance(), itr.advance() )
            insert( ritr.retrieve(), itr );
    }
    return *this;
}
