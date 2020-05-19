
/* Exercise 5.13
   The program reads last N lines from the input stream and prints 
   them(like tail program) */

#include <stdio.h>
#include <string.h>  /* for strcpy() function */
#include <stdlib.h>  /* for atoi() function */
#include <errno.h>   /* for using of errno variable */

#define MAXPTR 1000     /* maximum count of input line */
#define MAXLINE 1000    /* maximum length of input line */

int readlines(char **, int);
void writelines(char **, int);

int main(int argc, char **argv) {
    int c, nlines, i;
    char *lines[MAXPTR];  /* an array of pointers to string */
    int n;  /* n is count of tail lines, that must be printed */
    
    /* check correctness of arguments */
    if (argc > 2) {
        printf("Usage: tail -n\n");
        return 0;
    }
    else if (argc == 2) {
        n = atoi(*++argv);
        /* if errno == ERANGE, atoi() function didn't work correctly;
           if n >= 0, an argument has not '-' character */
        if (errno == ERANGE || n >= 0) {
            printf("how I must understand %s argument?\n", *argv);
            printf("Usage: tail -n\n");
            return 0;
        } else
            n = -n;
    }
    else  /* default: */
        n = 10;
    
    if (n > 0) {
        /* nlines = count of lines read */
        if ((nlines = readlines(lines, MAXPTR)) > 0) {
            if (nlines < n)
                n = nlines;
            printf("\n");
            writelines(lines + nlines - n, n);
        }
        else if (nlines == 0)
            printf("error: no lines\n");
        else
            printf("error: in readlines function!\n");
    } else {
        /* if n == 0, do nothing */    
    }
    return 0;
}

/* readlines: write input lines to line[] - array of pointers
   to string; return count of written lines, or -1 */
int readlines(char **lines, int maxptr) {
    int my_getline(char *, int);
    char *alloc(int);    
    int len, written = 0;
    char *p, line[MAXLINE];

    while ((len = my_getline(line, MAXLINE)) > 0)
        if ((p = alloc(len)) != NULL) {
            line[len - 1] = '\0';  /* delete newline character */
            strcpy(p, line);
            *lines++ = p;
            written++;  /* count of lines written to lines[] array */
        } else {
            printf("error: no free space!\n");
            return -1;
        }
    return written;
}

/* writelines: print strings from line[] */
void writelines(char **lines, int nlines) {
    while (nlines-- > 0)
        printf("%s\n", *lines++);
}

/* my_getline: get line and write it to s-string */
int my_getline(char *s, int maxline) {
    int c;
    char *p = s;
    
    while (--maxline > 0 && (c = getchar()) != EOF && c != '\n')
        *s++ = c;
    if (c == '\n')
        *s++ = '\n';
    *s = '\0';
    return s - p;
}

#define BUFSIZE (MAXPTR * MAXLINE)
char buf[BUFSIZE];  /* free space for alloc() function */
char *bufp = buf;

/* alloc: return pointer to free N bites, or NULL; N is len */
char *alloc(int len) {
    if (BUFSIZE - (bufp - buf) >= len) {
        bufp += len;
        return (bufp - len);
    }
    return NULL;
}
