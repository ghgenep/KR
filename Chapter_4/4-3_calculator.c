
/* The program is a primitive calculator that does +, *, - and /
   operations. */

#include <stdio.h>
#include <stdlib.h>   /* for atof() function */
#include <ctype.h>

#define MAXOP 100     /* max size of operand or operation */
#define NUMBER '0'    /* means that a number is found */

#define NUMBER_OF_CELL 100

int bp = 0;     /* buffer pointer */
char buf[NUMBER_OF_CELL];  /* buffer
                    for getch() and ungetch() functions */

#define NUMBER_OF_CELL_IN_STACK 100

int sp = 0;  /* stack pointer - has address of next free cell */
double sbuf[NUMBER_OF_CELL_IN_STACK];  /* stack 
                    for pop() and push() functions*/

void ungetch(int c);  
int getch(void);      
int getop(char s[]);  
void push(double f);  
double pop(void);     

int main(void) {
    int type;
    double op2;   /* second operand of calculator */
    char s[MAXOP];  /* array has an operand or operation, that is
                                                         found */

    while ((type = getop(s)) != EOF) {
        switch (type) {
            case NUMBER:
                push(atof(s));
                break;
            case    '+':
                push(pop() + pop());
                break;
            case    '*':
                push(pop() * pop());
                break;
            case    '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case    '/':
                op2 = pop();
                if (op2 == 0.0)
                    printf("error: zero divisor\n");
                else
                    push(pop() / op2);
                break;
            default    :
                printf("error: unknown commnad -> %s\n", s);
                break;
            case   '\n':
                printf("\t%.8f\n", pop());
                break;

        }
    }
    
    return 0;
}

/* push: push double-number to stack */
void push(double f) {
    if (sp < NUMBER_OF_CELL_IN_STACK)
        sbuf[sp++] = f;
    else
        printf("error: buffer full, can't push %f\n", f);
}

/* pop: pop double-number from stack */
double pop(void) {
    if (sp > 0)
        return sbuf[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

/* getop: write to s-string an operand; return type of s */
int getop(char s[]) {
    int i, c;
    /* missing space characters */
    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';    
    if (!isdigit(c) && c != '.') /* if c != number */
        return c;
    
    i = 0;
    if (isdigit(c))
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.')
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';
    
    if (c != EOF)
        ungetch(c);
        
    return NUMBER;    
}

/* getch: like getchar() but it can take characters returned 
                              in input stream with ungetch() */
int getch(void) {
    return (bp > 0) ? buf[--bp] : getchar();
}

/* ungetch: return unwanted characters in input stream */
void ungetch(int c) {
    if (bp < NUMBER_OF_CELL)
        buf[bp++] = c;
    else
        printf("error: ungetch() buffer full\n");
}

