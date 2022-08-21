#include "parsing.h"


void spaces_fix(char *str) {
    char *str_space = strstr(str, " ");
    while (str_space != NULL) {
        for (int i = 0; str_space[ i ] != '\0'; i++)
            str_space[ i ] = str_space[ i + 1 ];
        str_space = strstr(str, " ");
    }
}

int brackets(const char *str) {
    int num = 0, i = 0;
    while (str[ i ] != '\0') {
        if (str[ i ] == '(') num++;
        if (str[ i ] == ')') num--;
        if (num < 0) return num;
        i++;
    }
    return num;
}


int sign_check(char *str, int n, int biflag) {
    int flag   = 0;
    char *symb = "*/+-";
    char *nums = "1234567890";
    for (int i = 0; i < n; i++) {
        if (!flag) {
            if (str[ i ] == 'c'
                && ((str + i) == strstr((str + i), "ctg(")
                    || (str + i) == strstr((str + i), "cos("))) {
                i += 2;
            } else if (str[ i ] == 's'
                       && (str + i) == strstr((str + i), "sin(")) {
                i += 2;
            } else if (str[ i ] == 's'
                       && (str + i) == strstr((str + i), "sqrt(")) {
                i += 3;
            } else if (str[ i ] == 't'
                       && (str + i) == strstr((str + i), "tan(")) {
                i += 2;
            } else if (str[ i ] == 'l'
                       && (str + i) == strstr((str + i), "ln(")) {
                i += 1;
            } else if ((strchr(symb, str[ i ]) != NULL && !biflag)
                       || str[ i ] == '(') {
                flag = sign_check((str + i + 1), 1, 1);
            } else if ((str[ i ] == ')' && !biflag)
                       || (strchr(nums, str[ i ]) != NULL && str[ i + 1 ] != '('
                           && str[ i - 1 ] != ')')
                       || (str[ i ] == '.'
                           && strchr(nums, str[ i + 1 ]) != NULL)) {
            } else if (str[ i ] == 'x' && (i == 0 || i == n - 1)) {
            } else if (str[ i ] == 'x' && strchr(nums, str[ i + 1 ]) == NULL
                       && strchr(nums, str[ i - 1 ]) == NULL
                       && str[ i + 1 ] != '(' && str[ i - 1 ] != ')') {
            } else {
                flag = 1;
                break;
            }
        }
    }
    return flag;
}

char *str_to_polish(char *str) {
    int i = 0, n = 0;
    char *polish      = calloc(3 * strlen(str) + 1, sizeof(char));
    char *first       = "+-";
    char *second      = "*/";
    int flag_num      = 0;
    int flag_dot      = 0;
    char *numbers     = "0123456789x";
    struct node *root = NULL;
    while (str[ i ] != '\0') {
        if (str[ i ] == '.' && !flag_dot) {
            polish[ n++ ] = str[ i ];
            flag_dot      = 1;
        } else if (str[ i ] == '.' && flag_dot) {
            free(polish);
            return NULL;
        } else if (strchr(numbers, str[ i ]) && flag_num == 0) {
            polish[ n++ ] = ' ';
            polish[ n++ ] = str[ i ];
            flag_num      = 1;
        } else if (strchr(numbers, str[ i ]) && flag_num == 1) {
            polish[ n++ ] = str[ i ];
        } else if (strchr(first, str[ i ]) != NULL) {
            flag_dot = flag_num = 0;
            root                = stacking(root, 1, str[ i ], polish, &n);
        } else if (strchr(second, str[ i ]) != NULL) {
            flag_dot = flag_num = 0;
            root                = stacking(root, 2, str[ i ], polish, &n);
        } else if (strstr(str + i, "sin") == str + i) {
            flag_dot = flag_num = 0;
            root                = stacking(root, 3, 's', polish, &n);
            i += 2;
        } else if (strstr(str + i, "cos") == str + i) {
            flag_dot = flag_num = 0;
            root                = stacking(root, 3, 'c', polish, &n);
            i += 2;
        } else if (strstr(str + i, "tan") == str + i) {
            flag_dot = flag_num = 0;
            root                = stacking(root, 3, 't', polish, &n);
            i += 2;
        } else if (strstr(str + i, "ctg") == str + i) {
            flag_dot = flag_num = 0;
            root                = stacking(root, 3, 'g', polish, &n);
            i += 2;
        } else if (strstr(str + i, "sqrt") == str + i) {
            flag_dot = flag_num = 0;
            root                = stacking(root, 3, 'q', polish, &n);
            i += 3;
        } else if (strstr(str + i, "ln") == str + i) {
            flag_dot = flag_num = 0;
            root                = stacking(root, 3, 'l', polish, &n);
            i += 1;
        } else if (str[ i ] == '(') {
            flag_dot = flag_num = 0;
            root                = stacking(root, 0, '(', polish, &n);
        } else if (str[ i ] == ')') {
            flag_dot = flag_num = 0;
            while (root->data != '(') {
                polish[ n++ ] = ' ';
                polish[ n++ ] = root->data;
                root          = pop(root);
            }
            root = pop(root);
            if (root && (root->prior == 3)) {
                polish[ n++ ] = ' ';
                polish[ n++ ] = root->data;
                root          = pop(root);
            }
        }
        i++;
    }
    while (root) {
        polish[ n++ ] = ' ';
        polish[ n++ ] = root->data;
        root          = pop(root);
    }
    polish[ n++ ] = '\0';
    for (int j = 0; polish[ j ] != '\0'; j++) polish[ j ] = polish[ j + 1 ];
    return polish;
}

struct node *stacking(struct node *root, int prior, char c, char *polish,
                      int *n) {
    if (root == NULL) {
        root = init(prior, c);
    } else {
        root             = push(root, c, prior);
        struct node *tmp = root;
        if (c != '(') {
            while ((tmp->next) && (tmp->next->data != '(')) {
                if (tmp->next->prior >= prior) {
                    polish[ (*n)++ ] = ' ';
                    polish[ (*n)++ ] = tmp->next->data;
                    tmp->next        = pop(tmp->next);
                } else {
                    tmp = tmp->next;
                }
            }
        }
    }
    return root;
}

void unar_nul(char *str, int n) {
    if (str[ 0 ] == '-') {
        for (int j = n; j > 0; j--) {
            str[ j ] = str[ j - 1 ];
        }
        n++;
        str[ 0 ] = '0';
        str[ n ] = '\0';
    }
    for (int i = 1; i < n; i++) {
        if (str[ i ] == '-' && str[ i - 1 ] == '(') {
            for (int j = n + 1; j > i; j--) str[ j ] = str[ j - 1 ];
            str[ i ] = '0';
            n++;
        }
    }
}

int first_last_sym(const char *str, int n) {
    int flag = 0;
    if (str[ 0 ] == '+' || str[ 0 ] == '/' || str[ 0 ] == '*'
        || str[ 0 ] == '.')
        flag = 1;
    if (str[ n - 1 ] == '+' || str[ n - 1 ] == '/' || str[ n - 1 ] == '*'
        || str[ n - 1 ] == '-')
        flag = 1;
    return flag;
}


int operator_check(char *str, int n, int flag_next) {
    int flag           = 1;
    char numbers[ 11 ] = "1234567890";
    if (str[ 0 ] == '+') flag = 0;
    for (int i = 0; i < n && flag; i++) {
        if (str[ i ] == 's' && (str + i == strstr(str + i, "sqrt("))) {
            i = i + 3;
        } else if (str[ i ] == 's' && (str + i == strstr(str + i, "sin("))) {
            i = i + 2;
        } else if (str[ i ] == 'c' && (str + i == strstr(str + i, "cos("))) {
            i = i + 2;
        } else if (str[ i ] == 'c' && (str + i == strstr(str + i, "ctg("))) {
            i = i + 2;
        } else if (str[ i ] == 't' && (str + i == strstr(str + i, "tan("))) {
            i = i + 2;
        } else if (str[ i ] == 'l' && (str + i == strstr(str + i, "ln("))) {
            i = i + 1;
        } else if ((strchr("+*/-", str[ i ]) != NULL && flag_next)
                   || (str[ i ] == '(')) {
            flag = operator_check(str + i + 1, 1, 0);
        } else if ((str[ i ] == ')' && flag_next)
                   || (strchr(numbers, str[ i ]) != NULL)
                   || (str[ i ] == '.'
                       && ((str[ i - 1 ] >= 48 && str[ i - 1 ] <= 57)
                           && (str[ i + 1 ] >= 48 && str[ i + 1 ] <= 57)))) {
        } else if (str[ i ] == 'x' && (i == 0 || i == n - 1)) {
        } else if (str[ i ] == 'x' && strchr(numbers, str[ i + 1 ]) == NULL
                   && strchr(numbers, str[ i - 1 ]) == NULL
                   && str[ i + 1 ] != '(' && str[ i - 1 ] != ')') {
        } else {
            flag = 0;
        }
    }
    return flag;
}
