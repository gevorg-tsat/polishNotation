#include "parsing.h"
#include <stdio.h>

int main() {
    char str_temp[25] = "sin(cos((x+2)*3) )";
    spaces_fix(str_temp);
    char *str = str_temp;
    str = str_to_polish(str);
    printf("%s", str);
    return 0;
}