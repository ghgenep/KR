
/* The program uses (expression_1)?(expression_2):(expression_3)
   expression. */

#include <stdio.h>

int main(void) {
    int n;

    n = 4;
    printf("You have %d item%s.\n", n, (n == 1) ? "" : "s");
        /* OMG, this is genius!!! */
    n = 1;
    printf("Now you have %d item%s.\n", n, (n == 1) ? "" : "s");

    return 0;
}

