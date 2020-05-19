
/* Exercise 1.10
   The program transtlates '\t', '\b' and '\\' characters into  '\\t', '\\b'
   and '\\\\' in order to seeing them. */
   
#include <stdio.h>

int main(void) {
    int c;
    
    while ((c = getchar()) != EOF) {
        if (c == '\t')
            printf("\\t");
        else if (c == '\b')     /* don't work in ubuntu terminal */
            printf("\\b");
        else if (c == '\\')
            printf("\\\\");
        else putchar(c);
    }

    return 0;
}   /* C is a very cool programming language */

