#include "print_graph.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define eps 2. / 48.



void print_graph(double* data) {
    char A[OSY][OSX];
    double y_step = (Y_UP - Y_DOWN) / OSY; 
    for (int i = 0; i < OSX; i++) {
        for (int j = 0; j < OSY; j++) {
            if ((data[i] > Y_DOWN + j*y_step) && (data[i] < Y_DOWN + (j + 1) * y_step))
                A[i][j] = '*';
            else 
                A[i][j] = '.';
        }
    }
    for (int i = 0; i < OSX; i++) {
        for (int j = 0; j < OSY; j++) {
            printf("%lf", A[i][j]);
        }
        printf("\n");
    }
}