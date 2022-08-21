#include "calc.h"
#include "operation_stack.h"
#include <math.h>
#include <stdio.h>
#include <string.h>
#define INIT_CAPACITY 1

operation_stack *stack_from_expression(char *expression) {
    if (!expression) {
        return NULL;
    }
    operation_stack *stack = init_operation_stack(INIT_CAPACITY);
    while (*expression) {
        while (is_space(expression)) {
            ++expression;
        }
        if (is_eof(expression)) {
            break;
        }
        if (is_x(expression)) {
            operation_node new_node = {.type = variable, .variable = 'x'};
            int res = operation_stack_push_back(stack, new_node);
            if (!res) {
                return NULL;
            }
            expression = strchr(expression, ' ');
        }
        if (is_number(expression)) {
            double number = 0;
            sscanf(expression, "%lf", &number);
            operation_node new_node = {.value = number, .type = value};
            int res = operation_stack_push_back(stack, new_node);
            if (!res) {
                return NULL;
            }
            expression = strchr(expression, ' ');
        }
        if (is_function(expression)) {
            char func = '\0';
            sscanf(expression, "%c", &func);
            operation_node new_node = {.type = function, .operation = func};
            int res = operation_stack_push_back(stack, new_node);
            if (!res) {
                return NULL;
            }
            expression = strchr(expression, ' ');
        }
        if (is_operator(expression)) {
            char oper = '\0';
            sscanf(expression, "%c", &oper);
            operation_node new_node = {.type = operator, .operation = oper };
            int res = operation_stack_push_back(stack, new_node);
            if (!res) {
                return NULL;
            }
            expression = strchr(expression, ' ');
        }
        ++expression;
    }
    return stack;
}

bool is_number(const char *current_pos) {
    double x;
    return sscanf(current_pos, "%lf", &x);
}

bool is_x(const char *current_pos) {
    char x;
    sscanf(current_pos, "%c", &x);
    if (x == 'x') {
        return true;
    }
    return false;
}

bool is_function(const char *current_pos) {
    char x;
    sscanf(current_pos, "%c", &x);
    char *functions = "sctgqln";
    if (strchr(functions, x)) {
        return true;
    }
    return false;
}

bool is_operator(const char *current_pos) {
    char x;
    sscanf(current_pos, "%c", &x);
    char *functions = "*/+-";
    if (strchr(functions, x)) {
        return true;
    }
    return false;
}

bool is_space(const char *current_pos) {
    char x;
    sscanf(current_pos, "%c", &x);
    if (x == ' ') {
        return true;
    }
    return false;
}
bool is_eof(const char *current_pos) {
    char x;
    int check = sscanf(current_pos, "%c", &x);
    if (check == EOF) {
        return true;
    }
    return false;
}

double operator_func(double left_operand, double right_operand, OPERATORS operation) {
    switch (operation) {
        case '+': {
            return left_operand + right_operand;
        }
        case '-': {
            return left_operand - right_operand;
        }
        case '*': {
            return left_operand * right_operand;
        }
        case '/': {
            return left_operand / right_operand;
        }
        default: {
            break;
        }
    }
    return 0;
}

double math_func(double unar_operand, OPERATORS operation) {
    switch (operation) {
    case 's': {
        return sin(unar_operand);
    }
    case 'c': {
        return cos(unar_operand);
    }
    case 't': {
        return tan(unar_operand);
    }
    case 'g': {
        return cos(unar_operand) / sin(unar_operand);
    }
    case 'q': {
        return sqrt(unar_operand);
    }
    case 'l': {
        return log(unar_operand);
    }
    default: {
        break;
    }
    }
    return 0;
}
/*
    ln      = 'l',
*/

int calc_exp_postfix(const operation_stack * expression, double var) {
    if (!expression) {
        return null_data_error;
    }
    operation_stack* copy_expression = copy_operation_stack(*expression);
    operation_stack* operands = init_operation_stack(INIT_CAPACITY);
    reverse_operation_stack(copy_expression);
    while (!empty_operation_stack(copy_expression)) {
        switch (top_operation_stack(copy_expression)->type) {
        case value: {
            int res = operation_stack_push_back(operands, *top_operation_stack(copy_expression));
            if (!res) {
                return res;
            }
            res = pop_operation_stack(copy_expression);
            if (!res) {
                return res;
            }
            break;
        }
        case operator: {
            double right_operand = top_operation_stack(operands)->value;
            int res = pop_operation_stack(operands);
            if (!res) {
                return res;
            }
            double left_operand = top_operation_stack(operands)->value;
            res = pop_operation_stack(operands);
            if (!res) {
                return res;
            }
            OPERATORS operation = top_operation_stack(copy_expression)->operation;
            double result = operator_func(left_operand, right_operand, operation);
            operation_node tmp = {.type = value, .value = result};
            res = operation_stack_push_back(operands, tmp);
            if (!res) {
                return res;
            }
            res = pop_operation_stack(copy_expression);
            if (!res) {
                return res;
            }
            break;
        }
        case function: {
            double unar_operand = top_operation_stack(operands)->value;
            int res = pop_operation_stack(operands);
            if (!res) {
                return res;
            }
            OPERATORS operation = top_operation_stack(copy_expression)->operation;
            double result = math_func(unar_operand, operation);
            operation_node tmp = {.type = value, .value = result};
            res = operation_stack_push_back(operands, tmp);
            if (!res) {
                return res;
            }
            res = pop_operation_stack(copy_expression);
            if (!res) {
                return res;
            }
            break;
        }
        case variable: {
            operation_node tmp = *top_operation_stack(copy_expression);
            tmp.type = value;
            tmp.value = var;
            operation_stack_push_back(operands, tmp);
            int res = pop_operation_stack(copy_expression);
            if (!res) {
                return res;
            }
            break;
        }
        default:
            break;
        }
    }

    return success;
}
/*
    value = 1,
    operator= 2,
    function = 3,
    variable = 4,
*/

/*
1_op – ,
2_op – .
index

cos(4 + 5 / x)


4 5 x / + c

16+x


TODO:
стек для операндов отдельный
copy_stack
// индексы для операторов
//  
*/
