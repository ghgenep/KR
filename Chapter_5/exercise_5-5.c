
/* Exercise 5.5
   The program uses my_strncpy(), my_strncat() and 
   my_strncmp() functions. */

#include <stdio.h>

/* my_strncpy: copy n characters from t to s */
void my_strncpy(char *s, char *t, int n) {
    while (*s++ = *t++) 
        if (--n == 0)
           break;
}

/* my_strncat: concatenate t to the end of t; size of t = n */
void my_strncat(char *s, char *t, int n) {
    while (*s)
        s++;
    while (*s++ = *t++)
        if (--n == 0)
            break;
}

/* my_strncmp: compare first n characters of s and t strings */
int my_strncmp(char *s, char *t, int n) {
    while (*s == *t)
        if (--n == 0)
            return 0;  /* if string s == string t */
        else 
            s++, t++;

    return *s - *t;  /* < 0, if string s < t
                        > 0, if s > t */
}
            
int main(void) {
    char str[20] = "";
    
    my_strncpy(str, "123123", 3);
    printf("%s\n", str);   /* print '123' */
    
    my_strncat(str, "456789", 3);
    printf("%s\n", str);   /* print '123456' */
    
    printf("%d\n", my_strncmp(str, "123567", 5)); /* negative number */

    return 0;
}
