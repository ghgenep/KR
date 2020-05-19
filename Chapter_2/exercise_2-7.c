
/* Exercise 2.7
   The program uses the invert(x, p, n) function that returns x 
   with the n bits that begin at position p inverted. */

#include <stdio.h>

unsigned int invert(unsigned int x, int p, int n);

int main(void) {
    printf("invert(0xADU, 3, 1) == %X\n", invert(0xADU, 3, 1));

    return 0;

}

unsigned int invert(unsigned int x, int p, int n) {
    return (x ^ (~(~0U << p) << n));
}

