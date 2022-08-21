#include "operation_stack.h"
#include <stdlib.h>

int mul_int(int number, int coefficient) {
    return number * coefficient;
}
int div_int(int number, int coefficeint) {
    return number / coefficeint;
}
operation_stack *init_operation_stack(int init_capacity) {
    operation_stack *op_stack
        = (operation_stack *)malloc(sizeof(operation_stack));

    if (!op_stack) {
        return NULL;
    }

    if (init_capacity < 1) {
        init_capacity = 1;
    }
    op_stack->operations_list
        = (operation_node *)malloc(sizeof(operation_node) * init_capacity);
    if (!op_stack->operations_list) {
        free(op_stack);
        return NULL;
    }
    op_stack->size      = 0;
    op_stack->_capacity = init_capacity;

    return op_stack;
}

int operation_stack_push_back(operation_stack *op_stack,
                              const operation_node operation) {
    if (!op_stack) {
        return null_data_error;
    }
    if (op_stack->_capacity < 1) {
        return type_structure_violating;
    }
    if (op_stack->_capacity == op_stack->size) {
        int res = grow_operation_stack(op_stack);
        if (!res) {
            return res;
        }
    }

    return operation_node_copy(&op_stack->operations_list[ op_stack->size++ ],
                               operation);
}

int reallocate_peration_stack(operation_stack *op_stack, int coefficient,
                              func fun) {
    if (op_stack->_capacity == 0) {
        op_stack->_capacity = 1;
    }
    operation_node *temp_buffer = realloc(
        op_stack->operations_list, op_stack->_capacity * sizeof(operation_node)
                                       * fun(op_stack->_capacity, coefficient));
    if (!temp_buffer) {
        return memory_allocation_error;
    }
    op_stack->_capacity       = fun(op_stack->_capacity, coefficient);
    op_stack->operations_list = temp_buffer;
    return success;
}

int grow_operation_stack(operation_stack *op_stack) {
    return reallocate_peration_stack(op_stack, 2, mul_int);
}

int shrink_operation_stack(operation_stack *op_stack) {
    return reallocate_peration_stack(op_stack, 2, div_int);
}

int operation_node_copy(operation_node *operation, const operation_node copy) {
    operation->operation = copy.operation;
    return success;
}

operation_node *top_operation_stack(operation_stack *op_stack) {
    if (!op_stack) {
        return NULL;
    }
    return &op_stack->operations_list[ op_stack->size - 1 ];
}

bool empty_operation_stack(operation_stack *op_stack) {
    return op_stack->size;
}

int pop_operation_stack(operation_stack *op_stack) {
    if (op_stack->size == 0) {
        return success;
    }
    if (--op_stack->size * 4 <= op_stack->_capacity) {
        int res = shrink_operation_stack(op_stack);
        if (!res) {
            return res;
        }
    }
    return success;
}

void destroy(operation_stack **op_stack) {
    free((*op_stack)->operations_list);
    free(*op_stack);
    *op_stack = NULL;
}
