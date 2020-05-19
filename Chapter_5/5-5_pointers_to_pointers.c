
/* The program uses functions that use pointers to pointers. */

#include <stdio.h>
#include <string.h>

#define MAXLINE 5000

int readlines(char **, int);
void writelines(char **, int);
void qsort(char **, int, int);

int main(void) {
    /* an array of pointer to characters */
    char *lineptr[MAXLINE] = {};
    int nlines;     /* count of this pointers */

    if ((nlines = readlines(lineptr, MAXLINE)) >= 0) {
        qsort(lineptr, 0, nlines - 1);
        printf("\n");
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
}

#define MAXLEN 1000   /* max length of string */
int my_getline(char *, int);
char *alloc(int);

/* readlines: get strings and put them to lineptr[] */
int readlines(char *lineptr[], int maxlines) {
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len = my_getline(line, MAXLEN)) > 0)
            if (nlines >= maxlines || (p = alloc(len)) == NULL)
                return -1;
            else {
                line[len - 1] = '\0';  /* delete '\n' */
                strcpy(p, line);
                lineptr[nlines++] = p;
            }
    return nlines;  /* return count of strings read */
}

/* writelenes: print strings from lineptr[] */
void writelines(char *lineptr[], int nlines) {
    while (nlines-- > 0)
        printf("%s\n", *lineptr++);
}

void swap(char **, int, int);

/* qsort: sort v[left]...v[right] in asceding order */
void qsort(char *v[], int left, int right) {
    int i, last;
    
    /* do nothing, if array has less than 2 element */
    if (left >= right)  
        return;
    last = left;
    swap(v, left, (left + right) / 2);
    
    for (i = left + 1; i <= right; i++)
        if (strcmp(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    qsort(v, left, last - 1);
    qsort(v, last + 1, right);
}

/* swap: exchange v[i] and v[j] */
void swap(char *v[], int i, int j) {
    char *temp;
    
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
/* my_getline: get string and return its length */
int my_getline(char *s, int maxline) {
    int c;
    char *t = s;
    
    while (--maxline > 0 && (c = getchar()) != EOF && c != '\n')
        *s++ = c;
    if (c == '\n')
        *s++ = '\n';
    *s = '\0';
    return s - t;
}

#define MEMORY_SIZE 10000
char memory[MEMORY_SIZE];
char *free_memory = memory;

/* alloc: return pointer to free memory; its size == len */
char *alloc(int len) {
    if (len <= (MEMORY_SIZE - (free_memory - memory))) {
        free_memory += len;
        return (free_memory - len);  /* old free_memory */
    } else
        return 0;  /* there is no free space */
}
