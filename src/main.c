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
    if (!temp) {
            return 1;
        }
    str = temp;
    spaces_fix(str);
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
    double* array = (double*)malloc(sizeof(double) * LENGTH);
    fill_array(array, str);

    print_graph(array);

    return 0;
}
