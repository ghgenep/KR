
/* Exercise 1.6
   Is (getchar != EOF) expression equal 1 or 0. */

#include <stdio.h>

int main(void) {
    if (getchar() != EOF)
        putchar('1');  /* if that's true, print 1 */
    else
        putchar('0');

    return 0;
}

