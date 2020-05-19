
/* Exercise 5.14
   The program uses my_my_qsort() function that can take -n and -r keys:
   -n       sort an array not by alphabet, but by numeric value
   -r       sort an array in the reverse order */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>  /* for atof() function */

#define MAXPTR 5000
char *lineptr[MAXPTR];   /* an array of pointer to input starings */

int readlines(char **, int);
void writelines(char **, int);
void my_qsort(void **, int, int, int (*)(void *, void *));
int numcmp(const char *, const char *);

int main(int argc, char **argv) {
    void reverse(void **, int);
    int nlines;         /* count of lines read */
    int numeric = 0;    /* if 1, numerical sorting */
    int rev = 0;    /* if 1, reverse sorting */
    int c;
    
    while (--argc > 0 && *(*++argv) == '-')
        while ((c = *++(*argv)) != '\0')
            switch (c) {
                case 'n': 
                    numeric = 1;
                    break;
                case 'r':
                    rev = 1;
                    break;
                default :
                    printf("error: illegal otpion \'%c\'\n", c);
                    argc = -1;
                    break;
            }
    if (argc != 0) {
        printf("Usage: program_name -n -r\n");
        return 0;
    }
    if ((nlines = readlines(lineptr, MAXPTR)) >= 0) {
        /* name of function is pointer to function */
        my_qsort((void **) lineptr, 0, nlines - 1,
              (int (*)(void *, void *)) (numeric ? numcmp : strcmp));
        printf("\n");
        if (rev == 1)
            reverse((void **) lineptr, nlines - 1);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("input too big to sort\n");
        return 1;
    }
}

/* reverse: reverse the order of pointers in lineptr[] */
void reverse(void **lineptr, int nlines) {
    void *temp;
    int i = 0;
    
    while (i < nlines) {
        temp = lineptr[i];
        lineptr[i++] = lineptr[nlines];
        lineptr[nlines--] = temp;
    }
}

#define MAXLINE 1000

/* readlines: get and put strings to lineptr[] array; return
   a count of strings, that was got */
int readlines(char **lineptr, int maxptr) {
    char *alloc(int);
    int my_getline(char *, int);
    int nlines, len;
    char line[MAXLINE], *ptr;
    
    nlines = 0;
    while ((len = my_getline(line, MAXLINE)) > 0)
        if (nlines < maxptr && (ptr = alloc(len)) != NULL) {
            line[len - 1] = '\0';  /* delete newline character */
            strcpy(ptr, line);
            lineptr[nlines++] = ptr;
        } else
            return -1;
    return nlines;
}

/* writlines: print all strings from lineptr[] array */
void writelines(char **lineptr, int maxptr) {
    while (maxptr-- > 0)
        printf("%s\n", *lineptr++);
}

/* my_qsort: do quick sorting by using (*comp)() function */
void my_qsort(void **ptr, int left, int right, 
           int (*comp) (void *, void *)) {
    void swap(void **, int, int);
    int i, last;
    
    if (left >= right)
        return;
    last = left;
    swap(ptr, left, (right + left) / 2);
    for (i = left + 1; i <= right; i++)
        if ((*comp)(ptr[i], ptr[left]) < 0)
            swap(ptr, ++last, i);
    swap(ptr, last, left);
    my_qsort(ptr, left, last - 1, comp);
    my_qsort(ptr, last + 1, right, comp);
}

/* numcmp: compare numbers, that are in strings */
int numcmp(const char *s1, const char *s2) {
    double f1 = atof(s1);
    double f2 = atof(s2);
    
    if (f1 < f2)
        return -1;
    else if (f1 > f2)
        return 1;
    else
        return 0;
}

#define SIZE_OF_FREE_MEMORY 50000
char buf[SIZE_OF_FREE_MEMORY];
char *buf_ptr = buf;

/* alloc: return pointer to free space; space == len bytes */
char *alloc(int len) {
    if ((SIZE_OF_FREE_MEMORY - (buf_ptr - buf)) >= len) {
        buf_ptr += len;
        return buf_ptr - len;
    } else
        return NULL;
}

/* my_getline: get and put string to line[] */
int my_getline(char *line, int maxlen) {
    int c;
    char *start = line;
    
    while (--maxlen > 0 && (c = getchar()) != EOF && c != '\n')
        *line++ = c;
    if (c == '\n')
        *line++ = '\n';
    *line = '\0';
    return line - start;
}

/* swap: exchange two arguments in ptr[] */
void swap(void *ptr[], int i, int j) {
    void *temp = ptr[i];
    ptr[i] = ptr[j];
    ptr[j] = temp;
}
