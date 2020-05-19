
/* The program uses read() and write() function to print charcters
   from input stream into output stream without buffering. */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/* mgetc: get char from input stream and return it; if no char - EOF */
int mgetc(void) {
	char c;

	if (read(0, &c, 1) < 0) {
		fprintf(stderr, "erro in read() function\n");
		exit(1);
	}	
	return c ? (unsigned char) c : EOF;
}
   
int main(void) {
	char c;

	while ((c = mgetc()) != EOF)
		if (write(1, &c, 1) != 1) {
			fprintf(stderr, "error in write() function\n");
			exit(2);
		}

	return 0;
}

