
/* Exercise 1.9
   The program translates the input into output, replacing string of only
   space sequence to one space character. */
   
#include <stdio.h>

int main(void) {
    int i, c;   /* i == count of spaces */

    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            /* search for EOR or unspace symbol */
            for (i = 0; (c = getchar()) != EOF && c == ' '; i++)
                ;
            if (c == '\n')
                if (i == 0)     /* if "\n\n" */
                    putchar('\n');
                else
                    printf(" \n");
            else if (c == EOF) {
                putchar('\n');
            } else {  /* if unspase symbol, print spaces */
                while (i--)
                    putchar(' ');
                putchar(c);
            }
        }                
    }

    return 0;
}

