
/* The program uses atoi(s) function that translates number-string s 
   into number and returns it. */

#include <stdio.h>
#include <ctype.h>

int atoi(char s[]);

int main(void) {
    char s1[10] = "  -1342";
    char s2[10] = "  +1342";

    printf("s1 == \"%s\"\n", s1);
    printf("s2 == \"%s\"\n", s2);
    printf("atoi(s1) returns %d\n", atoi(s1));
    printf("atoi(s2) returns %d\n", atoi(s2));    

    return 0;
}

/* atoi: translates number-string s into number and returns it */
int atoi(char s[]) {
    int i, sign, n;

    for (i = 0; isspace(s[i]); i++)
        ;
    sign = (s[i] == '-') ? -1 : 1;   /* set the sign */
    if (s[i] == '+' || s[i] == '-')
        i++;

    for (n = 0; isdigit(s[i]); i++)   /* translate string into number */
        n = n * 10 + (s[i] - '0');
    
    return (n * sign);
}

