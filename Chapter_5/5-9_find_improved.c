
/* The program uses an argument of command line and performs the function
   of the find program. This parogram can have -x(except) and -n(number) 
   arguments. */

#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

int my_getline(char *, int);

int main(int argc, char **argv) {
    int found = 0, except = 0, number = 0, c;
    char line[MAXLINE], *p;
    long int linenum = 0;
    
    /* **++argv is first character of next argument */
    while(--argc > 0 && **++argv == '-')
        /* *++(*argv) is next character of an argument */
        while (c = *++(*argv))
            switch (c) {
                case 'x':
                    except = 1;
                    break;
                case 'n':
                    number = 1;
                    break;
                default :
                    printf("find: illegal option %c\n", c);
                    argc = 0;
                    found = -1;
                    break;
            }
    if (argc != 1)
        printf("Usage: find -x -n pattern\n");
    else
        while (my_getline(line, MAXLINE) > 0) {
            linenum++;
            /* strstr() function returns pointer to first found substring;
               else - NULL */
            p = strstr(line, *argv);
            if ((except && p == NULL) || (!except && p != NULL)) {
                    if (number) 
                        printf("%ld: ", linenum);
                    printf("%s", line);
                    found++;
            } 
        }
    return found;
}

/* my_getline: get string and write it to s string; return length of string */
int my_getline(char *s, int maxline) {
    int c;
    char *t = s;
    
    while (--maxline > 0 && (c = getchar()) != EOF && c != '\n')
        *s++ = c;
    if (c == '\n')
        *s++ = '\n';
    *s = '\0';
    
    return s - t;
}
