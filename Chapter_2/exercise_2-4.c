
/* Exercise 2.4
   The program deletes in the s1 all characters from the s2. */

#include <stdio.h>

void squeeze(char s1[], char s2[]);

int main(void) {
    char s1[] = "12345678123";
    char s2[] = "1835";

    printf("s1: %s\ns2: %s\n", s1, s2);
    squeeze(s1, s2);
    printf("out: %s\n", s1);

    return 0;
}

/* squeeze: delete in the s1 all characters from the s2 */
void squeeze(char s1[], char s2[]) {
    int i, j, k;

    for (i = j = 0; s1[i] != '\0'; i++)  {
        for (k = 0; s2[k] != '\0'; k++)
            if (s1[i] == s2[k])
                break;

        /* if s1[i] != any characters from s2 */
        if (s2[k] == '\0')
            s1[j++] = s1[i];
    }
    s1[j] = '\0';
}
