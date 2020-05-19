
/* Exercise 1.19
   The program uses the reverse function for printing every line. */

#include <stdio.h>

/* reverse: reverse string and put it into out */
void reverse(char *string) {
    int i, j, c;
    
    for (i = 0; string[i] != '\0'; i++) /* '\0' - end of a string */
        ;
    i--;
    for (j = 0; i > j; j++, i--) {
        c = string[j];
        string[j] = string[i];
        string[i] = c;
    }
}

/* main: read every line, reverse it and print now */
int main(void) {
    int c, i;
    char source[1000];
    
    i = 0;
    while ((c = getchar()) != EOF) {
        if (c != '\n') { 
            source[i] = c;
            i++;
        } else {
            source[i] = '\0';
            reverse(source);
            printf("%s\n", source);
            i = 0;
        }            
    }

    return 0;
}

