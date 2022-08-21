#include "parsing.h"
#include <stdio.h>
#include "calc.h"
#include "operation_stack.h"
#include "print_graph.h"

int main() {
    char *str;
    int n = 0;
    str = malloc(sizeof(char));
    int flag = 1;
    printf("y = ");
    while (flag) {
        n++;
        char *temp = realloc(str, n*sizeof(char));
        if (!temp) {
            return 1;
        }
        str = temp;
        scanf("%c", &str[n-1]);
        if (str[n-1] == '\n') {
        str[n-1] = '\0';
        flag = 0;
        }
    }
    char *temp = realloc(str, 2*n*sizeof(char));
    free(str);
    if (!temp) {
            return 1;
        }
    str = temp;
    spaces_fix(str);
    unar_nul(str, strlen(str));
    if (brackets(str)) {
        printf("brackets error\n");
        return 1;
    }

    if (first_last_sym(str, strlen(str))) {
        printf("syntax error\n");
        return 1;
    }
    if (operator_check(str, strlen(str), 1) == 0) {
        printf("syntax error\n");
        return 1;
    }
    str = str_to_polish(str);
    double* array = (double*)malloc(sizeof(double) * LENGTH);
    fill_array(array, str);

    print_graph(array);
    free(array);
    free(str);
    return 0;
}
