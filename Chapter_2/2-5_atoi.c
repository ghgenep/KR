
/* The program uses atoi() function that translates number-string
   to number-integer and returns it. */

#include <stdio.h>

/* atoi() function converts char to int */
int atoi(char s[]);

int main(void) {
    char s[] = "01984";
 
    printf("input is: \"01984\"");
    printf("\noutput is: %d\n", atoi(s));

    return 0;
}

/* atoi: translates number-string to number-integer and returns it */
int atoi(char s[]) {
    int i, n;

    n = 0;
    for (i = 0; s[i] >= '0' && s[i] <= '9'; i++)
        n = n * 10 + (s[i] - '0');

    return n;
}

