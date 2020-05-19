
/* Exercise 1.11
   The program counts a words. How I can test it? */

/* 
1. If there is no the new line character at the end of file, we will have 
   N - 1 lines number. 
2. Or input, for example, 70000 letters...(int type will overflow).
*/

#include <stdio.h>

#define IN  1
#define OUT 0

int main(void) {
    int c, nl, nw, nc, state;   /* 2 */

    state = OUT;
    nl = nw = nc = 0;
    while ((c = getchar()) != EOF) {
        ++nc;
        if (c == '\n')   /* 1 */
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

