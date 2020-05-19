
/* Exercise 4.4
   The program is a primitive calculator that does +, *, -, / and
   % operations. It can works with negavite values and has
   new operations: upper() -> pirnt upper number, dublicate() ->
   dublicate upper number, and exchange() -> exchange two upper
   numbers. */

#include <stdio.h>
#include <stdlib.h>   /* for atof() function */
#include <ctype.h>
#include <math.h>     /* for fmod() function; compilation with
                                                  -lm key*/

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

/* new functions: */
void upper(void);     
void dublicate(void); 
void exchange(void);  

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
            case    '%':  /* take remainder of division */
                op2 = pop();
                if (op2 == 0.0)
                    printf("error: zero divisor\n");
                else               
                    push(fmod(pop(), op2));
                break;
            case    '$':  /* exchange two upper numbers */
                exchange(); 
                break;
            case    '#':  /* print upper number */
                upper();
                break;
            case    '@':  /* dublicate upper number */
                dublicate();
                break;
            case   '\n':
                printf("\t%.8f\n", pop());
                break;
            default    :
                printf("error: unknown commnad -> %s\n", s);
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

/* upper: print upper number */
void upper(void) {
    if (sp > 0)
        printf("## %f ##\n", sbuf[sp - 1]);
    else
        printf("stack empty\n");
}

/* dublicate: dublicate upper number */
void dublicate(void) {
    double new = pop();
    push(new);
    push(new);
}

/* exchange: exchange two upper numbers */
void exchange(void) {
    double first, second;
    
    first = pop();
    second = pop();
    push(first);
    push(second);
}

/* getop: write to s-string an operand; return type of s */
int getop(char s[]) {
    int i, c;
    
    i = 0;
    /* missing space characters */
    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';    
    if (!isdigit(c) && c != '.') /* if c != number */
        if (c == '-') {
            if (isdigit(c = getch()) || c == '.') /* if negavite number */
                s[i = 1] = c;
            else {    /* just '-' operation */
                ungetch(c);
                return s[0];  
            }
        } else
            return c;
    
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

