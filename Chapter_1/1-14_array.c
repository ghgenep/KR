
/* The program counts digits, space characters and the other. */

#include <stdio.h>

int main(void) {
    int c, i, nwhite, nother;
    int ndigit[10];
    
    nwhite = nother = 0;
    for (i = 0; i < 10; ++i) 
        ndigit[i] = 0;
        
    while ((c = getchar()) != EOF) {
        if (c >= '0' && c <= '9')
            ++ndigit[c-'0'];
            /* '1'(0x31) - '0'(0x30) = 1(0x01)
               ... */
        else if (c == ' ' || c == '\t' || c == '\n')
            ++nwhite;
        else
            ++nother;
    } 
            
    printf("digits = ");
    for (i = 0; i < 10; ++i)
        printf("%d, ", ndigit[i]);
    printf(", white space = %d, other = %d\n",
            nwhite, nother);

    return 0;
}

