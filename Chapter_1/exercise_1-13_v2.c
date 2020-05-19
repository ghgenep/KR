
/* Exercise 1.13
   Version 2
   The program prints a vertical historgam of word lengths. */
 
#include <stdio.h>

int main(void) {
    int c, i, j, max, length;
    int array[4]; /* for count of words */
    int array2[4]; /* for symbols of diagram('*' or ' ') */
    
    for (i = 0; i <= 3; ++i) { /* count = 0, symbol = ' ' */
        array[i] = 0;
        array2[i] = ' ';
    }
    length = 0; /* length of word */
    
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
    
    max = array[0]; /* I search for max value */
    for (i = 1; i <= 3; ++i)
        if (max < array[i])
            max = array[i];

    printf("\n");
    /* print the colomns */        
    for ( ; max > 0; --max) {  /* max - biggest high of column */
        for (i = 0; i <= 3; ++i)
            if (array[i] == max)    /* array[i] - high of any column */
                array2[i] = '*';
        printf("%6c%6c%7c%8c\n", array2[0], array2[1],
                                 array2[2], array2[3]);
    }
    
    printf("---------------------------\n");
    printf("%6d%6d%7d%8d\n", array[0], array[1],
                             array[2], array[3]);
    printf(" [1-4] [5-8] [9-12] [13-...]\n");

    return 0;
}

