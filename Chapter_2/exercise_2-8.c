
/* Exercise 2.8
   The program uses rightrot(x, p) function that returns the value
   of the integer x rotated to the right by n bit positions. */

#include <stdio.h>

unsigned int rightrot(unsigned int x, int p);

int main(void) {
    printf("rightrot(0xF0U, 4) returns %X\n", rightrot(0xF0U, 4));

    return 0;
}

unsigned int rightrot(unsigned int x, int p) {
    int to_left;

    if (~0U << 16)   /* if == 0, int has 16 bits */
        to_left = 32;
    else
        to_left = 16;

    return ((x & (~(~0U << p)) << (to_left - p))  | x >> p);
}

