
/* Exercise 1.4
   The program translates the degrees Celsius to degrees Fahrenheit 
   and builds a degrees table. */

#include <stdio.h>

int main(void) {
    float fahr, celsius;
    int upper, step;
    
    celsius = 0;     /* lower border of the degrees table */
    upper = 100;    /* ... */
    step = 10;
    
    while (celsius <= upper) {
        fahr = (9.0 / 5.0 * celsius) + 32;     /* algorithm */
        printf("%4.0f %6.1f\n", celsius, fahr);
        celsius = celsius + step;
    }

    return 0;
}

