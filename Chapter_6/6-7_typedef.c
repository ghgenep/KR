
/* The program uses typedef for creating new type of variable. */

#include <stdio.h>
#define INDEX 3

typedef char *String;
int some_function(String s, int i) {
    return s[i];
}

void print_some(void) {
    typedef int Length;
    Length value = INDEX;
    
    printf("%d", value);
}

int main(void) {
    int i = INDEX;
    String str = "12345";
/*
    Length number = 4;
    printf("some number %d\n\n", number);
    ### error: unknown type name 'Length'
*/

    printf("%s with index ", str);
    print_some();
    printf(" is ");
    printf("%c\n", some_function(str, i));
    return 0;
}

