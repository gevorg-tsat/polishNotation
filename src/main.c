#include "parsing.h"
#include <stdio.h>

int main() {
    char *str = "cos(3*5+5)\0";
    str = str_to_polish(str);
    printf("%s", str);
}