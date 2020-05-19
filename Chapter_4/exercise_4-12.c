
/* Exercise 4.12
   The program uses itoa(i, s) function, that translates i-number
   into string and place it to s. The itoa() function uses a 
   recursion. */
   
#include <stdio.h>

void itoa(int i, char s[]);

int main(void) {
    char s[10] = "987654";
    
    printf("s == \"%s\"\n", s);
    itoa(-123, s);
    printf("itoa(-123, s) write to s \"%s\"\n", s);
    
    return 0;
}

/* itoa: translates i-number into string and place it to s */
void itoa(int i, char s[]) {
    static int j = 0;
    
    if (i < 0) {  /* change sign */
        s[j++] = '-';
        i = -i;
    }
    if ((i / 10) != 0)  /* stop when i has one digit */
        itoa(i / 10, s);
    s[j++] = i % 10 + '0';
    s[j] = '\0';    /* in case we have reached the last digit */
}

