
/* Exercise 1.15
   The program translates degrees Fahrenheit to degrees Celsius. */

#include <stdio.h>

int get_celsius(int fahr);

int main(void) {
    int celsius, fahr;
    int upper, step;
    
    upper = 300;
    step = 20;
    
    printf("fahr -> celsius\n");   
    for (fahr = 0; fahr <= upper; fahr = fahr + step) {
        celsius = get_celsius(fahr);
        printf("%4d -> %3d\n", fahr, celsius);
    }

    return 0;
}

/* get_celsius: translates degrees Fahrenheit to degrees Celsius
                and return it */
int get_celsius(int fahr) {
    return (5.0 / 9.0) * (fahr - 32);
}

