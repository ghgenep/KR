
/* Exercise 5.10
   The program is a primitive calculator that does +, *, - and /
   operations. Usage: ./a.out 2 3 + 5 - [...]. All operations must
   be written with name of program. */

#include <stdio.h>
#include <stdlib.h>   /* for atof() function */
#include <ctype.h>

#define MAXOP 1000     /* max size of operand or operation */
#define NUMBER '0'

#define NUMBER_OF_CELL_IN_STACK 100
int sp = 0;  /* stack pointer - has address of next free cell */

/* stack for pop() and push() functions*/
double sbuf[NUMBER_OF_CELL_IN_STACK];  
                         
void push(double f);  
double pop(void);     

int main(int argc, char **argv) {
    int temp, c, go_out;
    double op2;   /* second operand of calculator */
    char *start, *t;
    
    while (--argc > 0) {
        t = start = *++argv;
        go_out = 0;     /* == 1, if argument has been read */
        while (go_out == 0) {
            while (*t != '\0' && isdigit(*t))
                t++;
            /* if argument contains one argument only */
            if (*t == '\0') { 
                go_out = 1;
                c = NUMBER;
            } else {
                if (t != start) {
                    temp = *t;  /* save next operand of command */
                    *t = '\0';
                    c = NUMBER;
                } else {
                    if ((temp = *++t) == '\0')
                        /* if this is last operand of command
                           in a current argument */
                        go_out = 1;
                    *t = '\0';
                    c = *start;
                }
            }
        
            switch (c) {
                case NUMBER:
                    push(atof(start));
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
                    printf("error: unknown commnad -> %s\n", start);
                    break;
            }
            /* if argument has been read, go out */
            if (go_out == 1)
                break;
            start = t;    /* beginning of next operand in argument */
            *t = temp;    /* restore beginning of operand */
        }
    }
    printf("\t%.8f\n", pop());
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
