
/* The program uses an arguments of command line. This version uses argv
   variable as pointer. */

#include <stdio.h>

int main(int argc, char **argv) {
    while (--argc > 0)
        printf("%s%s", *++argv, (argc > 1) ? " " : "");
    printf("\n");
    return 0;
}
