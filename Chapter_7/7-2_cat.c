
/* The program does what cat program does. */

#include <stdio.h>

int main(int argc, char **argv) {
    FILE *fp;   /* fp is pointer to FILE structure */
    void filecopy(FILE *, FILE *);
    char *prog = *argv;

    if (argc == 1)
        filecopy(stdin, stdout);
    else
        while (--argc > 0)
            if ((fp = fopen(*++argv, "r")) == NULL) {
                fprintf(stderr, "%s: can't open %s\n", prog, *argv);
                exit(1);
            } else {
                filecopy(fp, stdout);
                fclose(fp);
            }
    /* ferror() return non-zero if an error was in a stream */
    if (ferror(stdout)) {
        fprintf(stderr, "%s: error writing stdout\n", prog);
        exit(2);
    }
    exit(0);
}

/* filecopy: copy characters from the stream ifp to stream ofp */
void filecopy(FILE *ifp, FILE *ofp) {
    int c;

    while ((c = getc(ifp)) != EOF)
        putc(c, ofp);
}

