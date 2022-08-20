#ifndef SRC_STACK_H_
#define SRC_STACK_H_
#include <stdlib.h>
#include <string.h>

struct node {
    struct node *next;
    char *data;
    int prior;
};

int prior_check(char *str);
struct node* init(int prior, char data);
struct node* push(struct node *root, char data, int prior);
struct node* pop(struct node *root);
void destroy(struct node *root);

#endif  // SRC_STACK_H_
