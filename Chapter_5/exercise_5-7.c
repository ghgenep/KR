
/* Exercise 5.7 
   The program uses functions that use pointers to pointers. 
   The readlines() function works without using alloc() function. */

#include <stdio.h>
#include <string.h>

#define MAXLINE 5000
#define MEMORY_SIZE 10000

int readlines(char **, int, char *, int);
void writelines(char **, int);
void qsort(char **, int, int);

int main(void) {
    char *lineptr[MAXLINE] = {};    /* an array of pointer to characters */
    int nlines;                     /* count of this pointers */
    char memory[MEMORY_SIZE] = {};  /* free memory for strings */
    
    if ((nlines = readlines(lineptr, MAXLINE, memory, MEMORY_SIZE)) >= 0) {
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

/* readlines: get strings and put them to lineptr[] */
int readlines(char *lineptr[], int maxlines, char *memory, int maxsize) {
    int len, nlines;
    char line[MAXLEN];

    nlines = 0;
    while ((len = my_getline(line, MAXLEN)) > 0)
            /* maxsize variable contains max number of characters */
            if (nlines >= maxlines || (maxsize -= len) < 0)
                return -1;
            else {
                line[len - 1] = '\0';  /* delete '\n' */
                strcpy(memory, line);
                lineptr[nlines++] = memory;
                memory += len;
                /* now, memory is pointer to next free space */
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
