#ifndef SRC_PRINT_GRAPH_H_
#define SRC_PRINT_GRAPH_H_
#define OSX 80
#define OSY 25
#define X_LEFT 0
#define X_RIGHT 4*M_PI
#define Y_UP 1
#define Y_DOWN -1
#include <math.h>
#include <stdio.h>
#define LENGTH 80
#define STEP 4 * M_PI / LENGTH


void fill_array(double* array, char* expression);
void print_graph(double* data);

#endif  // SRC_PRINT_GRAPH_H_