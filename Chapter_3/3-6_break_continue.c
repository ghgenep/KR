
/* The program uses delete_spaces() function that deletes all 
   spaces in the end of string. */

#include <stdio.h>
#include <string.h>  /* for strlen() function */

void delete_spaces(char s[]);

int main(void) {
    char s[] = "123        \n    ";
    
    printf("now, s == \"%s\"\n", s);
    delete_spaces(s);
    printf("delete_spaces(s);\n");
    printf("now, s == \"%s\"\n", s);

    return 0;
}

void delete_spaces(char s[]) {
    int n;

    for (n = strlen(s) - 1; n >= 0; n--)
        if (s[n] != ' ' && s[n] != '\t' && s[n] != '\n')
            break;
/* or:
        if (s[n] == ' ' || s[n] == '\n' || s[n] == '\t')
            continue; 
        else
            break;
*/
    s[n + 1] = '\0';
}

