
/* Exercise 7.2
   The program prints input text to a imaginary screen. The width of screen
   is 80 characters(by default), but it can be changed by WIDTH constant
   below. And lines don's cross the screen.
   The options:
   -x   - print an unprinted characters with hexadecimal code(default);
   -o   - print an unprinted characters with octal code;
   -l   - print all letters in lower case;
   -u   - print all letters in upper case. */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

int indent = 1;   /* an indent in beginning of line: 1 - is, 0 - isn't */

/* variables below are changed by get_argument() function: */
unsigned int hexadecimal = 0;
unsigned int octal = 0;
unsigned int upper = 0;
unsigned int lower = 0;

#define ERR_RETURN 0
#define OK_RETURN 1
#define WIDTH 80      /* width of the wanted screen */

int get_arguments(int, char **);
int tonothing(int);
int getch(void);
void ungetch(int);

int main(int argc, char **argv) {
    int status, c, i, old_i;
    char out_string[WIDTH * 2];
    char *format;          /* output format for unprinted characters */
    int (*function)(int);  /* pointer to tolower() or toupper() function */

    if ((status = get_arguments(argc, argv)) == ERR_RETURN) {
        printf("Usage: ./a.out [-x -o -u -l]\n");
        return 0;
    }

    i = 0;
    if (upper)
        function = toupper;
    else if (lower)
        function = tolower;
    else
        function = tonothing;

    if (hexadecimal)
        if (lower)
            format = "0x%x";
        else
            format = "0x%X";
    else
        format = "0%o";

    while ((c = getch()) != EOF) {
        /* delete spaces in beginning of line, if we
           don't wait for indent */
        if (i == 0 && indent == 0)
            if (isspace(c) && c != '\n')
                while (isspace(c = getch()))
                    if (c == '\n')
                        continue;
        /* if '\n', it is a last line of paragraph; print it */
        if (c == '\n') {
            out_string[i] = '\0';
            printf("%s\n", out_string);
            i = 0;
            indent = 1;  /* let's wait for indent */
            continue;
        }
        /* if c is unprinted character, print its hexadecimal or
           octal code */
        if (iscntrl(c)) {
            old_i = i;
            /* sprintf() returns a number of characters whitten */
            i += sprintf(out_string + i, format, (unsigned int) c);
            if (i > WIDTH) {
                while (old_i != i)
                    ungetch(out_string[i--]);
                out_string[old_i] = '\0';
                indent = 0;   /* we don't wait for indent */
                printf("%s\n", out_string);
                i = 0;
            }
            continue;
        }
        if (i < WIDTH) {
            out_string[i] = (*function)(c);
            i++;
        } else {    /* too many characters */
            if (c == '\n')   /* may be skipped, it's ok */
                indent = 1;
            else {
                indent = 0;
                ungetch(c);
            }
            /* line can end in a middle of a word; if don't: */
            if (isspace(out_string[--i]) || isspace(c)) {
                out_string[i + 1] = '\0';
            } else {
                /* search for start of current word */
                while (!isspace(out_string[i]))
                    if (i >= 0)
                        ungetch(out_string[i--]);
                    else {   /* word has WIDTH or more characters */
                        printf("error: too long word!\n");
                        return 0;
                    }
                out_string[i] = '\0';
            }
            i = 0;
            printf("%s\n", out_string);
        }
    }
    /* if c == EOF and there's no '\n' in the end of input text,
       print a last line correctly */
    if (i != 0) {
        out_string[i] = '\0';
        printf("\n%s\n", out_string);
    }
    return 0;
}

/* get_arguments: process arguments and return ERR_RETURN or
   OK_RETURN */
int get_arguments(int argc, char **argv) {
    char *current;    /* current argument */

    while (argc-- > 1) {
        current = *++argv;
        if (*current == '-' && *(current + 1) != '\0') {
            while (*++current != '\0')
                switch (*current) {
                    case 'x':
                        hexadecimal = 1;
                        break;
                    case 'o':
                        octal = 1;
                        break; 
                    case 'l':
                        lower = 1;
                        break; 
                    case 'u':
                        upper = 1;
                        break; 
                    default :
                        printf("error: unknown argument -%c\n", *current);
                        return ERR_RETURN;
                }
        } else {
            printf("error: unknown argument %c\n", *current);
            return ERR_RETURN;
        }
    }
    if (octal && hexadecimal)
        printf("error: both -o and -x are set\n");
    else if (lower && upper)
        printf("error: both -u and -l are set\n");
    else {
        if (octal == 0)
            hexadecimal = 1;
        return OK_RETURN;
    }
    return ERR_RETURN;
}

/* tonothing: return c; is used when tolower() and toupper() are
   not used */
int tonothing(int c) {
    return c;
}

int buf[WIDTH];  /* a buffer for getch() and ungetch() functions */
int bp = 0;

/* getch: return character from buffer, or use getchar() */
int getch(void) {
    return (bp > 0 ? buf[--bp] : getchar());
}

/* ungetch: put character into buffer */
void ungetch(int c) {
    if (bp < WIDTH)
        buf[bp++] = c;
    else
        printf("error: too many characters in buffer!\n");
}

