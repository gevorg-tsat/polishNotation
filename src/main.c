#include "parsing.h"
#include <stdio.h>

int main() {
    char *str = str_to_polish("cos(2*x)*(9+cos(x))*sin(9*cos(ln(x)))+1-9\0");
    printf("%s", str);
}