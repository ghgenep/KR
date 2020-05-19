
/* The program uses (expression_1)?(expression_2):(expression_3)
   expression. */

#include <stdio.h>

int main(void) {
    printf("%f\n", (1) ? 2.0 : 2);

    return 0;
}
	
/* Notes:
   If expression_2 and expression_3 have different types, the
   expression has "the highest" type. So printf() function must 
  have "%f" string but not "%d". */

