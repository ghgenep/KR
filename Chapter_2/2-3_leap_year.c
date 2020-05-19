
/* The program prints that a year is or isn't leap. */

#include <stdio.h>

int main(void) {
    int year = 0;
    while (year <= 500) {
        if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
            printf("Year %3d is leap\n", year);
        else
            printf("Year %3d is not leap\n", year);
        year = year + 21;
    }

    return 0;
}

