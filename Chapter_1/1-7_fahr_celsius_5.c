
/* The program translates the degrees Celsius to degrees Fahrenheit
   and build a degrees table(from 300 to 0 degrees). */
   
#include <stdio.h>

/* Let's use simbolic constants so it's useful */
#define LOWER 0
#define UPPER 300
#define STEP 20

int main(void) {
    int fahr;

    for (fahr = UPPER; fahr >= LOWER; fahr = fahr - STEP) {
        printf("%4d %6.1f\n", fahr, (5.0 / 9.0) * (fahr - 32));
    }

    return 0;
}

