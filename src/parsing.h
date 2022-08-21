#include "stack.h"
#include <stdio.h>

int sign_check(char* str, int n, int biflag);
int prior(char *str);
char* str_to_polish(char *str);
void spaces_fix(char *str);
struct node* stacking(struct node* root, int prior, char c, char *polish, int *n);
int brackets(char *str);
void unar_nul(char* str, int n);
int first_last_sym(char* str, int n);
int operator_check(char* str, int n, int flag_next);