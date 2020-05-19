
/* Exercise 4.14
   The program uses swap macro, that exchanges two arguments. */

#include <stdio.h>

/* swap: exchange x and y, that have type t */
#define swap(x, y, t)   \
{                       \
    t temp = x;         \
    x = y;              \
    y = temp;           \
}

int main(void) {
    int i = 0;
    int k = 4;
    
    printf("i = %d\nk = %d\n\n", i, k);
    swap(i, k, int);
/*  
    {
        int temp = i;
        i = k;
        k = i;
    }
*/
    printf("i = %d\nk = %d\n", i, k);
    
    return 0;
}

