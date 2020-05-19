
/* The program set a position at file and read N chars; the function
   lseek is used */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

#define BUFSIZE 10

int get(int file, long int pos, char *buf, int n);

int main(int argc, char **argv) {
	char out[BUFSIZE];
	int file;

	if ((file = open(*(argv + 1), O_RDONLY, 0)) == -1)
		fprintf(stderr, "error in open() function\n");
	if (get(file, 0x01, out, 10) == -1)
		fprintf(stderr, "error in get() function\n");
	else if (write(1, out, 10) == -1)
		fprintf(stderr, "error in write() function\n");

	return 0;
}

/* get: set a position at file and put N chars into the buf buffer */
int get(int file, long int pos, char *buf, int n) {
	if (lseek(file, pos, 0) >= 0)  /* 0 means from beginning */
		read(file, buf, n);
	else
		return -1;
}

