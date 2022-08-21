#include "print_graph.h"
#include "calc.h"
#include "operation_stack.h"
#include <math.h>


void fill_array(double* array, char* expression) {
    if (!array || !expression) {
        return ;
    }
    operation_stack* stack = stack_from_expression(expression);
    for (int i = 0; i < LENGTH; ++i) {
        calc_exp_postfix(stack, 0 + STEP * i, &array[i]);
    }

    destroy_operation_stack(&stack);
}