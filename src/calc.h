#ifndef SRC_CALC_H_
#define SRC_CALC_H_
#include <stdbool.h>

typedef enum ERRORS {
    success                  = 0,
    null_data_error          = 1,
    result_pointer_error     = 2,
    type_structure_violating = 4,
    memory_allocation_error  = 5
} ERRORS;

typedef enum OPERATORS {
    plus    = '+',
    minus   = '-',
    mul     = '*',
    divide  = '/',
    sinus   = 's',
    cosinus = 'c',
    tangens = 't',
    ctg     = 'g',
    sqroot  = 'q',
    ln      = 'l',
    number  = 'n',
} OPERATORS;

int calc_expr_postfix(char *expression, double *result);

bool is_number(char *expression);


#endif  //  SRC_CALC_H_
