#include "calc.h"
#include "operation_stack.h"
#include <math.h>
#include <stdio.h>
#include <string.h>
#define INIT_CAPACITY 1

// создание стека из выражения по постфиксной нотации
operation_stack *stack_from_expression(char *expression) {
    if (!expression) {
        return NULL;
    }
    operation_stack *stack = init_operation_stack(INIT_CAPACITY);
    while (*expression) {
        while (is_space(expression) && !is_eof(expression)) {
            ++expression;
        }
        if (is_eof(expression)) {
            break;
        }
        if (is_x(expression)) {
            operation_node new_node = {.type = variable, .variable = 'x'};
            int res = operation_stack_push_back(stack, new_node);
            if (res) {
                return NULL;
            }
            char* tmp = strchr(expression, ' ');
            if (!tmp) {
                return stack;
            }
            expression = tmp;
            continue;
        }
        if (is_number(expression)) {
            double number = 0;
            sscanf(expression, "%lf", &number);
            operation_node new_node = {.value = number, .type = value};
            int res = operation_stack_push_back(stack, new_node);
            if (res) {
                return NULL;
            }
            char* tmp = strchr(expression, ' ');
            if (!tmp) {
                return stack;
            }
            expression = tmp;
            continue;
        }
        if (is_function(expression)) {
            char func = '\0';
            sscanf(expression, "%c", &func);
            operation_node new_node = {.type = function, .operation = func};
            int res = operation_stack_push_back(stack, new_node);
            if (res) {
                return NULL;
            }
            char* tmp = strchr(expression, ' ');
            if (!tmp) {
                return stack;
            }
            expression = tmp;
            continue;
        }
        if (is_operator(expression)) {
            char oper = '\0';
            sscanf(expression, "%c", &oper);
            operation_node new_node = {.type = operator, .operation = oper };
            int res = operation_stack_push_back(stack, new_node);
            if (res) {
                return NULL;
            }
            char* tmp = strchr(expression, ' ');
            if (!tmp) {
                return stack;
            }
            expression = tmp;
            continue;
        }
            //++expression;
        
    }
    return stack;
}

// проверка следующего элемента в строке на число
bool is_number(const char *current_pos) {
    double x;
    return sscanf(current_pos, "%lf", &x);
}

// проверка следующего элемента в строке на переменную Х
bool is_x(const char *current_pos) {
    char x;
    sscanf(current_pos, "%c", &x);
    if (x == 'x') {
        return true;
    }
    return false;
}

// проверка следующего элемента в строке на функцию
bool is_function(const char *current_pos) {
    char x;
    sscanf(current_pos, "%c", &x);
    char *functions = "sctgql";
    if (strchr(functions, x)) {
        return true;
    }
    return false;
}

// проверка следующего элемента в строке на бинарный оператор
bool is_operator(const char *current_pos) {
    char x;
    sscanf(current_pos, "%c", &x);
    char *functions = "*/+-";
    if (strchr(functions, x)) {
        return true;
    }
    return false;
}

// проверка следующего элемента в строке на пробел
bool is_space(const char *current_pos) {
    char x;
    sscanf(current_pos, "%c", &x);
    if (x == ' ') {
        return true;
    }
    return false;
}

// проверка строки на конец
bool is_eof(const char *current_pos) {
    char x;
    int check = sscanf(current_pos, "%c", &x);
    if (check == EOF) {
        return true;
    }
    return false;
}

// вычисление результата бинарного оператора
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

// вычисление результата унарной функции
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

// вычисление выражения по постфиксной нотации, помещенной в стек
int calc_exp_postfix(const operation_stack * expression, double var, double* expression_result) {
    if (!expression) {
        return null_data_error;
    }
    operation_stack* copy_expression = copy_operation_stack(*expression);
    operation_stack* operands = init_operation_stack(INIT_CAPACITY);
    reverse_operation_stack(copy_expression);
    // for (int i = 0; i < copy_expression->size; ++i) {
    //     printf("%d %c", copy_expression->operations_list[i].type, (char)copy_expression->operations_list[i].value);
    // }
    // printf("\n");
    // for (int i = 0; i < 5; ++i) {
    //     printf("%d \n", top_operation_stack(copy_expression)->type);
    //     pop_operation_stack(copy_expression);
    // }
    while (empty_operation_stack(copy_expression)) {
        operation_node oper = *top_operation_stack(copy_expression);
        printf("type = %d\n", oper.type);
        int res = pop_operation_stack(copy_expression);
        if (res) {
            return res;
        }
        switch (oper.type) {
        case variable: {
            operation_node tmp = {.value = var, .type = value};
            printf("variable = %c\n", oper.variable);
            operation_stack_push_back(operands, tmp);
            break;
        }
        case value: {
            int res = operation_stack_push_back(operands, oper);
            printf("value = %f\n,", oper.value);
            if (res) {
                return res;
            }
            break;
        }
        case operator: {
            double right_operand = top_operation_stack(operands)->value;
            printf("operator = %c\n", oper.operation);
            printf("right operand = %lf ", right_operand);
            int res = pop_operation_stack(operands);
            if (res) {
                return res;
            }
            double left_operand = top_operation_stack(operands)->value;
            printf("left operand = %lf\n", left_operand);
            res = pop_operation_stack(operands);
            if (res) {
                return res;
            }
            OPERATORS operation = oper.operation;
            double result = operator_func(left_operand, right_operand, operation);
            operation_node tmp = {.type = value, .value = result};
            res = operation_stack_push_back(operands, tmp);
            if (res) {
                return res;
            }
            break;
        }
        case function: {
            printf("function = %c\n", oper.operation);
            printf("value = %c\n", oper.variable);
            double unar_operand = top_operation_stack(operands)->value;
            int res = pop_operation_stack(operands);
            if (res) {
                return res;
            }
            OPERATORS operation = oper.operation;
            double result = math_func(unar_operand, operation);
            operation_node tmp = {.type = value, .value = result};
            res = operation_stack_push_back(operands, tmp);
            if (res) {
                return res;
            }
            break;
        }
        default:
            break;
        }
    }
    *expression_result = top_operation_stack(operands)->value;
    destroy_operation_stack(&operands);
    destroy_operation_stack(&copy_expression);
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
