
/* Exercise 7.4
   The program uses minscanf() function that is like scanf().
   In format string the function can use max width, and
   following types: i, d, o, x, u, f, g, e, s and c. */

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>

#define MAX_FORMAT 100   /* max length of format string in minscanf() */
#define ERR_RETURN -2;

int minscanf(char *fmt, ...);

int main(void) {
    char s[100];
    int i;
    char c;
    printf("### counter = %d\n", minscanf("%2d%c%s, bla", &i, &c, s));
    printf("%d\n%c\n", i, c);
    printf("%s\n", s);

}

/* minscanf: like scanf(), but can contains in the format string 
   a max width, and following types: i, d, o, x, u, f, g, e, s and c;
   the function returns a number of scaned arguments */
int minscanf(char *fmt, ...) {
    va_list ap;   /* a pointer to unnamed argument in ... list */ 
    int c, counter = 0;   /* number of scaned arguments */
    char format[MAX_FORMAT], *fp;   /* format string for scanf() */

    va_start(ap, fmt);  /* take a pointer to first argument in ... list */
    for (fp = format; *fmt != '\0'; fmt++) {
        if (*fmt != '%') {
            *fp++ = *fmt;
            continue;
        } else {
            *fp++ = '%';
            while (isdigit(*++fmt)) {   /* take a max width */
                *fp++ = *fmt;
                continue;
            }
            if (*fmt == '\0') {   /* if unfinished specificator */
                printf("error: unfinished specificator\n");
                return ERR_RETURN;
            }
            *fp++ = *fmt;
            switch(*fmt) {
                case 'i': case 'd': case 'o': case 'x': case 'u':
                    *fp = '\0';
                    if (*fmt == 'u')
                        counter += scanf(format, va_arg(ap, unsigned int *));
                    else
                        counter += scanf(format, va_arg(ap, unsigned int *));
                    fp = format;
                    break;
                case 's': case 'c':
                    *fp = '\0';
                    counter += scanf(format, va_arg(ap, char *));
                    fp = format;
                    break;
                case 'e': case 'f': case 'g':
                    *fp = '\0';
                    counter += scanf(format, va_arg(ap, float *));
                    fp = format;
                    break;
                case '%':           
                    *fp++ = '%';  /* it's just '%' character */
                    break;
                default :
                    printf("error: unknown type \'%c\'\n", *fmt);
                    return ERR_RETURN;
            }
        }
        format[0] = '\0';
    }
    va_end(ap);  /* the eng of using va_ macros */
    return counter;
}

