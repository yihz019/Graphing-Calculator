#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <iomanip>
using namespace std;

template <typename T>
struct node
{
public:
    node(const T &item = T(), node *next = nullptr):  
    _item(item), _next(next)
    {}

    friend std::ostream &operator<<(std::ostream &outs, const node<T> &printMe)
    {
        outs << "[" << printMe._item << "]->";
        return outs;
    }
    T _item;
    node *_next;
};

#endif