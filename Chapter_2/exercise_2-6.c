
/* Exercise 2.6
   The program uses setbits(x,p,n,y) function that returns x with n
   bits that begin at position p set to the rightmost n bits of y,
   leaving the other bits unchanged. */

#include <stdio.h>

unsigned int setbits(unsigned int x, int p, int n, unsigned int y);

int main(void) {
    printf("setbits(0x34U, 1, 3, 0x21U) returns %xu",
           setbits(0x34U, 1, 3, 0x21U));

    return 0;
}

unsigned int setbits(unsigned int x, int p, int n, unsigned int y) {
    unsigned int k = ((~0 << n) << p) | (~(~0 << p));
    /* k frees space */
    return ((x & k) | ((~(~0 << n) & y) << p));
}

