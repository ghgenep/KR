
/* Usage:
./a.out 1 2 3 < some_file.txt
   OR:
./a.out < some_file.txt 1 2 3
   OUTPUT:
a.out 1 2
   So changing of the input stream are not saved into argv[] array. */

#include <stdio.h>

int main(int argc, char **argv) {
    printf("%s %s %s\n", *argv, *(argv + 1), *(argv + 2));
    return 0;
}

