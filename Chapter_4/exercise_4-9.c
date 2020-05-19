
/* Exercise 4.9
   The program uses getch() and ungetch() functions that work on EOF
   correctly. */

#include <stdio.h>

void ungetch(int c);  
int getch(void);      

#define NUMBER_OF_CELL 100

int bp = 0;     /* buffer pointer */
char buf[NUMBER_OF_CELL];  /* buffer 
                    for getch() and ungetch() functions */

int main(void) {
    int c;
    ungetch('!');  /* ['!', ]  <-- stack */
    ungetch('i');  /* ['!', 'i', ] */
    ungetch('H');  /* ['!', 'i', 'H', ] */
    ungetch(EOF);  /* ['!', 'i', 'H', } */
    while ((c = getch()) != EOF)  /* if ungetch() don't work on 
                    EOF, it will out. */
        printf("%c", c);
        
    return 0;
}

/* getch: like getchar() but can take characters returned in 
   input stream */        
int getch(void) {
    return (bp > 0) ? buf[--bp] : getchar();
}

/* ungetch: return unwanted characters in input stream */
void ungetch(int c) {
    if (bp < NUMBER_OF_CELL) {
        if (c != EOF)
            buf[bp++] = c;
    }
    else
        printf("error: ungetch() buffer full\n");
}

