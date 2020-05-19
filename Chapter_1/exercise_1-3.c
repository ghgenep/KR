
/* Exercise 1.3
   The program translates the degrees Fahrenheit to the degrees Celsius
   and builds a degrees table that has a title. */

#include <stdio.h>

int main(void) {
    float fahr, celsius;
    int upper, step;
    
    fahr = 0.0;      /* lower border of the degrees table */
    upper = 300;   /* ... */
    step = 20;
  
    printf("A table of translation degrees:\nfahr celsius\n");  
    while (fahr <= upper) {
        celsius = (5.0 / 9.0) * (fahr - 32);    /* algorithm */
        printf("%4.0f %6.1f\n", fahr, celsius);
        fahr = fahr + step;
    }

    return 0;
}

