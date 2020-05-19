
/* The program tests a strlen function. */

#include <stdio.h>

int strlen(char s[]);

int main(void) {
    printf("%d\n", strlen("12345678"));

    return 0;
}

/* strlen: return lenght of string */
int strlen(char s[]) {
    int i;

    i = 0;
    while (s[i] != '\0')
        ++i;

    return i;
}

