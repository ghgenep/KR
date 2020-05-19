
/* The program uses have_equal(s1, s2) function that prints "YES", 
   if s2 and s1 have one or more same characters. Otherwise,
   the function prints "NO". 
   The program uses goto operator. */

#include <stdio.h>

void have_equal(char s1[], char s2[]);

int main(void) {
    char s1[] = "123456789";
    char s2[] = "aoyf1oru";

    have_equal(s1, s2);

    return 0;
}

/* have_equal() demonstrates goto operator */
void have_equal(char s1[], char s2[]) {
    int i, j;

    for (i = 0; s1[i] != '\0'; i++)
        for (j = 0; s2[j] != '\0'; j++) 
            if (s1[i] == s2[j]) {
                printf("YES! s1[%d] and s2[%d] have '%c'",
                                    i, j, s1[i]);
                goto YES_and_out;
            }
    printf("NO! s1[%d] and s2[%d] have not same character.", i, j);
    YES_and_out: ;   /* if ';' is not in the end of statement,
         the error "label at end of compound statement" will be 
         occurred. */
}
    
