
/* The program check a statement "a variable, declared in internal
   composite operator(block), blocks the same name variable in 
   external composite operator. YES, it's true. */
   
#include <stdio.h>

int main(void) {
    int i, k;
    
    k = 0;
    i = 0;
    printf("i = %d\nk = %d\n\n", i, k);   /* 0 0 */
    if (i == 0) {
        int i;  /* block i variable in an external block */
        k = 1;
        i = 1;
        printf("i = %d\nk = %d\n\n", i, k);   /* 1 1 */
    }
    printf("i = %d\nk = %d\n\n", i, k);   /* 0 1 */
    {       /* is a composite operator */
        int i = 2;
        k = 2;
        printf("i = %d\nk = %d\n\n", i, k);   /* 2 2 */
    }
    printf("i = %d\nk = %d\n\n", i, k);   /* 0 2 */
    
    return 0;
}

