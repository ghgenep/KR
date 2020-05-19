
/* The program copies the input stream into output stream. */

#include <stdio.h>

int main(void) {
    int c;
    
    c = getchar();          /* get a character from the keyboard */
    while (c != EOF) {      /* EOF is end-of-file */
        putchar(c);         /* put character into the screen */
        c = getchar();
    }

    return 0;
}

