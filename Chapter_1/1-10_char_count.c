
/* The program counts a characters from input stream. */

#include <stdio.h>

int main(void) {
    long nc;
    
    nc = 0;
    while (getchar() != EOF)    /* we don't need to save a
                                   values of characters */
        ++nc;                   /* increment */
    printf("%ld\n", nc);

    return 0;
}

