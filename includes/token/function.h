#ifndef FUNCTION_H
#define FUNCTION_H
#include <iostream>
#include "token.h"

using namespace std;
// variables [x,y,z]
class Function: public Token
{
public:
    Function();
    Function(string var);
    int get_ident(){return ident;}; //return trig identity 
    
    void Print(ostream &outs) const;

    TOKEN_TYPES TypeOf(){ //return type
        return FUNCTION;
    }
        

private:
    string _var;
    int ident = 0; // trig identity
};

#endif 