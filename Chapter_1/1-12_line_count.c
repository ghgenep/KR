
/* The program counts the lines of the input stream. */

#include <stdio.h>

int main(void) {
    int c, nl;
    nl = 0;
    
    while ((c = getchar()) != EOF) {
        if (c == '\n')  /* every line has \n char in the end */
            ++nl;       /* count a lines */
    }
    printf("%d\n", nl);

    return 0;
}

