
/* The program uses an argument of command line and performs the function of 
   the find program. */

#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

int my_getline(char *, int);

int main(int argc, char **argv) {
    int found = 0;
    char line[MAXLINE];
    
    if (argc != 2)
        printf("Usage: find pattern\n");
    else
        while (my_getline(line, MAXLINE) > 0)
            /* strstr() function returns pointer to first found substring;
               else - NULL */
            if (strstr(line, argv[1]) != NULL) {
                printf("%s", line);
                found++;
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
