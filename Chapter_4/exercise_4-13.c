
/* Exercise 4.13
   The program uses reverse(s) function, that reverses the order of
   characters in s by using recursion. */
   
#include <stdio.h>

void reverse(char s[]);

int main(void) {
    char arr[] = "123456789";
    
    printf("arr = \"%s\"\n", arr);
    reverse(arr);
    printf("reverse(arr)\n");
    printf("arr = \"%s\"\n", arr);
    
    return 0;
}

/* reverse: reverse the order of characters in s */
void reverse(char s[]) {
    static int i = 0;  
    static int j = 0;
    int c;
    
    if (s[i] != '\0') {
        c = s[i++];
        reverse(s);
    } else
        return;  /* if s[i] == '\0', c contains random value */
    s[j++] = c;
}

