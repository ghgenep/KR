
/* Exercise 1.14
   The program outputs a horizontal histogram of letters([a-z]). */

#include <stdio.h>

int main(void) {
    int c, i;
    int array[26];
    
    for (i = 0; i <= 26; ++i)
        array[i] = 0;        

    while ((c = getchar()) != EOF) {
        if (c >= 'a' && c <= 'z') /* if symbol */
            ++array[c - 'a'];
    }

    /* print the histogram */
    for (i = 0; i <= 25; ++i) {
        printf("a: %3d ", array[i]);
        while (array[i]--)
            putchar('*');
        putchar('\n');
    }

    return 0;
}
            
