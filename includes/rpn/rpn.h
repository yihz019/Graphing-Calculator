#ifndef RPN_H
#define RPN_H
#include <iostream>
#include <cmath>
#include <math.h>
#include "../token/token.h"
#include "../token/integer.h"
#include "../token/operator.h"
#include "../token/function.h"
#include "../queue/MyQueue.h"
#include "../stack/MyStack.h"

using namespace std;

class RPN
{
public:
    RPN();
    RPN(const Queue<Token*>& q); //CTOR

    double eval(double num = 0);
    double operator()(double value = 0);

    void set_input(Queue<Token*> & token);
    void print(ostream &outs) const;

private:
    Queue<Token*> post; // Postfix 
    int min;
    int max;
};




#endif // RPN_H