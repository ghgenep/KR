
/* Exercise 7.7
   The program searches a files for a pattern. If a string has a pattern,
   print that string. if there are no files, read stdin stream. 
   Usage: progname [-l -x -n] pattern [file1[, file2 [...]]]
   Options:
   -l  print the file name, if pattern exists;
   -n  print line of string with the pattern;
   -x  print string that don't have the pattern. */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int print_patt(char *, char *, int);

#define YES_PATTERNS 1
#define NO_PATTERNS 0
#define MAXLEN 1000      /* max length of string */
#define FILE_MAX_LEN 20  /* max length of file name */

/* for puting bits to int */
#define L_ARGUMENT 0x04
#define X_ARGUMENT 0x02
#define N_ARGUMENT 0x01

int main(int argc, char **argv) {
    char pattern[MAXLEN];   /* search a string for a word */
    int lxn_arg = 0;	    /* int var with argument */
    int c;
    char prog[FILE_MAX_LEN];    /* name of the program */
    char *usage_mes = "Usage: %s [-l -x -n] pattern [file1[, file2 [...]]]\n";

    strcpy(prog, *argv);
    if (argc > 1) {
		argc--;    /* name of the program */
		while ((c = **++argv) == '-') {
		    char *p = (*argv);
		    argc--;
		    while (*++p != '\0') 
				switch (*p) {
				    case 'l':
						lxn_arg |= L_ARGUMENT;   /* put bit to int */
						break;
				    case 'x': 
						lxn_arg |= X_ARGUMENT;
						break;
				    case 'n':
						lxn_arg |= N_ARGUMENT;
						break;
				    default :
						fprintf(stderr, "error: unknown argument -%c\n", *p);
						fprintf(stderr, usage_mes , prog);
						exit(1);
						break;
				}
		}
		if (argc > 0) {
		    strcpy(pattern, *argv++);
		    argc--;
		} else {
		    fprintf(stderr, "error: no pattern\n");
		    exit(2);
		}
    } else {
		fprintf(stderr, usage_mes , prog);
		return 0;
    }
    
    if (argc == 0)  /* there is no files */
		print_patt("stdin", pattern, lxn_arg);
    else 
		while (argc-- > 0) {
		    if (freopen(*argv, "r", stdin) == NULL) {
				fprintf(stderr, "error: can not open file %s\n", *argv);
		    }
		    if (print_patt(*argv, pattern, lxn_arg) == YES_PATTERNS)
				/* if patterns exist and it's not last file, print blank line */
				if (argc != 0)
			    	printf("\n");
		    argv++;
		    if (ferror(stdin)) {
				fprintf(stderr, "error: in reading stdin stream\n");
				exit(3);
		    }
		}
    return 0;
}

/* print_patt: search a string for a pattern; return:
   - YES_PATTERNS, if patterns exist;
   - else - NO_PATTERNS */
int print_patt(char *filename, char *pattern, int lxn_arg) {
    char str[MAXLEN];
    int p = 0;      
    int fname = 0;  
    int cur_line = 0;  /* current line in a file */
    
    while (fgets(str, MAXLEN, stdin) != NULL) {
		cur_line++;
		if (strstr(str, pattern) != NULL) 
		    p = 1;    /* p == 1, if pattern exists */
		else
		    p = 0;

		/* x is -x argument;
		   p is existing of pattern;
		   +---+---+---+---+---+
		   | p | 0 | 0 | 1 | 1 |
		   +---+---+---+---+---+
		   | x | 0 | 1 | 0 | 1 |
		   +---+---+---+---+---+
		       | 0 | 1 | 1 | 0 |  if 1, print string;
		       +---+---+---+---+
		   So it's XOR function;
		*/
		if ((lxn_arg & X_ARGUMENT) ^ p) {
		    if (lxn_arg & L_ARGUMENT)
				if (fname == 0) {  /* fname == 1, if name of a file is 
			                      	already printed */
			    	printf("### %s:\n", filename);
			    	fname = 1;
				}
		    if (lxn_arg & N_ARGUMENT)
				printf("line %d: ", cur_line);
		    if (fputs(str, stdout) == EOF) {
				fprintf(stderr, "error: in putting out the string\n");
				exit(4);
		    }
		}
    }
    if (ferror(stdin)) {
		fprintf(stderr, "error: in reading strings\n");
		exit(5);
    }
    if (fname == 1)
		return YES_PATTERNS;   /* need to print blank line */
    else
		return NO_PATTERNS;
}

