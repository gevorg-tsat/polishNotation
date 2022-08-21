#include "parsing.h"
#include <stdio.h>
#include "calc.h"
#include "operation_stack.h"

int main() {
    char *str_temp;
    int n = 0;
    str_temp = malloc(sizeof(char));
    int flag = 1;
    while (flag) {
        n++;
        str_temp = realloc(str_temp, n*sizeof(char));
        scanf("%c", &str_temp[n-1]);
        if (str_temp[n-1] == '\n') {
        str_temp[n-1] = '\0';
        flag = 0;
        }
    }
    str_temp = realloc(str_temp, 2*n*sizeof(char));
    spaces_fix(str_temp);
    char *str = str_temp;
    if (brackets(str)) {
        printf("brackets error");
        return 1;
    }
    unar_nul(str, strlen(str));

    if (first_last_sym(str, strlen(str))) {
        printf("syntax error");
        return 1;
    }
    if (operator_check(str, strlen(str), 1) == 0) {
        printf("syntax error");
        return 1;
    }
    str = str_to_polish(str);
    printf("%s\n", str);
    operation_stack* stack = stack_from_expression(str);
    double exp_result;
    int res = calc_exp_postfix(stack, -1, &exp_result);
    if (res) {
        return -1;
    }
    printf("\n%lf\n", exp_result);
    return 0;
}
