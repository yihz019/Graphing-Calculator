
#include "rpn.h"
#include "../queue/MyQueue.h"
#include "../stack/MyStack.h"

RPN::RPN() {}

double RPN::operator()(double value)
{
    return eval(value);
}

RPN::RPN(const Queue<Token *> &q)
{
    post = q;
}

double RPN::eval(double num)
{
    Stack<double> out; // output stack
    Queue<Token *> temp(post); // copy postfix queue into local queue

    double val = 0; // value to return
    double _num = 0; // to get the num from INTEGER token
    int prec; // precedence
    int trig; // trig identity
    

    Queue<Token*>::Iterator it = temp.begin();
    for (; it != nullptr; it++)
    {
        // Looping through the queue and getting the type
        //==============================
        Token *t = *it; // token pointer
        // cout << endl;
        // t->Print();
        // cout << t->TypeOf() << endl;
        //===============================

        switch (t->TypeOf()) // check type
        {
            case INTEGER: // if is an integer push it
            {
                _num = static_cast<Integer *>(t)->get_num();
                out.push(_num); // push into stack
                break;
            }
            case OPERATOR: // if operator pop pop, do math and push back
            {
                val = out.pop();                               // pop out lastnumber
                prec = static_cast<Operator *>(t)->get_prec(); // get precendence of operator
                switch (prec)                                  // check for precedence of operators and do the math
                {
                    case 5: { // ^
                        val = pow(out.pop(), val);
                        break;
                    }
                    case 4: {// "/" 
                        val = out.pop() / val;
                        break;
                    }
                    case 3: { // "*"
                        val = out.pop() * val;
                        break;
                    }
                    case 2: { //'+'
                        val = out.pop() + val;
                        break;
                    }
                    case 1:{ // '-'
                        if (out.empty()){ 
                            val *= -1;
                        }
                        else{
                            val = out.pop() - val;
                        }
                        break;
                    }
                }
                out.push(val); // push the value back
                break;
            }
            case FUNCTION: // if is funciton
            {
                trig = static_cast<Function *>(t)->get_ident(); // get trig identity
                switch(trig)
                {
                    case 0: // only variables
                        val = num; // give the value and push at the end  // push value given to change the funtion [variable]
                        break;
                    case 1: // sin
                        // val = out.pop();
                        val = sin(out.pop());
                        break;
                    case 2: // cos
                        val = cos(out.pop()); 
                        break;
                    case 3: // tan
                        val = tan(out.pop()); 
                        break;
                    case 4: // cot
                        {int temp = out.pop();
                        val = cos(temp)/sin(temp); }
                        break;
                    case 5: // pi
                        val = (M_PI); 
                        break;
                    case 6: // sec
                        val = 1/cos(out.pop()); 
                        break;
                    case 7: // csc
                        val = 1/sin(out.pop()); 
                        break;
                    case 8: // arcsin
                        val = asin(out.pop()); 
                        break;
                    case 9: // arcos
                        val = acos(out.pop()); 
                        break;
                    case 10: // artan
                        val = atan(out.pop()); 
                        break;   
                    case 11: // abs
                        val = abs(out.pop()); 
                        break;  
                    case 12: // alpha
                        val = isalpha(out.pop()); 
                        break;
                    case 13: // sqrt
                        val = sqrt(out.pop()); 
                        break;  
                    case 14: // log
                        val = log(out.pop()); ;
                        break;   
                    case 15: // log(a,b) [b]ase
                        {int temp = out.pop();
                        val = log(out.pop())/log(temp);}
                        break; 
                    case 16: // e
                        // out.pop();//
                        val = (exp(num)); 
                        break;   
                    case 17: // arcsect
                        val = (acos(1/out.pop())); 
                        break; 
                    case 18: // arccsc
                        val = (asin(1/out.pop())); 
                        break; 
                    case 19: //log
                        val = log(out.pop());
                        break;
                }
                out.push(val); // push value given to change the funtion [variable]
                break;
            }
            case R_PAREN: // if is right_parentesese
            case L_PAREN: // if is an left_parentheses
            case TOKEN:
                break;
        }
    }
    // cout << "\nRESULT: ";
    return out.pop();
    // return val;
}

void RPN::set_input(Queue<Token *> &token)
{
    post = token;
}

void RPN::print(ostream &outs) const
{
    outs << post << endl;
}

