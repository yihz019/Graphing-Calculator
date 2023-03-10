#include "tk_string.h"

Tokenizer::Tokenizer() {} //CTOR

Tokenizer::Tokenizer(string equation)  //set equation string
{
    string tk_string; //local string token to push into Queue
    for (int i = 0; i < equation.size(); i++) //if string not empty
    {
        if (isdigit (equation[i])){ // if is digit, is integer
            while (isdigit (equation[i])){ 
                tk_string += (equation[i]); //add it to local string (string of tokens) 
                i++; //till is not a digit
            }
            if (tk_string.front() != NULL){ //push every integer into Q if is not empty
                _infix.push (new Integer(stod(tk_string))); //tranform string into digit and push 
                tk_string.clear(); //clear string
            }
        }
        if (isalpha (equation [i])) { //if is char {alphabeth} / function 
            //add every single funtion into string and
            //create variable or function token to push it into the infix Q
            while (isalpha (equation [i])){
                tk_string += tolower (equation [i]); //tranform into lowercase and keep adding
                i++;
            } 

            if (tk_string.front() != NULL && tk_string.length() < 2){ //only one variable [x,y,z]
                _infix.push(new Function(tk_string));
                tk_string.clear();
            }
            else if(tk_string.length() > 1) { //trig function
                _infix.push (new Function (tk_string));
                tk_string.clear();
            }
        }
        
        
        //else swith and create the operator token for each case
        if (!isalpha (equation[i]) && !isdigit (equation[i])){
            switch (equation[i]) {
            case '+':
                _infix.push(new Operator("+"));
                break;
            case '-':
                _infix.push (new Operator("-"));
                break;
            case '*':
                _infix.push (new Operator("*"));
                break;
            case '/':
                _infix.push (new Operator("/"));
                break;
            case '^':
                _infix.push (new Operator("^"));
                break;
            case '(':
                _infix.push (new LeftParen("("));
                break;
            case ')':
                _infix.push (new RightParen(")"));
                break;
            }
        }
    }
}

Queue <Token*> Tokenizer::get_infix(){ 
    return _infix;   //return tokenized queue
}

// if (equation[i] == tk_string.back()){ //if find same variable (function)
//     i = equation.size(); //get pos
//     tk_string.clear(); //clear local string
//     if (!_infix.empty()){
//         do {
//             _infix.pop(); //pop 
//         } while (!_infix.empty());       
//     }
// }
