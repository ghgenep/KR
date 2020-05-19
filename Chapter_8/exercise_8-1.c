
/* Exercise 8.1
   The program does what cat program does. The read(), write(), open()
   and close functions are used. */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdlib.h>

#define BUFSIZE 1024

void error_exit(char *mes, int exit_value, ...);
void filecopy(int inf, int outf);

int main(int argc, char **argv) {
	int inf, f;

	if (argc == 1)
		filecopy(0, 1);

	f = 1;  /* number of file in argv[] array */
	while (argc-- > 1)
		if ((inf = open(*(argv + f), O_RDONLY, 0)) == -1)
			error_exit("error: in opening file %s\n", 1, *(argv + f));
		else {
			filecopy(inf, 1);
			close(inf);
			f++;  /* next file */
		}

	return 0;
}

/* filecopy: copy characters from stream inf into stream outf */
void filecopy(int inf, int outf) {
	char buf[BUFSIZE];
	int n;

	while ((n = read(inf, buf, BUFSIZE)) > 0)
		if (write(outf, buf, n) != n) 
			error_exit("error: in write() function\n", 2);
	if (n != 0)  /* if it's ok, n have to be 0 */
		error_exit("error: in read() function\n", 3);
}

/* error_exit: print an error message end exit with some value */
void error_exit(char *mes, int exit_value, ...) {
	va_list args;  /* for getting arguments from "..." */

	va_start(args, exit_value);
	vfprintf(stderr, mes, args);
	va_end(args);
	exit(exit_value);
}

