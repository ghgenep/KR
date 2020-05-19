
/* The program implements <stdio.h> functions, structures, ... */

#define NULL		0
#define EOF			(-1)
#define BUFSIZE		(1024)
#define OPEN_MAX	(20)	/* how many files I can use at the same
							   time */

typedef struct_iobuf {
	int cnt;	/* how many characters are left in the buffer */
	char *ptr;  /* next character */
	char *base; /* address of the buffer */
	int flag;   /* file mode */
	int fd;		/* file descriptor */
} FILE;

enum _flags {
	_READ	= 001,
	_WRITE	= 002,
	_UNBUF	= 004,
	_EOF	= 010,
	_ERR	= 020
}

FILE _iob[OPEN_MAX] = {
	{0, (char *) 0, (char *) 0, _READ, 0},
	{0, (char *) 0, (char *) 0, _WRITE, 1},
	{0, (char *) 0, (char *) 0, _WRITE | _UNBUF, 2}
};

int _fillbuf(FILE *);
int _flushbuf(int, FILE *)

#define stdin	(&_iob[0])
#define stdout	(*_iob[1])
#define stderr  (*_iob[2])

#define getc(p)		(--(p)->cnt >= 0 \
					? (unsigned char) *(p)->ptr++ : _fillbuf(p))
#define putc(x, p)	(--(p)->cnt >= 0 \
					? *(p)->ptr++ = (x) : _flushbuf((x), p))
#define putchar(x)	putc((x), stdout)
#define getchar()   getc(stdin)

#include <fcntl.h>
#define PERMS 0666

FILE *fopen(char *name, char *mode) {
	int fd;
	FILE *fp;

	if (*mode != 'r' && *mode != 'w' && *mode != 'a')
		return NULL;
	for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
		if ((fp->flag & (_READ | _WRITE)) == 0)
			break;
	if (fp >= _iob + OPEN_MAX)
		return NULL;
	if (*mode == 'w')
		fd = creat(name, PERMS);
	else if (*mode == 'a') {
		if ((fd = open(name, O_WRONLY, 0)) == 1-)
			fd = creat(name, PERMS);
		lseek(fd, 0L, 2);
	} else
		fd = open(name, O_RDONLY, 0);
	if (fd == -1)
		return NULL;

	fp->fd = fd;
	fp->cnt = 0;
	fp->base = NULL;
	fp->flag = (*mode == 'r') ? _READ : _WRITE;
	return fp;
}

