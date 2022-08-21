#include "print_graph.h"
#include "calc.h"
#include "operation_stack.h"
#include <math.h>
#include <stdio.h>

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


void print_graph(double* data) {
    char A[OSY][OSX];
    double y_step = ((double)Y_UP - Y_DOWN) / OSY; 
    for (int i = 0; i < OSX; i++) {
        for (int j = 0; j < OSY; j++) {
            if ((data[i] >= Y_DOWN + j*y_step) && (data[i] <+ Y_DOWN + (j + 1) * y_step))
                A[j][i] = '*';
            else 
                A[j][i] = '.';
        }
    }
    for (int i = OSY - 1; i >= 0; i--) {
        for (int j = 0; j < OSX; j++) {
            printf("%c", A[i][j]);
        }
        printf("\n");
    }
}