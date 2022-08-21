#include "calc.h"
#include "operation_stack.h"
#include <stdio.h>

int main() {
    char *str = "4 5 x / +";

    operation_stack* stack = stack_from_expression(str);
    // printf("value = %lf\n", stack->operations_list[0].value);
    // printf("value = %lf\n", stack->operations_list[1].value);
    // printf("variable = %c\n", stack->operations_list[2].variable);
    // printf("operator = %c\n", stack->operations_list[3].operation);
    // printf("function = %c\n", stack->operations_list[4].operation);


    // for (int i = 0; i < stack->size; ++i) {
    //     printf("%d %c", stack->operations_list[i].type, (char)stack->operations_list[i].value);
    // }
    // printf("\n");
    // for (int i = 0; i < 5; ++i) {
    //     printf("%d \n", top_operation_stack(stack)->type);
    //     pop_operation_stack(stack);
    // }

    double exp_result;
    int res = calc_exp_postfix(stack, 3, &exp_result);
    if (res) {
        return -1;
    }
    printf("\n%lf\n", exp_result);
    
    return 0;
}

/*
    value = 1,
    operator= 2,
    function = 3,
    variable = 4,
*/