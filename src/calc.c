#include "calc.h"
#include "operation_stack.h"
#include <math.h>
#include <stdio.h>
#include <string.h>
#define INIT_CAPACITY 1

int calc_expr_postfix(char *expression, double *result, double x) {
    if (!expression) {
        return null_data_error;
    }
    if (!result) {
        return result_pointer_error;
    }
    operation_stack *stack = init_operation_stack(INIT_CAPACITY);
    while (*expression) {
        while (is_space(expression)) {
            ++expression;
        }
        if (is_number(expression)) {
            double number = 0;
            sscanf(expression, "%lf", &number);
            operation_node new_node = {.value = number, .type = value};
            int res = operation_stack_push_back(stack, new_node);
            if (!res) {
                return res;
            }
            expression = strchr(expression, ' ');
        }
        if (is_function(expression)) {
            char func = '\0';
            sscanf(expression, "%c", &func);
            operation_node new_node = {.type = function, .operation = func};
            int res = operation_stack_push_back(stack, new_node);
            if (!res) {
                return res;
            }
            expression = strchr(expression, ' ');
        }
        if (is_operator(expression)) {
            char oper = '\0';
            sscanf(expression, "%c", &oper);
            operation_node new_node = {.type = operator, .operation = oper };
            int res = operation_stack_push_back(stack, new_node);
            if (!res) {
                return res;
            }
            expression = strchr(expression, ' ');
        }
        ++expression;
    }


    return success;
}

bool is_number(char *current_pos) {
    double x;
    return sscanf(current_pos, "%lf", &x);
}

bool is_function(char *current_pos) {
    char x;
    sscanf(current_pos, "%c", &x);
    char *functions = "sctgqln";
    if (strchr(functions, x)) {
        return true;
    }
    return false;
}

bool is_operator(char *current_pos) {
    char x;
    sscanf(current_pos, "%c", &x);
    char *functions = "*/+-";
    if (strchr(functions, x)) {
        return true;
    }
    return false;
}

bool is_space(char *current_pos) {
    char x;
    sscanf(current_pos, "%c", &x);
    if (x == ' ') {
        return true;
    }
    return false;
}
bool is_eof(char *current_pos) {
    char x;
    int check = sscanf(current_pos, "%c", &x);
    if (check == EOF) {
        return true;
    }
    return false;
}