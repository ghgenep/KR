
/* The program uses union(like structure). */

#include <stdio.h>

union Data {
    int i;
    float f;
    char *s;
};

int main(void) {
    union Data data;
    printf("%f\n", data.f = 4.5);
    printf("%d\n", data.i = 3);
    printf("%s\n", data.s = "help");
    return 0;
}

