
/* The getint function. Version 1. */

#include <stdio.h>
#include <ctype.h>
#define BUFSIZE 100

int buf[BUFSIZE];   /* for getch and ungetch functions */
int buf_count;

/* getch: like getchar, but considers the buffer */
int getch(void) {
    return (buf_count == 0) ? getchar() :  buf[--buf_count];
}

/* ungetch: push an unnecessary character to the buffer */
void ungetch(int c) {
    if (buf_count == BUFSIZE)   /* if overflow */
        printf("too many characters!\n");
    else
        buf[buf_count++] = c;
}

/* getint: get a string, find number, convert it to integer number
   and return it */
int getint(int *p) {
    int c, sign;

    while (isspace(c = getch()))
        ;
    if (c != '-' && c != '+' && !isdigit(c) && c != EOF) {  /* if unnecessary
                                                       character */
        ungetch(c);
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '-' || c == '+') {
        c = getch();
    
    for (*p = 0; isdigit(c); c = getch())   /* convert characters to numbers */
        *p = *p * 10 + (c - '0');
    *p = *p * sign;

    if (c != EOF)   /* now, c is EOF or unnecessary character */
        ungetch(c);
    return c;
}

int main(void) {
    int i;

    printf("%d\n", getint(&i));     /* input:  '         1234rifu'
                                       output: '1234' */
    printf("%d\n", getint(&i));     /* input:  '         -321rifu'
                                       output: '-321' */
    printf("%d\n", getint(&i));     /* input:  '  ar1234rifu'
                                       output: '0' */
    printf("%d\n", getint(&i));     /* input:  '   -'
                                       output: '0' */
    return 0;
}

