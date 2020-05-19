
/* The file contains printf_my() static function. Can it be visible
   out of file? NO, it cannot! Also, the file contains printf_new()
   function, that uses printf_my() function and can be visible out
   of file. */
   
#include <stdio.h>

static void printf_my(void) {
    printf("This is static function!\n");
}

void printf_new(void) {
    printf_my();
}

