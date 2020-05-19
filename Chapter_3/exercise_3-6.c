
/* Exercise 3.6
   The program uses itoa(n, s, p) function that has 3 agruments.
   The third argument is a minimum field width. */

#include <stdio.h>

void itoa(int n, char s[], int p);

int main(void) {
    char s1[30] = "";
    char s2[30] = "";
    char s3[30] = "";
    
    printf("s1, s2, s3 == \"\"\n");
    printf("itoa(0, s1, 0)\n"
           "itoa(1342, s2, 8)\n"
           "itoa(1342, s3, 4)\n");
    itoa(1342, s1, 3);
    itoa(1342, s2, 8);
    itoa(1342, s3, 4);
    printf("s1 = \"%s\"\n"
           "s2 = \"%s\"\n"
           "s3 = \"%s\"\n", s1, s2, s3);

    return 0;
}

void itoa(int n, char s[], int p) {
    int i, low, diff, last, temp;

    i = low = diff = 0;
    if (n < 0) {
        s[i++] = '-';
        n = -n;
        low = 1;  /* s[low] is first number */
    }
    do {
        s[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);
    s[i] = '\0';
    last = i;
    /* this block reverses the order of symbols */
    for (i--; low < i; i--, low++) {
        temp = s[i];
        s[i] = s[low];
        s[low] = temp;
    }
    i = last;
    /* this block advances numbers to right if p > len of string */
    if ((diff = p - i) > 0) {
        s[i + diff] = '\0';
        for (i--; i >= 0; i--)
            s[i + diff] = s[i];
        while (--diff >= 0)
            s[diff] = ' ';
    }
}

