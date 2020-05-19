
/* Exercise 5.1
   The program uses getint() function that takes string and translates it
   into a integer number. The function can treats '-' and '+' characters
   without digits after correctly. */

#include <stdio.h>
#include <ctype.h>

#define BUFSIZE 100

int buf[UFSIZE];   /* for getch() and ungetch() functions */
int buf_count;

/* getch: like getchar, but considers the buffer of an unwanted
   characters */
int getch(void) {
    return (buf_count == 0) ? getchar() :  buf[--buf_count];
}

/* ungetch: push an unwanted character to the buffer */
void ungetch(int c) {
    if (buf_count == BUFSIZE)   /* if overflow */
        printf("too many characters!\n");
    else
        buf[buf_count++] = c;
}

/* getint: get a string, translate it into a number, and write it to *p */
int getint(int *p) {
    int c, sign;

    while (isspace(c = getch()))
        ;
    if (c != '-' && c != '+' && !isdigit(c) && c != EOF) { 
        /* if unwanted character */
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

    for (*p = 0; isdigit(c); c = getch()) /* convert characters to numbers */
        *p = *p * 10 + (c - '0');
    *p = *p * sign;

    if (c != EOF)   /* now, c is EOF or unwanted character */
        ungetch(c);
    return c;
}

int main(void) {
    int i, c;
    
    while ((c = getint(&i)) != EOF && c != 0)             
        printf("i == %d\n", i);
        
    if (c == 0)
        printf("error: %c is occured, it's not a number!\n", c);

    return 0;
}

