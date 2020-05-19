
/* Exercise 1.22
   The program cuts too long lines into shorter ones. */

#include <stdio.h>
#define COLUMN 80   /* max number of symbols in line */
#define YES 1
#define NO 0

int main(void) {
    int c, i, base;
    char out[COLUMN + 1];	/* +1 in order to know a next character */
    int newline = NO;    /* is the mandatory newline character */

    for (i = 0; (c = getchar()) != EOF; i++) {
        out[i] = c;
        if (c == '\n') {    /* and i <= COLUMN - 1 */
            out[i] = c;
            out[i + 1] = '\0';
            newline = YES;
        }
        else if (i == COLUMN - 1) {
            if (c != '\t' && c != ' ') {
                /* if line ends when we're in word */
                if ((out[i + 1] = c = getchar()) != ' ' && c != '\t' &&
                                               c != '\n') {   
                    while (out[i] != '\t' && out[i] != ' ') {
                        i--;
                    }
                    base = i + 1;    /* where word starts */
                    out[i] = '\0';
                    printf("%s\n", out);
                    i = 0;
                    while (base <= COLUMN)   /* copying */
                        out[i++] = out[base++];
                    i--;
                    continue;
                }
                out[i + 1] = '\0';
            }
            out[i] = '\0';
        } else
            continue;

        printf("%s", out);
        while ((c = getchar()) == '\n' || c == ' ' || c == '\t')
            /* if c is EOF, it is known in main FOR cycle */    
            if (c == '\n') {
                printf("\n");
                newline = YES;
            }
            
        out[0] = c;
        if (newline == NO)
           /* newline variable is needed when more shorter lines are created */
            printf("\n");
        i = 0;
        continue;
    }

    return 0;
}
