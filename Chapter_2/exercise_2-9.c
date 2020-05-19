
/* Exercise 2.9
   The program uses a more faster bitcount() function, that counts
   1-bits.
   The expression "x &= (x-1)" deletes the rightest 1-bit: in a new
   number (x-1) all the rightest zeros and one 1-bit are converted.
   In old and new numbers this digits are different so & operation
   deletes them. */

#include <stdio.h>

int bitcount(unsigned int x);

int main(void) {
    printf("0xAA has %d 1-bits\n", bitcount(0xAA));

    return 0;
}

int bitcount(unsigned int x) {
    int i;

    if (x == 0)
        return 0;
    for (i = 0; x &= (x - 1); i++)
        ;

    return i + 1;  /* + 1, because when x == 0, the lasted 1-bit
                      is not counted */
}

