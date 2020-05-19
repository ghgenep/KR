
/* The program checks whether elements of array is 0 if they are not
   initialized? */

#include <stdio.h>

#define N 10

int ex_arr[N] = {1, 2, 3};  /* ex_arr[3, ... N-1] must be == 0 */

int main(void) {
    int i;
    int in_arr[N] = {1, 2, 3};  /* in_arr[3, ... N-1] must be == 0 
                                  let's check it: */    
    for (i = 0; i < N; i++)
        printf("external ex_arr[%d] = %d\t"
               "internal in_arr[%d] = %d\n\n", i, in_arr[i], i, ex_arr[i]);
               
    /* yes, it's true */
    return 0;
}

