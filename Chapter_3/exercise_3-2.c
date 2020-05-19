
/* Exercise 3.2
   The program uses escape_1() and escape_2() functions; 
   escape_1(): translates "\n" and "\t" into '\n' and '\t';
   escape_2(): translates '\n' and '\t' into "\n" and "\t". */

#include <stdio.h>
#define N 20

void escape_1(char to[], char from[]);
void escape_2(char to[], char from[]);

int main(void) {
    char s1[N] = "";
    char s2[] = "1\t2\n3\t";
    char s3[N] = "";
    int i;

    printf("now s2 = \"%s\"\n", s2);
    printf("then: escape_2(s1, s2)\n");
    escape_2(s1, s2);
    printf("now s1 = \"%s\"\n", s1);
    printf("now s3 = \"%s\"\n", s3);
    printf("then: escape_1(s3, s1)\n");
    escape_1(s3, s1);
    printf("now s3 = \"%s\"\n", s3);

    return 0;
}

/* escape_1: translates "\n" and "\t" into '\n' and '\t' */
void escape_1(char to[], char from[]) {
    int i, j, c;

    i = j = 0;
    while ((c = from[i]) != '\0')
        if (c == '\\') {   /* miss first '\\' symbol */
            while ((c = from[++i]) == '\\')
                to[j++] = '\\';
            switch (c) {
                case  'n': to[j] = '\n'; break;
                case  't': to[j] = '\t'; break;
                 /* recollect '\\' symbol */
                case '\0': to[j] = '\\'; break; 
                default  : to[j++] = '\\'; to[j] = c; break;
            }
            j++;
            i++;
        }
        else
            to[j++] = from[i++];

    to[j] = '\0';
}

/* escape_2: translates '\n' and '\t' into "\n" and "\t" */
void escape_2(char to[], char from[]) {
    int i, j, c;

    i = j = 0;
    while ((c = from[i]) != '\0') {
        switch (c) {
            case '\n': to[j++] = '\\'; to[j++] = 'n'; break;
            case '\t': to[j++] = '\\'; to[j++] = 't'; break;
            default  : to[j++] = c; break;
        }
        i++;
    }
    to[j] = '\0';
}

