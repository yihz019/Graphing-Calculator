#include "integer.h"

Integer::Integer(){  
    i = 0;
}

Integer::Integer(double value){ 
    i = value; 
}

Integer::Integer(string value){ 
    i = atoi(value.c_str()); 
}

double Integer::get_num(){
    return i;
}

void Integer::Print(ostream &outs) const{
    // outs <<"Integer: ["
    outs <<i;
}


