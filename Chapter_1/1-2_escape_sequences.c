
/* I'm using the escape sequences. */

#include <stdio.h>

int main(void) {
    printf("\"hello, \\world!\"\n"); 
    printf("hello\b\n");    /* o character don't disapper */
    printf("hello\ba\n");
    printf("h\tl\tlo\n"); 

    return 0;
}

