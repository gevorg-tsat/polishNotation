#include "calc.h"
#include <stdio.h>

int main() {
    char *str = "15.5hello my friend";
    float x;
    // int i = sscanf(str, "%f", &x);
    if (is_number(str)) {
        sscanf(str, "%f", &x);
        printf("%f", x);
    }
    return 0;
}
