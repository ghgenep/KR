
/* Exercise 2.5
   The program uses any() function, that returns index for s1[] of first  
   character, that is in s1 and s2. */

#include <stdio.h>

int any(char s1[], char s2[]);

int main(void) {
    char s1[] = "1234566787";
    char s2[] = "ory4rf";

    printf("s1: %s\ns2: %s\n", s1, s2);
    printf("index(first is 0): %d\n", any(s1, s2));

    return 0;
}

int any(char s1[], char s2[]) {
    int i, j;

    for (i = 0; s1[i] != '\0'; i++) {
        for (j = 0; s2[j] != '\0'; j++)
            if (s1[i] == s2[j])
                break;

        if (s2[j] != '\0')
            return i;
    }

    return -1;  /* if s1 has not characters, that are in s2 */
}

