#ifndef MY_QUEUE_H
#define MY_QUEUE_H

#include <iostream>
#include <iomanip>
#include <cassert>
using namespace std;

#include "../../includes/linked_list_functions/linked_list_functions.h"
#include "../../includes/node/node.h"

template <typename T>
class Queue
{
public:
    class Iterator
    {
    public:
        friend class Queue;                // give access to list to access _ptr
        Iterator() { _ptr = nullptr; }     // default ctor
        Iterator(node<T> *p) { _ptr = p; } // Point Iterator to where
        //...                        //  p is pointing to

        operator bool() // casting operator: true if _ptr not NULL
        {               //       this turned out to be a pain!
            if (_ptr != nullptr)
            {
                return true;
            }
            return false;
        }

        T &operator*()
        { // dereference operator
            return _ptr->_item;
        }

        const T &operator*() const
        { // dereference operator
            return _ptr->_item;
        }

        T *operator->()
        { // member access operator
            return &_ptr->_item;
        }

        const T *operator->() const
        { // member access operator
            return &_ptr->_item;
        }

        bool is_null() // true if _ptr is NULL
        {
            if (_ptr == nullptr)
            {
                return true;
            }
            return false;
        }
        friend bool operator!=(const Iterator &left, const Iterator &right) // true if left != right
        {
            return left._ptr != right._ptr;
        }

        friend bool operator==(const Iterator &left, const Iterator &right) // true if left == right
        {
            return left._ptr == right._ptr;
        }

        Iterator &operator++() // member operator: ++it; or ++it = new_value
        {
            _ptr = _ptr->_next; // i = 1,   j = ++i
            return *this;       // j = 2, i = 2
        }
        friend Iterator operator++(Iterator &it, int unused) // friend operator: it++
        {
            Iterator hold; // i = 1;   j = i++
            hold = it;     // j = 1, i = 2
            it = it._ptr->_next;
            return hold;
        }

    private:
        node<T> *_ptr; // pointer being encapsulated
    };

    Queue();

    Queue(const Queue<T> &copyMe);
    ~Queue();
    Queue &operator=(const Queue<T> &RHS);

    bool empty();
    T front();
    T back();

    void push(T item);
    T pop();

    Iterator begin() const; // Iterator to the head node
    Iterator end() const;   // Iterator to NULL
    void print_pointers();
    int size() const { return _size; }
    template <typename TT>
    friend ostream &operator<<(ostream &outs, const Queue<TT> &printMe);

private:
    node<T> *_front;
    node<T> *_rear;
    int _size;
};

//=================================

template <typename T>
Queue<T>::Queue()
{
    _front = nullptr;
    _rear = nullptr;
    _size = 0;
}

// BIG 3
template <typename T>
Queue<T>::Queue(const Queue<T> &copyMe)
{
    _size = copyMe._size;
    _rear = _copy_list(_front, copyMe._front);
}

template <typename T>
Queue<T>::~Queue()
{
    delete[] _front;
}

template <typename T>
Queue<T> &Queue<T>::operator=(const Queue<T> &RHS)
{
    if (this != &RHS) // check for self-reference
    {
        _clear_list<T>(_front);
        _size = RHS._size;                         // copy non-dynamic member variables.
        _rear = _copy_list<T>(_front, RHS._front); // copy node from rhs to this
        return *this;
    }
    return *this;
}

template <typename T>
bool Queue<T>::empty()
{
    if (_front == nullptr)
    {
        return true;
    }
    return false;
}

template <typename T>
T Queue<T>::front()
{
    // assert(_front == nullptr);
    return _front->_item;
}

template <typename T>
T Queue<T>::back()
{
    return _rear->_item;
}

template <typename T>
void Queue<T>::push(T item)
{
    _size += 1;
    _rear = _insert_after(_front, _rear, item);
}

template <typename T>
T Queue<T>::pop()
{
    assert(_front != nullptr);
    _size -= 1;
    return (_delete_node(_front, _front));
}

template <typename T>
typename Queue<T>::Iterator Queue<T>::begin() const // Iterator to the head node
{
    return Iterator(_front);
}

template <typename T>
typename Queue<T>::Iterator Queue<T>::end() const // Iterator to NULL
{
    return Iterator(nullptr);
}

template <typename T>
void Queue<T>::print_pointers()
{
    _print_list(_front);
}

template <typename TT>
ostream &operator<<(ostream &outs, const Queue<TT> &printMe)
{
    outs << "Queue:Head->";
    _print_list(printMe._front);
    return outs;
}

#endif