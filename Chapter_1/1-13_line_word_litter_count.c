
/* The program counts a lines, words and litters. */

#include <stdio.h>

#define OUT 0       /* I'm not in word */
#define IN  1       /* I'm not in word */

int main(void) {
    int c, nl, nw, nc, state;
    
    nl = nw = nc = 0;
    state = OUT;
    while ((c = getchar()) != EOF) {
        ++nc;
        if (c == '\n')
            ++nl;
        if (c == ' ' || c == '\n' || c == '\t')
            state = OUT;
        else if (state == OUT) {
            state = IN;
            ++nw;
        }
    }
    printf("%d %d %d\n", nl, nw, nc);

    return 0;
}

