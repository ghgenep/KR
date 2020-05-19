
/* The program uses lower() function that converts upper
   character into lower one and returns it. */

#include <stdio.h>

int lower(int c);

int main(void) {
    printf("input is: \'A\'\n");
    printf("output is: %c\n", lower('A'));
    printf("input is: \'b\'\n");
    printf("output is: %c\n", lower('b'));
 
    return 0;
}

int lower(int c) {
    if (c >= 'A' && c <= 'Z')
        return (c - 'A' + 'a');
    else
        return c;
}

