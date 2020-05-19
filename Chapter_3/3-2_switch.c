
/* The program uses switch operator. */

#include <stdio.h>

int main(void) {
    int i = 5;

    switch(i) {
        case 4: printf("i = 4\n");
                break;
        default: printf("i isn't found\n");
                 break;
        case 5: printf("i = 5\n");
                break;
    }

    i = 7;
    /* case and default may follow in any order */
    switch(i) {
        case 4: printf("i = 4\n");
                break;
        default: printf("i isn't found\n");
                 break;
        case 5: printf("i = 5\n");
                break;
    }

    return 0;
}

