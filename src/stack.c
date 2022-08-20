#include "stack.h"

struct node* init(int prior, char data) {
    struct node *tmp = malloc(sizeof(struct node));
    tmp -> next = 0;
    tmp -> prior = prior;
    tmp -> data = data;
    return tmp;
}

struct node* push(struct node *root, char data, int prior) {
    struct node *tmp = malloc(sizeof(struct node));
    tmp -> next = root;
    tmp -> data = data;
    root = tmp;
    return root;
}



struct node* pop(struct node *root) {
    struct node *tmp = root;
    root = tmp -> next;
    tmp -> next = 0;
    free(tmp);
    return root;
}

void destroy(struct node *root) {
    while (root != 0) {
        struct node *tmp = (root) -> next;
        free(root);
        root = tmp;
    }
}
