
/* The program uses strcpy() functions. */

#include <stdio.h>

/* strcpy: copy string t to string s; version 1 */
void strcpy_v1(char *s, char *t) {
    int i = 0;

    while ((s[i] = t[i]) != '\0')
        i++;
}

/* version 2 */
void strcpy_v2(char *s, char *t) {
    while ((*s = *t) != '\0') {
        s++;
        t++;
    }
}

/* version 3 */
void strcpy_v3(char *s, char *t) {
    while ((*s++ = *t++) != '\0') 
        ;
}

/* version 4 */
void strcpy_v4(char *s, char *t) {
    while (*s++ = *t++)
        ;
}

#define MAXLINE 100

int main(void) {
    char str[MAXLINE];

    strcpy_v1(str, "You are making a lot of noise.");
    printf("%s\n", str);   /* print 'hello, world' to output */
    
   strcpy_v2(str, "Could you be quieter?");
    printf("%s\n", str);   /* print 'hello, world' to output */
    
    strcpy_v3(str, "I'm trying to concentrate.");
    printf("%s\n", str);   /* print 'hello, world' to output */
    
    strcpy_v4(str, "Please.");
    printf("%s\n", str);   /* print 'hello, world' to output */

    return 0;
}

