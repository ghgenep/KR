
/* Exercise 2.10
   The program uses a new lower() function. */

#include <stdio.h>

int lower(int c);

int main(void) {
    printf("lower('B') returns '%c'\n"
           "lower('c') returns '%c'\n", lower('B'), lower('c'));

    return 0;
}

int lower(int c) {
    return (c >= 'A' && c <= 'Z') ? (c - 'A' + 'a') : c;
}

