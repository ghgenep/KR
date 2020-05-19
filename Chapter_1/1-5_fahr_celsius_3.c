
/* The program translates the degrees Celsius to degrees Fahrenheit
   and build a degrees table. */

#include <stdio.h>

int main(void) {
    int fahr;   /* let's use the for */

    for (fahr = 0; fahr <= 300; fahr = fahr + 20) {
        printf("%4d %6.1f\n", fahr, (5.0 / 9.0) * (fahr - 32));
    }

    return 0;
}

