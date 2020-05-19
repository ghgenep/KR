
/* The program uses strcmp() functions. */

#include <stdio.h>

/* strcmp: compare the s and t strings; version 1 */
int strcmp_v1(char *s, char *t) {
    int i;
    
    for (i = 0; s[i] == t[i]; i++)
        /* if s[i] == s[i], so string s == string t  ---> 0 */
        if (s[i] == '\0')       
            return 0;
    
    return s[i] - t[i];     /* s[i] > s[i] ---> positive
                               s[i] < s[i] ---> negative */
                               
}

/* version 2 */
int strcmp_v2(char *s, char *t) {    
    for ( ; *s == *t; s++, t++)
        if (*s == '\0')      
            return 0;
    
    return *s - *t;    
}

int main(void) {
    
    printf("%d\n", strcmp_v1("1", "2"));    /* -1 */
    printf("%d\n", strcmp_v2("1", "1"));    /* 0 */
    printf("%d\n", strcmp_v1("3", "1"));    /* 2 */

    return 0;
}
