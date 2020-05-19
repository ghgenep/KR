
/* Exercise 7.5
   The program is a primitive calculator that do +, -, / and *
   operations. The sscanf() function is used. To quit the 
   program, type letter 'q' in new line. */

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define MAXLINE 1000
char line[MAXLINE];  /* an array where my_getline() function
                        writes new string */
int p = 0;           /* point to next operand in line[]-string */

int get_line(char *, int);
void push(double);
double pop(void);

int main(void) {
    float f, op2;
    int c;
    
    /* get and treat every line */
    while (get_line(line, MAXLINE) != 0) {
        p = 0;
        while ((c = line[p]) != '\0') {
            while (isspace(c))
                c = line[++p];
            if (c == '\0')
                break;

            if (isdigit(c) || c == '-' || c == '+' || c == '.') {
                if (sscanf(line + p, "%f", &f) != 1) {  /* if it's not number */
                    if (c == '-') {
                        op2 = pop();
                        push(pop() - op2); 
                    } else if (c == '+')
                        push(pop() + pop()); 
                    else {   /* if dot - '.' */
                        printf("error: dot '.' is not operator, not number\n");
                        /* skip dot */
                    }
                    p++;
                } else {  /* if it's number */
                    push(f);
                    /* skip number in line string */
                    if (c == '.')
                        while (isdigit(line[++p]))
                            ;
                    else {
                        while (isdigit(c = line[++p]))
                            ;
                        if (c == '.')
                            while (isdigit(c = line[++p]))
                                ;
                    }
                }
            } else {  /* if it's not number */
                if (c == '/') {
                    op2 = pop();
                    if (op2 == 0.0)
                        printf("error: zero divisor\n");
                    else
                        push(pop() / op2);
                } else if (c == '*') 
                    push(pop() * pop());
                else if (c == 'q') {
                    printf("\n--- bye-bye ---\n");
                    exit(0);
                } else
                    printf("error: unknown operation\n");
                p++;
            }
        }  /* (c = line[p]) == '\0' */
        printf("\t%f\n", pop());  /* print result of calculating in line */
    }
}

/* my_getline: get line and write it into s-string */
int get_line(char s[], int lim) {
        int i, c;

        i = 0;
        --lim;  /* for '\0' in the end */
        while (i <= lim && (c = getchar()) != EOF && c != '\n')
            s[i++] = c;   
        if (i == lim + 1) {
            printf("error: too long string! must be %d characters\n",  lim);
            i--;
        } else if (c == '\n')
            s[i++] = c;
        s[i] = '\0';
        return i;
}

#define NUMBER_OF_CELL_IN_STACK 100
int sp = 0;  /* stack pointer - has address of next free cell */
double sbuf[NUMBER_OF_CELL_IN_STACK]; /* stack for pop() and push() */

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

