
/* The swap function. Version 1. */
#include <stdio.h>

/* swap: copy x to y, and y to x */
void swap(int *x, int *y) {
    int term;   /* for storing a temporary value */ 
    
    term = *x;
    *x = *y;
    *y = term;
}

int main(void) {
    int x, y;

    x = 4;
    y = 5;
    printf("x = %d, y = %d\n", x, y);   /* print 'x = 4, y = 5' */
    swap(&x, &y);
    printf("x = %d, y = %d\n", x, y);   /* print 'x = 5, y = 4' */

    return 0;
}
