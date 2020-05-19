
/* Exercise 4.6
   The program is a primitive calculator that does +, *, -, /, 
   %, > (sin), < (cos), and ^ (power) operations. It has specific
   operations: upper() -> pirnt upper number, dublicate() ->
   dublicate upper number, and exchange() -> exchange two upper
   numbers. Also, it can works on negavite values and variables:
   [some operations] = [name of variable](End of line)
   name of variable can be any tolower(letter): a, b, c, ... z.
   like "1 2 + 3 * 4 / = t".
   You can use variable wherever, where number can be used.
   like "t t * 2 /"                                          
   There is '_' variable, that keep last printed number.   */

#include <stdio.h>
#include <stdlib.h>   /* for atof() function */
#include <ctype.h>
#include <errno.h>    /* for using EDOM and ERANGE macros */
#include <math.h>     /* for fmod() and pow() functions;
                          compilation with -lm key*/

#define MAXOP 100     /* max size of operand or operation */
#define LETTER 'a'    /* means that variable is or will be used */
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
void upper(void);     
void dublicate(void); 
void exchange(void);  

int main(void) {
    int type;
    double f;
    double last;   /* last printed number */
    char var_f[26] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                      0, 0, 0, 0, 0, 0}; /* if var_f[N] == 0, variable 
                                                            is not used */
    double var[26] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                      0, 0, 0, 0, 0, 0}; /* var[N] is value of variable */
    double op2;   /* second operand of calculator */
    char s[MAXOP];  /* array has an operand or operation, that is
                                                         found */
    printf("Use \"<\"(cos) and \">\"(sin) in radian.\n");
    while ((type = getop(s)) != EOF) {
        if ('a' <= type && type <= 'z') /* if type is variable */
            type = LETTER;
            
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
            case    '^':   /* to power */
                op2 = pop();
                f = pow(pop(), op2);
                if (errno == EDOM) {
                    printf("IN ^ FUNCTION -> error of function" 
                           "definition area!\n");
                    break;
                }
                if (errno == ERANGE) {
                    printf("IN ^ FUNCTION -> error: out of range!\n");
                    break;
                }
                push(f);
                break;
            case    '<':   /* cos in radian */
                push(cos(pop()));
                break;
            case    '>':   /* sin in radian */
                push(sin(pop()));
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
/**** new operations: ****/
            case    '_':  /* last printed character */
                push(last);
                break;
            case    '=':
                if ((type = getop(s)) >= 'a' && type <= 'z') {
                    f = var[type - 'a'] = pop();
                    var_f[type - 'a'] = 1;  /* var_f[N] is flag of variable */
                    push(f);
                }
                else
                    printf("error: incorrent name of variable \'%c\'\n", type);
                break; 
            case LETTER:
                if (var_f[s[0] - 'a'] == 1)  /* if var_f[N] is used */
                    push(var[s[0] - 'a']);
                else
                    printf("error: variable is not used\n");
                break;  
/*************************/
            case   '\n':
                last = pop();
                printf("\t%.8f\n", last);
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
            if (isdigit(c = getch()) || c == '.') /* if negavite
                                                    number */
                s[i = 1] = c;
            else {    /* just '-' operation */
                ungetch(c);
                return s[0];  
            }
        }
        else
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

