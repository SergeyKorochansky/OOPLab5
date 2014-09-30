#ifndef LISTITR_H
#define LISTITR_H

template <typename Object>
class List;

template <typename Object>
class ListNode;

template <typename Object>
class ListItr
{
public:
    ListItr() : current(nullptr) {}
    bool isPastEnd() const
    { return current == nullptr; }
    void advance()
    { if( !isPastEnd( ) ) current = current->next; }
    Object &retrieve() const
    {return current->element; }

private:
    ListNode<Object> *current; // Current position
    ListItr( ListNode<Object> *theNode )
        : current( theNode ) { }
    friend class List<Object>; // Grant access to constructor
};


#endif // LISTITR_H
