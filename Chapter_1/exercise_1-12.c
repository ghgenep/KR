
/* Exercise 1.12
   The program prints every word in new line. */

#include <stdio.h>

#define OUT 0       /* I'm out word */
#define IN  1       /* I'm in */

int main(void) {
    int state, c;
    
    state = OUT;
    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\t' || c == '\n') {
            if (state == IN) {  /* if not, skip every space char */
                putchar('\n');
                state = OUT;    /* and now I'm out a word */
            }
        } else {
            putchar(c);
            state = IN;     /* I'm in word */
        }
    }

    return 0;
}

