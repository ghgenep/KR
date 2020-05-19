
/* Exercise 4.1
   The program uses strindex(source, p) function that returns an index
   of the rightest p-string in source-string; otherwise, it 
   returns -1. */

#include <stdio.h>
#define MAXLINE 1000

int my_getline(char s[], int lim);
int strindex(char source[], char p[]);

char pattern[] = "ould";

int main(void) {
    char line[MAXLINE];
    int found = 0;   /* a count of lines that contane pattern */
    int i;

    while (my_getline(line, MAXLINE) > 0)  /* if there is line, ... */
        if ((i = strindex(line, pattern)) >= 0) {
            printf("%s", line + i);    /* print line, starting with
                                                   pattern */
            found++;
        }
    
    return found;
}

/* my_getline: return length of new line */
int my_getline(char s[], int lim) {
    int c, i;

    i = 0;
    /* --lim for '\0' in the end */    
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (lim == 0) {
        printf("### ERROR -> line is so much long! ###\n");
        return 0;
    } else if (c == '\n')
        s[i++] = c;
    s[i] = '\0';

    return i;
}

/* strindex: return an index of t in source; otherwise, return -1 */
int strindex(char source[], char p[]) {
    int i, j, k;
    int base = 0;   /* rightest index of pattern */
    int flag = 0;       /* if flag == 1, line contanes pattern */

    for (i = 0; source[i] != '\0'; i++) {
        for (j = 0, k = i; p[j] != '\0' && p[j] == source[k]; j++, k++)
            ;
        if (p[j] == '\0' && j > 0) { /* if j == 0, pattern have no
                                               characters */
            flag = 1;
            base = i;
            i = k - 1;   /* because of for(...; i++) */
        }
    }
    if (flag)
        return base;
    
    return -1;
}

