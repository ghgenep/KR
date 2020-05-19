
/* The program demonstrates the insertion sort. */

#include <stdio.h>
#include <string.h>   /* for strlen() function */

void insertion_sort(char s[], int n);

int main(void) {
    char s[] = "35488602178";

    printf("now, s == \"%s\"\n", s);
    insertion_sort(s, strlen(s));
    printf("insertion_sort(s, strlen(s));\n");
    printf("now, s == \"%s\"\n", s);

    return 0;
}

/* insertion_sort: does insertion sort */
void insertion_sort(char s[], int n) {
    int i, j, temp, c;

    for (i = 1; i < n; i++)
        for (j = i; j > 0 && s[j - 1] > s[j]; j--) {
            temp = s[j];
            s[j] = s[j - 1];
            s[j - 1] = temp;
        }
}

