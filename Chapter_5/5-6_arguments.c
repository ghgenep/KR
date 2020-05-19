
/* The program uses an arguments of command line. */

#include <stdio.h>

int main(int argc, char **argv) {
    int i;

    /* argc has count of command line arguments */
    for (i = 1; i < argc; i++)
        printf("%s%s", argv[i], (i + 1 < argc) ? " " : "");
    printf("\n");
    return 0;
}
