#include "parsing.h"
#include <stdio.h>

int main() {
    char *str = "3*3*3+5\0";
    str = str_to_polish(str);
    printf("%s", str);
}