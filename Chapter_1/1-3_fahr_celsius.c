
/* The program translates the degrees Fahrenheit to the degrees
   Felsius and build a degrees table. */

#include <stdio.h>

int main(void) {
    int fahr, celsius;
    int lower, upper, step;
    
    lower = 0;      /* lower border of the degrees range */
    upper = 300;    /* upper border of the degrees range */
    step = 20;      
    
    fahr = lower;
    while (fahr <= upper) {     /* Until fahr > upper */
        celsius = 5 * (fahr - 32) / 9;
        printf("%d\t%d\n", fahr, celsius);
        fahr = fahr + step;     /* Next step */
    }

    return 0;
}

