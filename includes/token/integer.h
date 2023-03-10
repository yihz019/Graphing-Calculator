#ifndef INTEGER_H
#define INTEGER_H
#include <string>
#include "token.h"

using namespace std;

class Integer: public Token
{
public:
    Integer();
    Integer(double value);
    Integer(string value);

    void Print(ostream &outs) const;

    double get_num();

    int IntegerOnly(){return i;} //example of a function present in a child
    TOKEN_TYPES TypeOf(){
        return INTEGER;
    }

private:
    double i;
};

#endif // INTEGER_H
