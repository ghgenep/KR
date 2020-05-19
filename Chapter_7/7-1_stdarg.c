
/* The program uses minprintf() function, that uses a variable length list
   of variables. */

#include <stdio.h>
#include <stdarg.h>

void minprintf(char *fmt, ...);

int main(void) {
    minprintf("%d %f %s\n", 1, 2.3, "hey");
    return 0;
}

/* minprintf: like printf(), but minimal version */
void minprintf(char *fmt, ...) {
    va_list ap;  /* pointer to unnamed variables in ... list */
    char *p, *sval;
    int ival;
    double dval;

    va_start(ap, fmt);  /* set ap to a first unnamed variable */
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }
        switch (*++p) {
            case 'd':
                ival = va_arg(ap, int);  /* get an argument with type int */
                printf("%d", ival);
                break;
            case 'f':
                dval = va_arg(ap, double);   /* get next argument */
                printf("%f", dval);
                break;
            case 's':
                sval = va_arg(ap, char *);
                printf("%s", sval);
                break;
            default :
                putchar(*p);
                break;
        }
    }
    va_end(ap);   /* the end of using va_ macros */
}

