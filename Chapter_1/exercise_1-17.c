
/* Exercise 1.17
   The program outputs the lines that have over 80 characters. */

#include <stdio.h>

#define MAX 1000

int main(void) {
    int i, c;
    char out[MAX + 1];
    
    for (i = 0; (c = getchar()) != EOF && i < MAX; ++i) {
        out[i] = c;
        if (c == '\n') {
            out[i] = '\0';
            if (i > 10)
                printf("%s\n", out);
            i = -1;
        }
    }
    if (i > 10)
        printf("%s\n", out);

    return 0;
}
