
/* The program uses mgetchar() function written with read() function. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFSIZE 5

/* mgetchar: get any number of chars from input stream and return
   only one character; if no char - return EOF */
int mgetchar(void) {
	static char buf[BUFSIZE];
	static char *bufp = buf;
	static int n = 0;

	if (n == 0) {  /* if the buffer is empty */
		if ((n = read(0, buf, sizeof buf)) == -1) {
			fprintf(stderr, "erro in read() function\n");
			exit(1);
		}
		bufp = buf;
	}
	return (--n >= 0) ? (unsigned char) *bufp++ : EOF;
}

int main(void) {
	int c;

	while ((c = mgetchar()) != EOF)
		fprintf(stdout, "%c", c);

	return 0;
}
    
