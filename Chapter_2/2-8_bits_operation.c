
/* The program uses bits operations. */

#include <stdio.h>

int main(void) {
    printf("0x0F & 0x0E returns %X\n", 0x0F & 0x0E);
    printf("0x0F | 0xF0 returns %X\n", 0x0F | 0xF0);
    printf("~0x0F returns %X\n", ~0x0F);
    printf("0x0A ^ 0x0F returns %X\n", 0x0A ^ 0x0F);
    printf("~0U >> 4 returns %X\n", ~0U >> 4);
    printf("~0 >> 4 returns %X\n", ~0 >> 4);

    return 0;
}

