
/* Exercise 4.11
   The program is a primitive calculator that does +, *, - and /
   operations. The program uses a static variable in getop() function.
   */

#include <stdio.h>
#include <stdlib.h>   /* for atof() function */
#include <ctype.h>

#define MAXOP 100     /* max size of operand or operation */
#define NUMBER '0'    /* means that a number is found */

#define NUMBER_OF_CELL 100

#define NUMBER_OF_CELL_IN_STACK 100

int sp = 0;  /* stack pointer - has address of next free cell */
double sbuf[NUMBER_OF_CELL_IN_STACK];  /* stack for pop() & push() functions*/

int getop(char s[]);  
void push(double f);  
double pop(void);     

int main(void) {
    int type;
    double op2;   /* second operand of calculator */
    char s[MAXOP];  /* array has an operand or operation, that is found */

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
    static int unwanted;
    
    unwanted = ' ';    /* static variables are initilized only once */
    /* missing space characters */
    s[0] = unwanted;
    while ((c = s[0]) == ' ' || c == '\t')
        s[0] = getchar();
    s[1] = '\0';    
    if (!isdigit(c) && c != '.') /* if c != number */
        return c;
    
    i = 0;
    if (isdigit(c))
        while (isdigit(s[++i] = c = getchar()))
            ;
    if (c == '.')
        while (isdigit(s[++i] = c = getchar()))
            ;
    s[i] = '\0';
    
    unwanted = c;   /* unwanted is not deleted; c is safe */
        
    return NUMBER;    
}

