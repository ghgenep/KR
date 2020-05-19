
/* The program demonstrates the shell sort. */

#include <stdio.h>
#include <string.h>    /* for strlen() function */

void shell_sort(char s[], int n);

int main(void) {
    char s[] = "qywuflpjgoairesnthdmzkxbcv";

    printf("now, s == \"%s\"\n", s);
    shell_sort(s, strlen(s));
    printf("insertion_sort(s, strlen(s));\n");
    printf("now, s == \"%s\"\n", s);

    return 0;
}

/* shell_sort: does the shell sort */
void shell_sort(char s[], int n) {
    int i, j, temp, gap;

    for (gap = n / 2; gap > 0; gap = gap / 2)
        for (i = gap; i < n; i++)
            for (j = i - gap; j >= 0 && s[j] > s[j + gap]; j -= gap) {
                temp = s[j];
                s[j] = s[j + gap];
                s[j + gap] = temp;
            }
}

