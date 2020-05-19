
/* Exercise 1.21
   The program replace strings with only spaces on strings with 
   tabs and spaces. */

#include <stdio.h>
#define TAB 4
#define MAX 1000

/* insert_tab: replace spaces with tabs and put in the end
               some spaces. */
void insert_tab(char *string, int spaces) {
    int i, tabs;

    for (i = 0, tabs = spaces / TAB; i < tabs; i++)
        string[i] = '\t';
    i += spaces % TAB;
    string[i] = '\n';
    string[i + 1] = '\0';
}

int main(void) {
    int i, c, spaces, tabs;
    char out[MAX + 1];
    
    for (i = spaces = 0; (c = getchar()) != EOF && i < MAX; i++) {
        out[i] = c;
        if (c == ' ') {
            spaces++;
        } else if (c == '\n') {
            if (i == spaces)
                insert_tab(out, spaces);
            out[i + 1] = '\0';
            printf("%s", out);
            spaces = 0;
            i = -1;
        }
    } 
    if (c == EOF) {
        out[i] = '\n';
        out[i + 1] = '\0';
        insert_tab(out, spaces);
        printf("%s", out);
    } else if (i == MAX)
        printf("too long string!\n");
    return 0;
}    
    
