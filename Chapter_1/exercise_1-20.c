
/* Exercise 1.20
   The program replace the tabs on spaces. */

#include <stdio.h>

#define TAB 4
#define MAX 1000

int main(void) {
	int i,j,c;
	char out[MAX + 1];
	
	for (i = 0; (c = getchar()) != EOF && i < MAX; ++i) {
		out[i] = c;
		if (c == '\t') {
			/* j == 0, if we need 4 tabs */
			for (j = (i % TAB); j < TAB; j++, i++)
				out[i] = ' ';
			i--;
		}
	}
	out[i] = '\0';
	printf("%s", out);

    return 0;
}	

