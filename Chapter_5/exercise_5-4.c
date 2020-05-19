
/* Exercise 5.4
   The program uses strend() function. */

#include <stdio.h>

/* strend: return 1, if string t is in the end of s; else - 0 */
int strend(char *s, char *t) {
    char *p = t;

    while (*s)   /* search for a zero */
        s++;
    while (*t)   /* search for a zero */
        t++;
    while (*--s == *--t)
        if (t == p)
            return 1;   /* string t is in the end of the s */
        
    return 0;   /* no */
}

int main(void)  {
    printf("%d\n%d\n", strend("123456", "456"), 
                       strend("1231414", "rrft"));
        /* output: 1    
                   0 */

    return 0;
}
    
