
/* The program uses squeeze(s, c) function, that deletes all
   c characters in s string. */

#include <stdio.h>

void squeeze(char s[], int c);

int main(void) {
    char s[10] = "123421";

    printf("s == \"%s\"\n", s);
    printf("squeeze(s, '2');\n");
    squeeze(s, '2');
    printf("s == \"%s\"\n", s);

    return 0;
}

/* squeeze: deletes all c characters in s string */
void squeeze(char s[], int c) {
    int i, j;

    for (i = j = 0; s[i] != '\0'; i++)
        if (s[i] != c)
            s[j++] = s[i];
    s[j] = '\0';
}

