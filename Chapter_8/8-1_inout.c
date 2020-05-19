
/* The program uses read() and write() functions to print charcters
   from input stream into output stream with buffering. */

#include <unistd.h>

#define BUFSIZE 5

int main(void) {
	char buf[BUFSIZE];
    int n;

	/* read BUFSIZE chars to buf[] buffer; there'll be not 0 character
       in the end of buffer */
	while ((n = read(0, buf, BUFSIZE)) > 0) {
		/* it's not printf() function, so we don't care about 0 at 
		   the end of buffer */
		write(1, buf, n);
		write(1, "\n", 1);
	}

	return 0;
}

