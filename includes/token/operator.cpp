#include "operator.h"

Operator::Operator()
{
    op = nullptr;
}

Operator::Operator(string oper)
{
    op = oper; // [-, +, *, /, ^]

    if (op.length() == 1)
    {
        switch (op[0])
        {
        case '-':
            prec = 1;
            _p = 2;
            break;
        case '+':
            prec = 2;
            _p = 2;
            break;
        case '*':
            prec = 3;
            _p = 3;
            break;
        case '/':
            prec = 4;
            _p = 3;
            break;
        case '^':
            prec = 5;
            _p = 5;
            break;
        }
    }
}

int Operator::get_prec() // get precedence
{
    return prec;
}

int Operator::Operator::get_p() // get precedence
{
    return _p;
}

string Operator::get_oper()  
{
    return op;
} 

void Operator::Print(ostream &outs) const
{
    // outs << "operator: " ;
    outs << op;
}



