
/* Exercise 1.5
   The program translates the degrees Fahrenheit to the degrees Celsius
   and builds a degrees table(from 300 to 0).  */

#include <stdio.h>

int main(void) {
    float fahr, celsius;
    int lower, step;
    
    lower = 0;     /* lower border of the degrees table */
    fahr = 300;    /* ... */
    step = 20;
    
    printf("A table of translation degrees:\nfahr celsius\n");  
    while (fahr >= lower) {
        celsius = (5.0 / 9.0) * (fahr - 32);    /* algorithm */
        printf("%4.0f %6.1f\n", fahr, celsius);
        fahr = fahr - step;
    }

    return 0;
}

