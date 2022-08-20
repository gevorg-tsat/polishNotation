#include <stack.h>

int prior(char *str);
char* str_to_polish(char *str);
void spaces_fix(char *str);
struct node* stacking(struct node* root, int prior, char c, char *polish, int *n);