
#include "shunting_yard.h"

ShuntingYard::ShuntingYard() {}

ShuntingYard::ShuntingYard(const Queue<Token *> &q){ // CTOR
    inf = q;
}

void ShuntingYard::infix(const Queue<Token *> &q){
    inf = q;
}

Queue<Token *> ShuntingYard::postfix()
{
    Queue<Token *>::Iterator it = inf.begin();

    Queue<Token *> q; // output queue
    Stack<Token *> s; // operators stack
    int prec = 0, top = 0;
    Token *oper;
    string op;
    int trig;

    for (; it != nullptr; it++)
    {
        // cout << "s: " << s << endl;
        // cout << "q: " << q << endl;

        // Looping through the queue and getting the type
        //==============================
        Token *t = *it; // token pointer
        // cout << endl;
        // t->Print();
        // cout << t->TypeOf() << endl;
        // ===============================
        switch (t->TypeOf()) // check type
        {
            case INTEGER: { // if integer
                q.push(t); // push as normal number
                break;
            }
            case FUNCTION:{ // or funciton
                trig = static_cast<Function *>(t)->get_ident(); // get trig identity
                switch(trig)
                {
                    case 0:{
                        q.push(t); // push as normal number
                        break;
                    }
                    case 1: //trig functions
                    case 2:
                    case 3: 
                    case 4: 
                    case 5: //pi
                    case 6: 
                    case 7: 
                    case 8: 
                    case 9: 
                    case 10: 
                    case 11: 
                    case 12:
                    case 13: //sqrt 
                    case 14: //log(x)
                    case 15: //log(a,b)
                    case 16: //e
                    case 17: // arcsec
                    case 18: // arccsc
                    case 19: //log
                        s.push(t); //push into operator stack
                        break;
                }
                // t->Print();
                // q.push(t); // push as normal number
                break;
            }
            case OPERATOR:{ // if is an operator
                if (!s.empty()) // if stack not empty
                {
                    // t->Print();
                    prec = static_cast<Operator *>(t)->get_p(); // get prec of coming operator       
                    do
                    {
                        top = static_cast<Operator *>(s.top())->get_p(); // get prec of operator in the top of stack
                        if (top >= prec) // if sitting on operator >=
                        {
                            q.push(s.pop()); // pop from stack & push into queue
                        }
                        else  //sitting on operator < than me
                        {
                            s.push(t); // just push 
                            break;
                        }
                    } while (!s.empty() && top >= prec);  //keep checking till stack empty or find operator < than one entering 
                    if (s.empty()){ //if stack empty after popping
                        s.push(t); // push coming operator
                    }                    
                    break; //else just break
                }
                s.push(t); // if empty stack just push the operator
                break;
            }            
            case R_PAREN: // if is right_parentheses
            {
                // t->Print();
                Token *oper = s.pop();
                while (oper->TypeOf() != L_PAREN && !s.empty())
                {
                    q.push(oper); // pop from stack & push into queue
                    oper = s.pop();
                    // oper->Print() ;
                }
                // s.pop();
                break;
            }
            case L_PAREN: // if is left_parentheses
            {
                s.push(t);
                break;
            }
            case TOKEN:{
                break;
            }
        }

    }
    while (!s.empty()){
        q.push(s.pop()); //@ end pop last operator into queue
    }
    return q;
}

Queue<Token *> ShuntingYard::postfix(Queue<Token *> infix)
{
    inf = infix;
    return postfix();
}

void ShuntingYard::print(ostream &outs) const{
    outs << inf << endl;
}
