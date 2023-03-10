#include "function.h"

// variables [X,Y,Z]
Function::Function() 
{
    _var = nullptr;
}

Function::Function(string var)
{
    _var = var;
    
    if(_var == "sin")
        ident = 1;
    else if(_var == "cos")
        ident = 2;
    else if(_var == "tan")
        ident = 3;
    else if(_var == "cot")
        ident = 4;
    else if(_var == "pi")
        ident = 5;
    else if(_var == "sec")
        ident = 6;
    else if(_var == "csc")
        ident = 7;
    else if(_var == "arcsin")
        ident = 8;
    else if(_var == "arccos" || _var == "arcos" )
        ident = 9;
    else if(_var == "arctan")
        ident = 10;
    else if(_var == "abs")
        ident = 11;
    else if(_var == "alpha")
        ident = 12;
    else if ( _var == "sqrt")
        ident = 13;

    else if ( _var == "log")
        ident = 14;
    
    else if ( _var == "ln")
        ident = 15;
        
    else if(_var == "e")
        ident = 16;
    
    else if(_var == "arcsec")
        ident = 17;
    
    else if(_var == "arccsc" || _var == "arcsc")
        ident = 18;
    else if (_var == "log")
        ident = 19;
}

       

void Function::Print(ostream &outs) const 
{
    // outs << "variable: " ;
    outs << _var;
}





