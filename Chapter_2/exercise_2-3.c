
/* Exercise 2.3
   The program translates a hex-string to hex-number. */

#include <stdio.h>

int main(void) {
    int c, i;

    i = 0;
    while ((c = getchar()) != EOF) {
        if (c == '0')
            if ((c = getchar()) == 'x' || c == 'X') {
                while (((c = getchar()) >= '0' && c <= '9') ||
                       (c >= 'a' && c <= 'f') ||
                       (c >= 'A' && c <= 'F')) {
                    if (c <= '9')
                        i = i * 0x10 + (c - '0');
                    else if (c <= 'F')
                        i = i * 0x10 + (c - ('A' - 10));
                    else
                        i = i * 0x10 + (c - ('a' - 10));
                }
                break;
                /* if input-number is only "0x" or "0X", i == 0; */
            }
    }
    printf("%d or 0x%x", i, i);

    return 0;
}

