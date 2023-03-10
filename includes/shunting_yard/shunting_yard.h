#ifndef SHUNTING_YARD_H
#define SHUNTING_YARD_H
#include <iostream>
#include <cmath>
#include <string>
#include "../rpn/rpn.h"
#include "../token/token.h"
#include "../token/integer.h"
#include "../token/operator.h"
#include "../token/function.h"

#include "../queue/MyQueue.h"
#include "../stack/MyStack.h"

using namespace std;

class ShuntingYard
{
public:
    ShuntingYard(); //Default CTOR
    ShuntingYard(const Queue<Token*> &q); //CTOR

    Queue<Token*> postfix();
    Queue<Token*> postfix(Queue<Token*> infix);

    void infix(const Queue<Token*> &q); //set_input version 
    void print(ostream &outs) const;

private:
    Queue<Token*> inf; 
};

#endif // SHUNTING_YARD_H