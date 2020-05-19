
/* Exercise 3.5
   The program uses itob(n, s, b) function that converts 
   the integer n into a base b character representation 
   in the string s. */

#include <stdio.h>

void itob(int n, char s[], int b);

int main(void) {
    char s1[30] = "";
    char s2[30] = "";
    char s3[30] = "";
    
    printf("s1, s2, s3 == \"\"\n");
    printf("itob(1342, s1, 8)\n"
           "itob(1342, s2, 16)\n"
           "itob(1342, s3, 14)\n");
    itob(1342, s1, 8);
    itob(1342, s2, 16);
    itob(1342, s3, 14);
    printf("s1 = \"%s\"\n"
           "s2 = \"%s\"\n"
           "s3 = \"%s\"\n", s1, s2, s3);

    return 0;
}

/* itob: converts the integer n into a base b character representation 
   in the string s */
void itob(int n, char s[], int b) {
    int c, i, low, temp;

    i = low = 0;
    if (n < 0) {
        s[i++] = '-';
        n = -n;
        low = 1;  /* s[low] is first number */
    }
    do {
        c = n % b;
        if (c >= 0x0A && c < b)
            s[i++] = c - 0x0A + 'A';
        else
            s[i++] = c + '0';
    } while ((n /= b) > 0);
    s[i] = '\0';

    /* this block reverses the order of symbols */
    for (i--; low < i; i--, low++) {
        temp = s[i];
        s[i] = s[low];
        s[low] = temp;
    }
}

