
/* Exercise 7.3
   The program uses minprintf() function that is like printf(), but
   has a limited number of parameters: minus ('-'), width, dot with 
   precision, and following types: d, f, s, o, x, X, c. */

#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int minprintf(char *fmt, ...);

int main(void) {
    int i;
    minprintf("%4.2", i);
    i = minprintf("%d\n%f\n%6.4s\n", 1, 2.0, "three");
    printf("### i = %d\n", i);
    i = minprintf("%4X\n%8.3f\n%5.4s\n", 1, 2.1234, "1234567");
    printf("### i = %d\n", i);
    i = minprintf("%-4d\n%4d\n%-10s\n", -1, -1, "123");
    printf("### i = %d\n", i);
    i = minprintf("%4o\n%c\n", 32, 'F');
    printf("### i = %d\n", i);
    return 0;
}

/* max-number of characters for format-string for printf() */
#define MAX_FORMAT 100

/* minprintf: like printf(); can process with % character: 
   minus('-'), width, dot with precision, and following types:
   d, f, s, o, x, X, c. */
int minprintf(char *fmt, ...) {
    char *p;
    va_list ap;  /* pointer to unnamed arguments in ... list */
    int counter = 0;  /* number of printed characters */
    int i;

    /* for printf() function: */
    int precision = -1;  /* if precision >= 0, precision must be printed */
    char string[MAX_FORMAT] = "";  /* first argument in printf() function */

    va_start(ap, fmt);  /* take pointer to first argument in ... list */
    for (p = fmt; *p != '\0'; p++)
        if (*p != '%') {
            counter++;
            putchar(*p);
        } else {
            strcat(string, "%");
            if (*++p == '-') {
                strcat(string, "-");
                p++;
            }
            if (isdigit(*p)) {
                i = strlen(string);
                do {
                    string[i++] = *p;
                } while (isdigit(*++p));
                string[i] = '\0';
            }
            if (*p == '.') {  /* if just dot without number, default - 0 */
                precision = atoi(p + 1);
                do {
                    string[i++] = *p;
                } while (isdigit(*++p));
                string[i] = '\0';
            }
            if (*p == '\0') {
                printf("error: there's no a type\n");
                return -1;
            }

            switch(*p) {
                case '%':
                    if (strlen(string) == 0)
                        putchar('%');
                    else {
                        printf("error: parameters between both %% characters\n");
                        return -1;
                    }
                    counter++;
                    break;
                case 'd': 
                    strcat(string, "d");
                    counter += printf(string, va_arg(ap, int));
                    break;
                case 'f':
                    strcat(string, "f");
                    counter += printf(string, va_arg(ap, double));
                    break;
                case 's':
                    strcat(string, "s");
                    counter += printf(string, va_arg(ap, char *));
                    break;
                case 'X':
                case 'x':
                    if (*p == 'x')
                        strcat(string, "x");
                    else
                        strcat(string, "X");
                    counter += printf(string, va_arg(ap, int));
                    break;
                case 'o':
                    strcat(string, "o");
                    counter += printf(string, va_arg(ap, int));
                    break;
                case 'c':
                    strcat(string, "c");
                    counter += printf(string, va_arg(ap, int));
                    break;
                default :
                    printf("error: unknown type \'%c\'\n", *p);
                    return -1;
            }
            string[0] = '\0';
        }
    va_end(ap);  /* the end of using va_ macros */
    return counter;  /* count of written characters */
}

