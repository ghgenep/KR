
/* Exercise 1.13
   Version 1
   The program outputs a horizontal histogram of word lengths. */

#include <stdio.h>

int main(void) {
    int c, i, j, length;
    int array[4];
    
    for (i = 0; i <= 3; ++i)
        array[i] = 0;        
    length = 0;     /* length of word */

    do {
        c = getchar();
        if (c != ' ' && c != '\t' && c != '\n' && c != EOF) { /* if symbol */
            ++length;
        } else if (length != 0) {   /* distribute words */
            if (length <= 4)
                ++array[0];
            else if (length <= 8)
                ++array[1];
            else if (length <= 12)
                ++array[2];
            else
                ++array[3];
                
            length = 0;
        }
    } while (c != EOF);

    /* print the histogram */
    for (i = 0; i <= 2; ++i) {
        printf("\n[%2d -%2d]: %3d ", (i * 4) + 1, 
                                (i * 4) + 4,
                                array[i]);
        for (j = 1; j <= array[i]; ++j)
            putchar('*');
    }
    printf("\n[13 -..]: %3d ", array[3]);
    while (array[i]--)
            putchar('*');
    putchar('\n');

    return 0;
}
            
