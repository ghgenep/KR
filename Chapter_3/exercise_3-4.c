
/* Exercise 3.4
   The program uses itoa(n, s) function that translates number n 
   into number-string s. INT_MIN is treated correctly. */

#include <stdio.h>
#include <limits.h>

void itoa(int n, char s[]);

int main(void) {
    char s[30] = "";

    itoa(INT_MIN, s);   /* INT_MIN == INT_MAX + 1 */
    printf("%s\n", s);

    return 0;
}

/* itoa: translates number n into number-string s */
void itoa(int n, char s[]) {
    int i, low, temp;
    unsigned int new_n; /* if new_n is signed int and n is INT_MIN,
            the answer will be wrong:
            because we need to change sign; if we write "n = -n",
            here is what happens: 
                  1000'0000(8-bit)
                ^
                  1111'1111
                  ---------
                  0111'1111 + 1 == 1000'0000, that is what we 
            had in beggining(the two's complement of a number) */

    i = low = 0;
    if (n < 0) {
        s[i++] = '-';
        low = 1;
    }
    new_n = n; /* the value of bits don't change */
    do {
        s[i++] = new_n % 10 + '0';
    } while ((new_n /= 10) > 0);
    s[i] = '\0';

    for (i--; low < i; i--, low++) {
        temp = s[i];
        s[i] = s[low];
        s[low] = temp;
    }
}

