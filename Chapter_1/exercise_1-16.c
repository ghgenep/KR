
/* Exercise 1.16
   The program prints the longest line. */

#include <stdio.h>
#define MAXLINE 100

int get_line(char line[], int maxline);
void copy(char to[], char from[]);

int main(void) {
    int len;   /* lenght of current line */
    int max;   /* lenght of longest line */
    char line[MAXLINE];   /* current line */
    char longest[MAXLINE];   /* longest line */

    max = 0;
    while ((len = get_line(line, MAXLINE)) > 0)
        if (len > max) {
            max = len;
            copy(longest, line);
        }
    if (max > 0) {   /* max == 0 if there are no lines */
        printf("%s\n", longest);
        if (max >= len)
            printf("\nthe line is not full, because it has %d characters!", max);
    }
    else 
        printf("input is void!\n");

    return 0;
}

/* get_line: read a line and move it to s; return its lenght */
int get_line(char s[], int lim) {
    int c, i;

    for (i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (i == lim-1) {
        s[i] = '\0';   /* now i is number of characters */

        /* keep counting following letters */
        while ((c = getchar()) != '\n' && c != EOF) 
            i++;
        if (c == '\n')
            i++;

        return i;
    } else if (c == '\n') {
        s[i] = '\0';   /* '\0' because '\n' is printed in main function */
        i++;
    }
    s[i] = '\0';

    return i;
}

/* copy: copy from[] to to[] */
void copy(char to[], char from[]) {
    int i;

    i = 0;
    while ((to[i] = from[i]) != '\0')
        ++i;
}

