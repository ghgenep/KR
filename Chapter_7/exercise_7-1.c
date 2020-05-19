
/* Exercise 7.1
   The program echoes input to output stream. If an argument is "lower", 
   letters change their case to lower one; if "upper", - to upper one;
   otherwise - print an error. */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char **argv) {
    int (*function)(int);   /* pointer to function: either tolower()
                               or toupper() from ctype.h */
    int c;

    if (argc != 2) {
        /* argc keep a number of arguments of the program plus one */
        if (argc == 1)
            printf("error: program don't have an argument!\n");
        else
            printf("error: must be two arguments, not %d\n", argc - 1);
        printf("Usage: ./goto <upper/lower>\n");
        return 0;
    }

    argv++;   /* pointer to a first argument */
    if (strcmp("upper", *argv) == 0) 
        function = toupper;
    else if (strcmp("lower", *argv) == 0) 
        function = tolower;
    else {
        printf("error: unknown argument \"%s\"\n", *argv);
        return 0;
    }
    while ((c = getchar()) != EOF)
        putchar((*function)(c));
    return 0;
}

