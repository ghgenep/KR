
/* Exercise 1.23 */
// The program deletes all /* and */ comments.

#include <stdio.h>

#define TRUE  1
#define FALSE 2
#define MAX   10000

int main(void) {	
	int i, c, in_quote, get_back;
	char out[MAX + 1];

	in_quote = FALSE;
	for (i = 0; (c = getchar()) != EOF && i < MAX; i++) {
		out[i] = c;
        /* are we in quote? */
        if (c == '\"' && (out[i - 1] != '\\' || out[i - 1] == '\\' && 
                                                out[i - 2] == '\\')) {
			if (in_quote == TRUE)
				in_quote = FALSE;
			else
				in_quote = TRUE;
            continue;
        }
		
		if (in_quote == FALSE && c == '*' && out[i - 1] == '/') {
			get_back = i - 1;   /* get_back is the start of comment */

			/* get the comment */
			for ( ; (c = getchar()) != EOF && i < MAX; i++) {   
				out[i] = c;
				if (c == '/' && out[i - 1] == '*')
					break;
			}

            if (c == EOF) {
                printf("ERROR1: EOF, comment is not closed\n");
                printf("%s", out);
                return 0;
            } else if (i == MAX)
                printf("ERROR: Max number of symbols is reached\n####\n\n");
			i = get_back - 1;
		}
	}
   
   if (i == MAX)
        printf("ERROR: Max number of symbols is reached\n####\n\n");

	out[i] = '\0';
	printf("%s", out);

    return 0;
}

