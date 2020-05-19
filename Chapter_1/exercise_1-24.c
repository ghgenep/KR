
/* Exercise 1.24
   The program does a primitive syntax check of C programs. */

#include <stdio.h>
#define TRUE  				1
#define FALSE 				0  
#define MAX_BUFFER_SIZE		3000

int main(void) {
	int c, in_quote, in_sym, in_com;
    int s;  /* ( and ) */
    int m;  /* [ and ] */
    int k;  /* { and } */
    char out[MAX_BUFFER_SIZE];
	unsigned int i;

	in_quote = in_sym = in_com = FALSE;
	s = m = k = 0;

	for (i = 0; (c = getchar()) != EOF; ++i) {
		out[i] = c;

        /* ask a question: where are we? */
        if ((in_quote | in_sym | in_com) == FALSE) {
            if (c == '*' && out[i - 1] == '/') {
                in_com = TRUE;  /* comment is opening */
            } else if (c == '/' && out[i - 1] == '*') {
                if ((c = getchar()) != '*') { 
                    in_com = TRUE;  /* comment've not closed */
                    break;
                } else {  
                    out[i + 1] = c;
                    i++;
                    in_com = TRUE;   /* comment is opening */
                }
            } else if (c == '\'')
                in_sym = TRUE;
            else if (c == '\"')
                in_quote = TRUE;
            else if (c == '{') 
                k++;
            else if (c == '[')
                m++;
            else if (c == '(')
                s++;
            else if (c == '}')
                k--;
            else if (c == ']')
                m--;
            else if (c == ')')
                s--;
        } else if (in_com == TRUE) {
            if (c == '/' && out[i - 1] == '*')
                in_com = FALSE;
        } else if (in_sym == TRUE) {
            if (c == '\n')   /* symbols and quotes cannot have 
                                  inside the '\n' escape character */
                break;
            if (c == '\'' && (out[i - 1] != '\\' || 
                             (out[i - 1] == '\\' && out[i - 2] == '\\'))) {
                if (out[i - 1] != '\'' &&
                    out[i - 2] != '\'' &&
                    out[i - 3] != '\'')
                    break;
                else
                    in_sym = FALSE; 
            }
        } else {
            if (c == '\n')
                break;
            if (c == '\"' && (out[i - 1] != '\\' ||
                (out[i - 1] == '\\' && out[i - 2] == '\\')))
                 in_quote = FALSE;
        }
    }

    if ((in_sym | in_quote | in_com) == TRUE) { 
        if (in_sym == TRUE)
	    	printf("Check the ' and '.\n");
    	if (in_quote == TRUE)
    		printf("Check the \" and \".\n");
    	if (in_com == TRUE)
    		printf("Check the comments.\n");
    } else { 
    	if (s != 0)
    		printf("Check the ( and ).\n");
    	if (k != 0)
    		printf("Check the { and }.\n");
    	if (m != 0)
    		printf("Check the [ and ].\n");
	}

    return 0;
}
