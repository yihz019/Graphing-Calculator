#ifndef LINKED_LIST_FUNCTIONS_H
#define LINKED_LIST_FUNCTIONS_H

#include <iostream>
#include <iomanip>
#include <cassert>
#include "../../includes/node/node.h"

using namespace std;

// Linked List General Functions:
template <typename T>
void _print_list(node<T> *head);

// recursive fun! :)
template <typename T>
void _print_list_backwards(node<T> *head);

// return ptr to key or NULL
template <typename T>
node<T> *_search_list(node<T> *head, T key);

template <typename T>
node<T> *_insert_head(node<T> *&head, T insert_this);

// insert after ptr
template <typename T>
node<T> *_insert_after(node<T> *&head, node<T> *after_this, T insert_this);

// insert before ptr
template <typename T>
node<T> *_insert_before(node<T> *&head, node<T> *before_this, T insert_this);

// ptr to previous node
template <typename T>
node<T> *_previous_node(node<T> *head, node<T> *prev_to_this); /// if head is null then assert check like search

// delete, return item
template <typename T>
T _delete_node(node<T> *&head, node<T> *delete_this);

// duplicate the list...
template <typename T>
node<T> *_copy_list(node<T> *head);

// duplicate list and return the last node of the copy
template <typename T>
node<T> *_copy_list(node<T> *&dest, node<T> *src);

// delete all the nodes
template <typename T>
void _clear_list(node<T> *&head);

//_item at this position
template <typename T>
T &_at(node<T> *head, int pos);

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
//                              Sorted List Routines.
//                              Assume a Sorted List
//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

template <typename T>
node<T> *_insert_sorted(node<T> *&head, T item, bool ascending = true); // insert

// insert or add if a dup
template <typename T>
node<T> *_insert_sorted_and_add(node<T> *&head,
                                T item,
                                bool ascending = true);
// node after which this item goes order: 0 ascending
template <typename T>
node<T> *_where_this_goes(node<T> *head,
                          T item,
                          bool ascending = true);
// Last Node in the list
template <typename T>
node<T> *_last_node(node<T> *head); //

//======================================================================================

template <typename T>
void _print_list(node<T> *head)
{
    //[setup...]
    node<T> *walker = head; // point walker to start of the head
    //[condition...]
    while (walker != nullptr)
    {
        //[inside]
        cout << *walker;
        walker = walker->_next;
    }
    // outside...
    cout << "|||" << endl;
}

// recursive fun! :)
template <typename T>
void _print_list_backwards(node<T> *head)
{
    node<T> *walker = head;
    node<T> *last = head;

    if (walker->_next == nullptr)
    {
        cout << *walker;
    }

    else
    {
        last = _last_node(head);             // get and save last node
        cout << *last;                       // print last element as first
        walker = _previous_node(head, last); // get previous node of last

        while (walker != head) // going back until it hits head
        {
            cout << *walker;
            walker = _previous_node(head, walker);
        }
        cout << *walker; // print head as last element
    }
    cout << "|||" << endl;
}

// return ptr to key or NULL
template <typename T>
node<T> *_search_list(node<T> *head, T key)
{
    node<T> *walker = head;
    while (walker != nullptr)
    {
        if (walker->_item == key)
        {
            return walker; // stub: Return address of the node containing key
        }
        walker = walker->_next;
    }
    return nullptr; //   or nullptr if not found.
}

template <typename T>
node<T> *_insert_head(node<T> *&head, T insert_this)
{
    node<T> *temp = new node<T>(insert_this); // 1. create new node [temp]
    temp->_next = head;                       // 2. temp's next points to headptr
    head = temp;                              // 3. headptr points to where temp is pointing to:
    return head;

    // Option #2
    // node *temp = new node(item, headptr);
}

// insert after ptr
template <typename T>
node<T> *_insert_after(node<T> *&head, node<T> *after_this, T insert_this)
{
    node<T> *temp = new node<T>(insert_this); // create new node
    node<T> *walker = head;                   // point walker to search for pos

    if (walker == nullptr) // check if head is not null [if list is not empty]
    {
        return _insert_head(head, insert_this);
    }
    else
    {
        while (walker != nullptr) // while walker doesn't hit the end of list
        {
            if (walker == after_this) // found pos
            {
                temp->_next = walker->_next; // insert new node after pos
                walker->_next = temp;        // conect previous node
                return temp;
            }
            walker = walker->_next;
        }
    }
    return nullptr;
}

// insert before ptr
template <typename T>
node<T> *_insert_before(node<T> *&head, node<T> *before_this, T insert_this)
{
    node<T> *temp = new node<T>(insert_this); // create new node
    node<T> *walker = head;                   // point walker to search for pos
    node<T> *prev = head;

    if (walker == before_this && head != nullptr) // check if before this is head and list is not empty
    {
        return _insert_head(head, insert_this);
    }
    walker = walker->_next;
    while (walker != nullptr)
    {
        if (walker == before_this) // found pos
        {
            temp->_next = walker; // insert new node
            prev->_next = temp;   // conect previous node to new
            return temp;
        }
        walker = walker->_next;
        prev = prev->_next;
    }
    return nullptr;
}

// ptr to previous node
template <typename T>
node<T> *_previous_node(node<T> *head, node<T> *prev_to_this)
{
    node<T> *walker = head; // point walker to search for prev_to_this [pos]

    while (walker != nullptr && head != prev_to_this) // search rest of list if it's not first node
    {
        if (walker->_next == prev_to_this) // if next of me is prev_this
        {
            return walker; // return me
        }
        walker = walker->_next; // else keep going
    }
    return nullptr; // if node not in the list or is first node of the list
}

// delete, return item
template <typename T>
T _delete_node(node<T> *&head, node<T> *delete_this)
{
    T temp;                 // node item to be returned
    node<T> *walker = head; // node prev to delete_this
    node<T> *prev = head;   // node prev to delete_this

    if (walker == delete_this && walker != nullptr)
    {                         // if delete_this is head
        prev = walker->_next; // next to delete_this
        head = prev;          // connect to node next to delete_this
        temp = walker->_item; // get item
        delete walker;        // delete node
    }
    else
    {
        walker = walker->_next;
        while (walker != nullptr)
        {
            if (walker == delete_this && walker->_next != nullptr)
            {
                prev->_next = walker->_next;
                temp = walker->_item;
                delete walker;
                return temp;
            }
            if (walker == delete_this && walker->_next == nullptr)
            {
                prev->_next = nullptr;
                temp = walker->_item;
                delete walker;
                return temp;
            }
            walker = walker->_next;
            prev = prev->_next;
        }
    }
    return temp;
}

// duplicate the list...
template <typename T>
node<T> *_copy_list(node<T> *head)
{
    node<T> *walker = head;
    node<T> *prev = head;
    node<T> *temp = nullptr; // new node [temp]
    
    if (head->_next ==nullptr) //copying one element 
    {
        return _insert_head<T>(temp, prev->_item); // copy last element as first
    }

    if (walker != nullptr)   // check if list is not empty
    {
        walker = walker->_next;
        while (walker != nullptr)
        {
            walker = walker->_next; // move to the end of list
            prev = prev->_next;     // save last element
        }
        temp = _insert_head<T>(temp, prev->_item); // copy last element as first
        walker = _previous_node<T>(head, prev);    // move backwards
        while (walker != head)                     // keep copyig until it hits head
        {
            temp = _insert_head<T>(temp, walker->_item);
            walker = _previous_node<T>(head, walker);
        }
        temp = _insert_head<T>(temp, walker->_item); // copy head as last element

        return temp;
    }
    return nullptr; // if list is empty
}

// duplicate list and return the last node of the copy
template <typename T>
node<T> *_copy_list(node<T> *&dest, node<T> *src)
{
    dest = _copy_list(src);
    return _last_node(dest);
}

// delete all the nodes
template <typename T>
void _clear_list(node<T> *&head)
{
    node<T> *walker = head;
    node<T> *temp = head;
    node<T> item;

    if (head != nullptr)
    {
        temp = _last_node(head);                // move temp to last node
        walker = _previous_node<T>(head, temp); // get and save prev node to last node

        while (walker != head && head != nullptr) // keep deleting until walker hits frst node
        {
            item = _delete_node<T>(head, temp);     // delete the last element
            temp = walker;                          // going backwards
            walker = _previous_node<T>(head, temp); // keep saving previus node to the node we are deleting
        }
        item = _delete_node<T>(head, temp); // delete first node
        temp = walker;
        item = _delete_node<T>(head, temp); // delete head
    }
}

//_item at this position
template <typename T>
T &_at(node<T> *head, int pos)
{
    node<T> *walker = head;
    int count = 0; // counter
    if (pos == 0)
    {
        return head->_item;
    }
    else
    {
        while (walker != nullptr)
        {
            if (count == pos) // when counter matches pos
            {
                return walker->_item; // return item at that pos
            }
            walker = walker->_next; // else keep going (searching)
            count++;
        }
    }
    assert(pos > count);
    return head->_item;
}

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
//                              Sorted List Routines.
//                              Assume a Sorted List
//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

template <typename T> // insert
node<T> *_insert_sorted(node<T> *&head, T item, bool ascending)
{
    node<T> *p = _where_this_goes(head, item, ascending); // find where the item should go
    if (p == nullptr)                                     // if item is less than the rest
    {
        return _insert_head(head, item);
    }
    return _insert_after(head, p, item); // else just insert ater the pos found
}

// insert or add if a dup
// node after which this item goes order: 0 ascending
template <typename T>
node<T> *_insert_sorted_and_add(node<T> *&head, T item, bool ascending)
{
    node<T> *p = _where_this_goes(head, item, ascending); // find where the item should go
    if (p == nullptr)
    {
        return _insert_head(head, item);
    }
    if (p->_item == item) // if they are the same item (dups) then
    {
        p->_item = p->_item + item; // add them
        return p;
    }
    return _insert_after(head, p, item);
}

template <typename T>
node<T> *_where_this_goes(node<T> *head, T item, bool ascending)
{
    node<T> *leader = head;
    if (leader != nullptr && item < leader->_item) // if item is less than fisrt node
    {
        return nullptr;
    }
    while (leader != nullptr)
    {
        if (item == leader->_item) // if is a dup
        {
            return leader; // return the pos of the dup
        }
        if (ascending == true && item < leader->_item)
        {
            return _previous_node(head, leader);
        }
        if (ascending == false && item >= leader->_item)
        {
            return _previous_node(head, leader);
        }
        leader = leader->_next;
    }
    return _last_node(head);
}

// Last Node in the list
template <typename T>
node<T> *_last_node(node<T> *head)
{
    node<T> *walker = head;
    node<T> *prev = head;

    if (head != nullptr)
    {
        walker = walker->_next;   // move it next to prev
        while (walker != nullptr) // move till the end of list
        {
            walker = walker->_next; // walker hits null
            prev = prev->_next;     // so prev save last element
        }
        return prev;
    }
    return nullptr;
}

#endif