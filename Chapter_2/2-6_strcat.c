
/* The program uses strcat(s, t) function, that concatenates
   s and t. */

#include <stdio.h>

void strcat(char s[], char t[]);

int main(void) {
    char s[10] = "123";
    char t[] = "321";

    printf("s == \"123\"\n"
           "t == \"321\"\n");
    strcat(s, t);
    printf("strcat(s, t)\n"
           "s == \"%s\"\n", s);

    return 0;
}

void strcat(char s[], char t[]) {
    int i, j;

    i = j = 0;
    while (s[i] != '\0')
        i++;
    while ((s[i++] = t[j++]) != '\0')
        ;
}

