
/* Exercise 7.6
   The program takes two files and compares them, then prints
   strings in witch they are different. If files are not
   different, prints "### no difference" and exit. */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXLINE 1000
int line_number = 0;  /* line number in a file */

char *fgets_and_check(char *str, FILE *fp, char *name);

int main(int argc, char **argv) {
    char *prog = *argv;
    FILE *fp1, *fp2;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s file1 file2\n", prog);
        exit(1);
    }
    if ((fp1 = fopen(*(argv + 1), "r")) == NULL ||
        (fp2 = fopen(*(argv + 2), "r")) == NULL) {
        fprintf(stderr, "error: file %s was not opened\n",
            (fp1 == NULL) ? *(argv + 1) : *(argv + 2));
        exit(2);
    }

    char str1[MAXLINE], str2[MAXLINE];
    while (strcmp(fgets_and_check(str1, fp1, *(argv + 1)),
                   fgets_and_check(str2, fp2, *(argv + 2))) == 0) {
        line_number++;
        if (*str1 == '\0' && *str2 == '\0') {
            /* if string == "", EOF was got */
            printf("### no difference\n");
            exit(0);
        }
    }
    line_number++;
    printf("### %s, %d line:\n%s\n", *(argv + 1), line_number, str1);
    printf("### %s, %d line:\n%s\n", *(argv + 2), line_number, str2);
    exit(0);
}

/* fgets_and_check: put string into str[], check a return value;
   if no error in reading, return pointer to string */
char *fgets_and_check(char *str, FILE *fp, char *name) {
    if (fgets(str, MAXLINE, fp) == NULL)
        if (feof(fp))
            *str = '\0';
        else {
            fprintf(stderr, "error: in reading %s file\n", name);
            exit(3);
        }
    return str;
}

