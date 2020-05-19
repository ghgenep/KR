
/* Exercise 4.7
   The program uses ungets(s) function, that returns s-string to input
   stream. The program tests it. */

#include <stdio.h>
#include <string.h>

#define SIZE_OF_STACK 10

int sp = 0;     /* stack pointer */
int sbuf[SIZE_OF_STACK];    /* stack */

int getch(void);  
void ungets(char s[]);  

int main(void) {
    int c;
    int i = 0;
    char out[SIZE_OF_STACK * 10];
    
    printf("size of stack == %d\n", SIZE_OF_STACK);
    /* take characters and return them to input stream(sbuf) */
    while ((c = getch()) != EOF && c != '\n')
        out[i++] = c;
    out[i] = '\0';
    ungets(out);
    /* if out[0] == '\0', ungets() function has worked */
    if (out[0] == '\0') {
        i = 0;
        while ((c = getch()) != EOF)
            out[i++] = c;
        printf("%s", out);
    }
    
    return 0;
}

/* ungets: return s-strign to input stream; if ok, string is deleted */
void ungets(char s[]) {
    int i;
    
    if (sp + (i = strlen(s)) <= SIZE_OF_STACK) {  /*  " <= ",  because 
            if sp points to SIZE_OF_STACK-cell, it's ok(stack is full) */
        while (--i >= 0)
            sbuf[sp++] = s[i];
        s[0] = '\0';   /* delete string */
    }
    else
        printf("error: string \"%s\" is too long!\n", s);   
}

/* getch: like getchar() but can check stack for returned characters */
int getch(void) {
    return (sp > 0) ? sbuf[--sp] : getchar();
}

