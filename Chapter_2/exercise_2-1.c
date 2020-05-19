
/* Exercise 2.1
   The program prints max and min values of char, short, int and 
   long types. */

#include <stdio.h>
#include <limits.h>

int main(void) {
    unsigned char uc = -1;
    unsigned short us = -1;
    unsigned int ui = -1;
    unsigned long ul = -1;

    printf("From limits.h:\n");
    printf("signed char: max = %d --- min = %d\n"
           "unsigned char: max = %u --- min = 0\n"
           "signed short: max = %d --- min = %d\n"
           "unsigned short: max = %u --- min = 0\n"
           "signed int: max = %d --- min = %d\n"
           "unsigned int: max = %u --- min = 0\n"
           "signed long: max = %ld --- min = %ld\n"
           "unsigned long: max = %lu --- min = 0\n\n",
                   SCHAR_MAX, SCHAR_MIN, UCHAR_MAX,
                   SHRT_MAX, SHRT_MIN, USHRT_MAX,
                   INT_MAX, INT_MIN, UINT_MAX,
                   LONG_MAX, LONG_MIN, ULONG_MAX);

    printf("by myself:\n"
           "signed char: max = %d --- min = %hhd\n"
           "unsigned char: max = %u --- min = 0\n"
           "signed short: max = %d --- min = %hd\n"
           "unsigned short: max = %u --- min = 0\n"
           "signed int: max = %d --- min = %d\n"
           "unsigned int: max = %u --- min = 0\n"
           "signed long: max = %ld --- min = %ld\n"
           "unsigned long: max = %lu --- min = 0\n",
                uc >> 1, (uc >> 1) + 1, uc,
                us >> 1, (us >> 1) + 1, us,
                ui >> 1, (ui >> 1) + 1, ui,
                ul >> 1, (ul >> 1) + 1, ul);

    return 0;
}

