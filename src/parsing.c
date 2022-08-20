#include "parsing.h"

int prior(char *str) {
    if (strcmp(str, ")") == 0 || strcmp(str, "(") == 0)
        return -1;
    
}

void spaces_fix(char *str) {
    char *str_space = strchr(str, ' ');
    while (str_space != NULL) {
        for (int i = 0; str_space[i] != '\0'; i++)
            str_space[i] = str_space[i + 1];
        str_space = strchr(str, ' ');
    }
}

int brackets(char *str) {
    int num = 0, i = 0;
    while(str[i] != '\0') {
        if (str[i] == '(')
            num++;
        if (str[i] == ')')
            num--;
        if (num < 0)
            return i;
        i++;
    }
    return num;
}

char* str_to_polish(char *str) {
    int i = 0, n = 0;
    char *polish = calloc(3 * strlen(str) + 1, sizeof(char));
    char *first = "+-";
    char *second = "*/";
    int flag_num = 0;
    int flag_dot = 0;
    char *numbers = "0123456789x";
    struct node *root = NULL;
    while (str[i] != '\0') {
        if (str[i] == '.' && !flag_dot) {
            polish[n++] = str[i];
            flag_dot = 1;
        }
        else if (str[i] == '.' && flag_dot) {
            free(polish);
            return NULL;
        } 
        else if (strstr(numbers, str[i]) && flag_num == 0) {
            polish[n++] = ' ';
            polish[n++] = str[i];
            flag_num = 1;
        } else if (strstr(numbers, str[i]) && flag_num == 1) {
            polish[n++] = str[i];
        } else if (strchr(str[i], first) != NULL) {
            flag_dot = flag_num = 0;
            if (root == NULL) {
                root = init(1, str[i]);
            } else
                root = push(root, str[i], 1);
        } else if (strchr(str[i], first) != NULL) {
            flag_dot = flag_num = 0;
            if (root = NULL)
                root = init(2, str[i]);
            else {

            }
        }

    }
}
