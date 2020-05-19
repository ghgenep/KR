
/* The program uses itoa() function that translates number n 
   into number-string s. */

#include <stdio.h>
#include <string.h>

void itoa(int n, char s[]);

int main(void) {
    char s[10];

    itoa(1342, s);
    printf("itoa(1342, s) returns \"%s\"\n", s);

    return 0;
}

/* itoa: translates number n into number-string s */
void itoa(int n, char s[]) {
    int i, j, sign, temp;

    if ((sign = n) < 0)   /* safe sign */
        n = -n;
    i = 0;
    do {   /* generating numbers */
        s[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';

    /* reversing of string */
    for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        temp = s[i];
        s[i] = s[j];
        s[j] = temp;
    }
}

