
/* Exercise 4.10
   The program is a primitive calculator that does +, *, - and /
   operations. The program uses my_getline(s, lim) function that
   gets new string and writes it into s-string. */

#include <stdio.h>
#include <stdlib.h>   /* for atof() function */
#include <ctype.h>

#define MAXOP 100     /* max size of operand or operation */
#define NUMBER '0'    /* means that a number is found */
#define MAXLINE 100

int getop(char s[]);  
void push(double f);  
double pop(void); 
int my_getline(char s[], int lim);

char line[MAXLINE];  /* an array where my_getline() function 
            writes new string */
int p = 0;           /* point to next operand in line[]-string */

#define NUMBER_OF_CELL_IN_STACK 100

int sp = 0;  /* stack pointer - has address of next free cell */
double sbuf[NUMBER_OF_CELL_IN_STACK];  /* stack 
                    for pop() and push() functions*/
                    
int main(void) {
    int type = 0;

    double op2;     /* second operand of calculator */
    char s[MAXOP];  /* array has an operand or operation, that is
                                                         found */
    if (my_getline(line, MAXLINE) == 0) {
        printf("Nothing is written.\n");
        return 0;
    }
    while ((type = getop(s)) != '\0') {  /* if type == '\0',
                            we have EOF */
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
                if (my_getline(line, MAXLINE) == 0) {
                    printf("\nGoodbye!\n");
                    return 0;
                }
                p = 0;  /* point to first element of new string */
                break;
        }
    }
    
    return 0;
}

/* getop: write in s an operand; return type of s */
int getop(char s[]) {
    int i, c;
    
    i = 0;
    /* missing space characters */
    while ((s[i] = c = line[p]) == ' ' || c == '\t')
        p++; 
    if (!isdigit(c) && c != '.') /* if c != number */
        if (c == '-') {
            if (isdigit(c = line[++p]) || c == '.') { /* if negavite
                                                    number */
                s[i = 1] = c;
                p++;
                c = line[p];
            }
            else {    /* pust '-' operation */
                return s[0]; 
            }
        }
        else {
            p++;
            return c;
        }
    
    if (isdigit(c))
        while (isdigit(s[++i] = c = line[++p]))
            ;
    if (c == '.')
        while (isdigit(s[++i] = c = line[++p]))
            ;
            
    s[i] = '\0';
    /* p variable points to next operand in line string */
    return NUMBER;    
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
/* my_getline: get line and write it into s-string */
int my_getline(char s[], int lim) {
    int i, c;

    i = 0;
    --lim;  /* for '\0' in the end */
    while (i <= lim && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;   
    if (i == lim + 1)
        printf("error: too long string! must be %d characters\n",  lim);
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    
    return i;
}

