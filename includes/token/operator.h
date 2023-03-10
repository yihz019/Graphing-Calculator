#ifndef OPERATOR_H
#define OPERATOR_H

#include <iostream>
#include "token.h"

using namespace std;

class Operator: public Token    // [*, /, +, -] 
{
public:
    Operator();
    Operator(string oper);

    void Print(ostream &outs) const;
    
    TOKEN_TYPES TypeOf(){
        return OPERATOR;
    }

    int get_prec(); //get precedence for RPN
    int get_p(); //get precedence for sy

    string get_oper(); 

private:
    string op;
    int _p = 0;
    int prec = 0;  //precedence of operator

};


#endif