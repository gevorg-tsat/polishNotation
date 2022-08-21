#include "calc.h"
#include <math.h>
#include <stdio.h>
#include <string.h>


int calc_expr_postfix(char *expression, double *result) {
    if (!expression) {
        return null_data_error;
    }
    if (!result) {
        return result_pointer_error;
    }


    return success;
}

bool is_number(char *current_pos) {
    double x;
    return sscanf(current_pos, "%lf", &x);
}
