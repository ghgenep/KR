
/* Exercise 5.16
   The program uses my_my_qsort() function that can take following 
   keys:
   -n       sort an array not by alphabet, but by numeric value
   -r       sort an array in the reverse order 
   -f       upper and lower character are the same(a == A, ...)
   -d       sort by comparing only letters, digits and spaces */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>  /* for atof() function */

int numeric = 0;        /* -n option */
int rev = 0;            /* -r option */
int up_low_equal = 0;   /* -f option */
int dir_order = 0;      /* -d option */

#define MAXPTR 5000
char *lineptr[MAXPTR];   /* an array of pointer to input starings */

int readlines(char **, int);
void writelines(char **, int);
void my_qsort(void **, int, int);
int my_strcmp(char *, char *);

int main(int argc, char **argv) {
    void reverse(void **, int);
    int nlines;             /* count of lines read */
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
                case 'f':
                    up_low_equal = 1;
                    break;
                case 'd':
                    dir_order = 1;
                    break;
                default :
                    printf("error: illegal otpion \'%c\'\n", c);
                    argc = -1;
                    break;
            }
    if (argc != 0) {
        printf("Usage: program_name -n -r -f -d\n");
        return 0;
    }
    if ((nlines = readlines(lineptr, MAXPTR)) >= 0) {
        /* name of function is pointer to function */
        my_qsort((void **) lineptr, 0, nlines -1);
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

/* my_qsort: do quick sorting by using mode of comparing */
void my_qsort(void **ptr, int left, int right) {
    void swap(void **, int, int);
    int i, last;
    
    if (left >= right)
        return;
    last = left;
    swap(ptr, left, (right + left) / 2);
    for (i = left + 1; i <= right; i++)
        if (my_strcmp(ptr[i], ptr[left]) < 0)
            swap(ptr, ++last, i);
    swap(ptr, last, left);
    my_qsort(ptr, left, last - 1);
    my_qsort(ptr, last + 1, right);
}
 
/* my_strcmp: compare two strings */
int my_strcmp(char *s1, char *s2) {
    int isdns(int);  /* is digit or number or space */
    void gotolower(char *, char *);
    int i;
    char t1[MAXLINE], t2[MAXLINE];
    
    /**** -f option ****/
    if (up_low_equal) {
        /* copy s1 and s2 to t1 and t2 in lower case */
        gotolower(s1, t1);
        gotolower(s2, t2);
        s1 = t1;
        s2 = t2;
    }    
    
    /**** -n option ****/
    if (numeric) { 
        double f1 = atof(s1);
        double f2 = atof(s2);
    
        if (f1 < f2)
            return -1;
        else if (f1 > f2)
            return 1;
        else
            return 0;
    } /**** -d option ****/
    else if (dir_order) {        
        while (*s1 == *s2 && *s1 != '\0')
            s1++, s2++;
        if (*s1 == '\0') {
            if (*s2 == '\0')
                return 0;
            else
                return 1;
        } 
        else if (*s2 == '\0') {
            return 1;
        }
        else if (!isdns(*s1)) {
            if (!isdns(*s2))
                return 0;
            else
                return -1;
        }
        else if (!isdns(*s2))
            return 1;        
        else
            return *s1 - *s2;
    } /**** no options ****/ 
    else 
        return strcmp(s1, s2);
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

/* isdns: return not 0, if c is digit, or letter, or space */
int isdns(int c) {
    return (isdigit(c) || isalpha(c) || c == ' ');
}

/* gotolower: copy string in lower case */
void gotolower(char *from, char *to) {
    while (*to++ = tolower(*from++))
        ;
}
