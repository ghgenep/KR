
/* Exercise 5.2
   The program uses getfloat() function that takes string with
   numbers and translates it into a float number. */

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

/* getfloat: get a string, translate it into a number, and write it to *p */
int getfloat(float *p) {
    int c, sign, power;

    while (isspace(c = getch()))
        ;
    if (c != '-' && c != '+' && !isdigit(c) && c != EOF) {  
        /* if unnecessary character */
        ungetch(c);
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '-' || c == '+') {     
        if (!isdigit(c = getch())) {  /* is there digit after '-' or '+'? */
            ungetch(c);
            ungetch((sign == -1) ? '-' : '+');
            return 0;
        }
    }
    /* convert characters to numbers */
    for (*p = 0.0; isdigit(c); c = getch()) 
        *p = *p * 10 + (c - '0');
    if (c == '.')
        c = getch();
    /* power is the number of digits after the point */
    power = 1;
    while (isdigit(c = getch())) { 
        *p = *p * 10 + (c - '0');
        power = power * 10;
    }
    if (power != 0) 
        *p = *p / power; 
    *p = *p * sign;

    if (c != EOF)   /* now, c is EOF or unnecessary character */
        ungetch(c);
    return c;
}

int main(void) {
    float f;
    int c;
    
    while ((c = getfloat(&f)) != EOF && c != 0)             
        printf("f == %.7f\n", f);
        
    if (c == 0)
        printf("error: %c is occured, it's not a number!\n", c);

    return 0;
}

