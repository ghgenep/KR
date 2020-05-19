
/* Exercise 4.8
   The program uses getch() and ungetch() function. It's impossible to 
   return to input stream more than 1 character. */

#include <stdio.h>

#define SOME '3'

int var = 0;        /* temporary variable */
int var_f = 0;      /* flag of variable var */

int getch(void);  
void ungetch(int c);  

int main(void) {
    int c;
    
    printf("Program echoes, untill \'%c\' is occured\n", SOME);
    while ((c = getch()) != EOF) {
        if (c != SOME)
            printf("%c", c);
        else {
            printf("_<--\n!!! \'%c\' is occured !!!\n", SOME);
            break;
        }
    }
    
    return 0;
}

/* getch: like getchar() but can check temp variable for returned characters */
int getch(void) {
    if (var_f)      /* is var is used */
        var_f = 0;
    else
        var = getchar();
        
    return var;
}

/* ungetch: return to input stream only 1 character */
void ungetch(int c) {
    if (var_f == 0) {
        var = c;
        var_f = 1;   /* point that var is used */
    } else
        printf("error: no free space for \'%c\'\n", c);
}

