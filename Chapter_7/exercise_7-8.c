
/* Exercise 7.8
   The program prints files into output stream. Every file 
   starts in new page with a title. The program uses sequential 
   numbering of pages. */

#include <stdlib.h>
#include <stdio.h>

#define MAXSTR 1000  
#define PAGE_SIZE 30

int main(int argc, char **argv) {
    char str[MAXSTR];  /* for input string */
    FILE *fp;
    char *progname = *argv;  /* for usage message */
    unsigned int line_number, page_rest; 

    /* check existing arguments */
    if (argc == 1) {
		fprintf(stderr, "error: no files\n");
		printf("Usage: %s file [, file [...]]\n", progname);
		exit(1);
    }

    line_number = 0;
    while (--argc > 0) {
		if ((fp = fopen(*++argv, "r")) == NULL) {
		    fprintf(stderr, "error: can not open file %s\n", *argv);
		    exit(2);
	}
	printf("### %s:\n", *argv);

	/* get a string and print it */
	while (fgets(str, MAXSTR, fp) != NULL) {
	    printf("%5u: ", line_number);
	    line_number++;
	    fputs(str, stdout);
	    line_number++;
	}

	/* if NULL was got, check stream for an error */
	if (ferror(fp)) {
	    fprintf(stderr, "error: in opening file %s\n", *argv);
	    exit(3); 
	} 
	
	if (fclose(fp) == EOF) {
	    fprintf(stderr, "error: in closing file %s\n", *argv);
	    exit(4);
	}

	/* get number of blank lines to output stream and print them */
	page_rest = PAGE_SIZE - (line_number % PAGE_SIZE);
	while (page_rest-- > 0)
	    printf("\n");
    }
    return EXIT_SUCCESS;
}

