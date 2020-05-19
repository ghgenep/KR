
/* The program copies the input stream into output stream. Part 2 */

#include <stdio.h>

int main(void) {
    int c;
    
    while ((c = getchar()) != EOF)
        /* operator '=' returns the value of the variable */
        putchar(c);

    return 0;
}

