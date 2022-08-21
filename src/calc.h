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

int calc_expr_postfix(char *expression, double *result, double x);

bool is_number(char *current_pos);
bool is_function(char *current_pos);
bool is_operator(char *current_pos);
bool is_space(char *current_pos);
bool is_eof(char *current_pos);


#endif  //  SRC_CALC_H_
