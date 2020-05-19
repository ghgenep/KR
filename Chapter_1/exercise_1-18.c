
/* Exercise 1.18
   The program deletes tail tabs and spaces, deletes empty lines. */

#include <stdio.h>

#define MAX 1000

int main(void) {
    int i, c;
    char out[MAX + 1];  /* " + 1" for '\0' */
    
    for (i = 0; (c = getchar()) != EOF && i < MAX; ++i) {
        out[i] = c;
        if (c == '\n') {
            if (i == 0) {
                i--;
                continue;
            }
            if (out[i - 1] == '\n') /* if "\n\n" */
                i--;
            else {
                i--;
                for ( ; out[i] == ' ' || out[i] == '\t'; i--)
                    ;
                i++; /* because now we're on nonspase symbol */
                out[i] = '\n';
            }
        }
    }
    
    out[i] = '\0';
    printf("%s", out);

    return 0;
}

