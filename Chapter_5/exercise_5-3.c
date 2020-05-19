
/* Exercise 5.3
   The program uses new_strcat() function. */

#include <stdio.h>

/* new_strcat: concatenate stroeg t to the end of string s */
void new_strcat(char *s, char *t) {    
    while (*s)  /* search for a zero */
        s++;
    while (*t)
        *s++ = *t++;
    *s = '\0'; 
}

int main(void) {
    char str[20] = "123";
    
    new_strcat(str, "4567\n");
    printf("%s", str);    /* print '1234567' */
    
    return 0;
}
