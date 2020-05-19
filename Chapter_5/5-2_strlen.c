
/* The program uses strlen() function. */

#include <stdio.h>

/* strlen: return the length of the string; version 1 */
int strlen_v1(char *s) {
    int n;
    
    for (n = 0; *s != '\0'; s++)
        n++;
        
    return n;
}

/* version 2 */
int strlen_v2(char *s) {
    char *p = s;
    
    while (*p != '\0')
        p++;
        
    return p - s;
}

int main(void) {
    printf("\"%s\" have %d characters\n", 
        "123456", strlen_v1("123456"));
    printf("\"%s\" have %d characters\n", 
        "", strlen_v2(""));

    return 0;
}
