#ifndef LISTNODE_H
#define LISTNODE_H

template <typename Object>
class List;

template <typename Object>
class ListItr;

template <typename Object>
class ListNode
{
    ListNode(const Object &theElement = Object(), ListNode *n = nullptr)
        : element(theElement), next(n) {}
    Object element;
    ListNode *next;
    friend class List<Object>;
    friend class ListItr<Object>;
};

#endif // LISTNODE_H
