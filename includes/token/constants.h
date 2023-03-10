#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <iostream>
using namespace std;

enum TOKEN_TYPES {INTEGER,
                  OPERATOR,
                  FUNCTION,
                  R_PAREN,
                  L_PAREN,
                  TOKEN};

// string token_type_string(TOKEN_TYPES n){
//     switch(n)
//     {
//         case 0: return "INTEGER";
//             break;
//         case 1: return "OPERATOR";
//             break;
//         case 2: return "FUNCTION";
//             break;
//         case 3: return "R_PAREN";
//             break;
//         case 4: return "L_PAREN";
//             break;
//         case 5: return "TOKEN";
//             break;
    // }
// }

#endif // CONSTANTS_H
