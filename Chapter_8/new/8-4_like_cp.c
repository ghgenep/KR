
/* The program copies file like cp(doesn't work with directories). The
   open() and creat() functions are used. */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdlib.h>

#define BUFSIZE 100
#define MODE    0666  /* we need to use "umask 000" command
                         to set that mode */

void error(char *fmt, ...);

int main(int argc, char **argv) {
	int f1, f2, n;
	char buf[BUFSIZE];

	if (argc != 3)
		error("Usage: cp from to");
	if ((f1 = open(*(argv + 1), O_RDONLY, 0)) == -1)
		error("cp: can't open %s\n", *(argv + 1));
	else if ((f2 = creat(*(argv + 2), MODE)) == -1)
		error("cp: can't create %s with %03o mode", *(argv + 2), MODE);
	
	while ((n = read(f1, buf, BUFSIZE)) > 0)
		if (write(f2, buf, n) != n)
			error("cp: write error on file %s\n", *(argv + 2));

	return 0;
}

/* error: print an error message and exit */
void error(char *fmt, ...) {
	va_list args;   /* for getting arguments from "..." */
	
	va_start(args, fmt);
	fprintf(stderr, "error: ");
	vfprintf(stderr, fmt, args);
	fprintf(stderr, "\n");
	va_end(args); 
	exit(1);
}

