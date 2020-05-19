
/* The program translates the degrees Fahrenheit to the degrees
   Celsius and build a degrees table. */

#include <stdio.h>

int main(void) {
    float fahr, celsius;
    int lower, upper, step;
    
    lower = 0;      /* lower border of the degrees table */
    upper = 300;    /* upper border of the degrees table */
    step = 20;
    
    fahr = lower;
    while (fahr <= upper) {
        celsius = (5.0 / 9.0) * (fahr - 32);
        printf("%3.0f %6.1f\n", fahr, celsius);
        fahr = fahr + step;     /* next step */
    }

    return 0;
}

