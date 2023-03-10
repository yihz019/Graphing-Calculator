#ifndef TK_STRING_H
#define TK_STRING_H
#include <iostream>
#include <cstring>
#include <cmath>

#include "../stack/MyStack.h"
#include "../queue/MyQueue.h"

#include "token.h"
#include "integer.h"
#include "function.h"
#include "operator.h"
#include "leftparen.h"
#include "rightparen.h"

using namespace std;

class Tokenizer : public Token
{
public:
    Tokenizer(); //CTOR
    Tokenizer(string equation);  //set equation string to infix Q
    Queue <Token*> get_infix();   //return infix queue

private:
    Queue <Token*> _infix;   //infix queue

};

#endif // TK_STRING_H
