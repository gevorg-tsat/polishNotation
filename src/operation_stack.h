#ifndef SRC_OPERATION_STACK_H_
#define SRC_OPERATION_STACK_H_
#include "calc.h"

#ifndef OPERATION_TYPE
#define OPERATION_TYPE
typedef enum operation_type {
    value = 1,
    operator= 2,
    function = 3,
} operation_type;

typedef struct operation_node {
    operation_type type;
    union {
        OPERATORS operation;
        double value;
    };

} operation_node;

typedef struct operation_stack {
    operation_node *operations_list;
    int _capacity;
    int size;
} operation_stack;


#endif  //  OPERATION_TYPE


typedef int (*func)(int number, int coefficient);

int mul_int(int number, int coefficient);
int div_int(int number, int coefficeint);

operation_stack *init_operation_stack(int init_capacity);
int operation_stack_push_back(operation_stack *op_stack,
                              const operation_node operation);

int reallocate_peration_stack(operation_stack *op_stack, int coefficient,
                              func fun);
int grow_operation_stack(operation_stack *op_stack);
int shrink_operation_stack(operation_stack *op_stack);

int operation_node_copy(operation_node *operation, const operation_node copy);

operation_node *top_operation_stack(operation_stack *op_stack);

bool empty_operation_stack(operation_stack *op_stack);

int pop_operation_stack(operation_stack *op_stack);

void destroy(operation_stack **op_stack);
#endif  //  SRC_OPERATION_STACK_H_
