
/* Exercise 1.8
   The program counts the spaces, tabs and newlines. */

#include <stdio.h>

int main(void) {
    int c, space, tab, newline;
    
    space = tab = newline = 0;
    while ((c = getchar()) != EOF) {
        if (c == ' ')
            ++space;
        else if (c == '\t')
            ++tab;
        else if (c == '\n')
            ++newline;
    }

    printf("%d %d %d\n", space, tab, newline);

    return 0;
}

