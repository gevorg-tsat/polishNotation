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

#ifndef OPERATION_TYPE
#define OPERATION_TYPE
typedef enum operation_type {
    value = 1,
    operator= 2,
    function = 3,
    variable = 4,
} operation_type;

typedef struct operation_node {
    operation_type type;
    union {
        OPERATORS operation;
        double value;
        char variable;
    };
} operation_node;

typedef struct operation_stack {
    operation_node *operations_list;
    int _capacity;
    int size;
} operation_stack;


#endif  //  OPERATION_TYPE

double operator_func(double left_operand, double right_operand, OPERATORS operation);
double math_func(double unar_operand, OPERATORS operation);


// typedef int (*func)(int number, int coefficient);

int calc_exp_postfix(const operation_stack * expression, double var, double* expression_result);
operation_stack *stack_from_expression(char *expression);

bool is_number(const char *current_pos);
bool is_x(const char *current_pos);
bool is_function(const char *current_pos);
bool is_operator(const char *current_pos);
bool is_space(const char *current_pos);
bool is_eof(const char *current_pos);


#endif  //  SRC_CALC_H_
