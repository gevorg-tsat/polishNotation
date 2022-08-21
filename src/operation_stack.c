#include "operation_stack.h"
#include <stdlib.h>

// функция умножения целых чисел
int mul_int(int number, int coefficient) {
    return number * coefficient;
}

// функция деления целых чисел
int div_int(int number, int coefficeint) {
    return number / coefficeint;
}

// конструктор для стека операций и операторов
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

// создание нового стека копированием другого
operation_stack* copy_operation_stack(const operation_stack copy) {
    operation_stack* new_operation_stack = (operation_stack*)malloc(sizeof(operation_stack));
    if (!new_operation_stack) {
        return NULL;
    }
    new_operation_stack->size = copy.size;
    new_operation_stack->_capacity = copy._capacity;
    new_operation_stack->operations_list = copy_operation_node_list(copy);
    if (!new_operation_stack->operations_list) {
        free(new_operation_stack);
        return NULL;
    }
    return new_operation_stack;
}

// копирование содержимого контейнера стека
operation_node* copy_operation_node_list(const operation_stack copy) {
    operation_node* operation_node_list = (operation_node*)malloc(sizeof(operation_node) * copy._capacity);
    for (int i = 0; i < copy.size; ++i) {
        operation_node_copy(&operation_node_list[i], copy.operations_list[i]);
    }
    return operation_node_list;
}

//  вставка нового элемента в конец стека
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
        if (res) {
            return res;
        }
    }

    return operation_node_copy(&op_stack->operations_list[ op_stack->size++ ],
                               operation);
}

// перевыделение памяти контейнера стека
int reallocate_operation_stack(operation_stack *op_stack, int coefficient,
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
//  удвоение памяти выделенной для контейнера стека
int grow_operation_stack(operation_stack *op_stack) {
    return reallocate_operation_stack(op_stack, 2, mul_int);
}

//  уменьшение в два раза памяти выделенной для контейнера стека
int shrink_operation_stack(operation_stack *op_stack) {
    return reallocate_operation_stack(op_stack, 2, div_int);
}

// копирование одного узла стека в другой
int operation_node_copy(operation_node *operation, const operation_node copy) {
    operation->type      = copy.type;
    switch (operation->type) {
    case value: {
        operation->value     = copy.value;
        break;
    }
    case operator: {
    }
    case function: {
        operation->operation = copy.operation;
        break;
    }
    case variable: {
        operation->variable = copy.variable;
        break;
    }
    default:
        break;
    }

    return success;
}

// возврат указателя на верхний элемент стека
operation_node *top_operation_stack(operation_stack *op_stack) {
    if (!op_stack) {
        return NULL;
    }
    return &op_stack->operations_list[ op_stack->size - 1 ];
}

// провекра стека на пустоту
bool empty_operation_stack(operation_stack *op_stack) {
    return op_stack->size;
}

// удаление верхнего элемента стека
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

// деструктор стека
void destroy_operation_stack(operation_stack **op_stack) {
    free((*op_stack)->operations_list);
    free(*op_stack);
    *op_stack = NULL;
}

// реверс стека по указателю
void reverse_operation_stack(operation_stack *op_stack) {
    for (int i = 0; i < op_stack->size / 2; ++i) {
        operation_node tmp;
        operation_node_copy(&tmp, op_stack->operations_list[i]);
        operation_node_copy(&op_stack->operations_list[i], op_stack->operations_list[op_stack->size - 1 - i]);
        operation_node_copy(&op_stack->operations_list[op_stack->size - 1 - i], tmp);
    }
}
