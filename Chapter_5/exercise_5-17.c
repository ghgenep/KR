
/* Exercise 5.17
   The program uses my_my_qsort() function that can take following 
   keys:
   -n       sort an array not by alphabet, but by numeric value
   -r       sort an array in the reverse order 
   -f       upper and lower character are the same(a == A, ...)
   -d       sort by comparing only letters, digits and spaces */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>  /* for atof() function */

#define MAXLINE 1000
#define MAXPTR 5000
char *lineptr[MAXPTR];   /* an array of pointer to input starings */

int readlines(char **, int);
void writelines(char **, int);
void my_qsort(char **, int, int);
int my_strcmp(char *, char *);
char *get_field(char *, int);
char *save_field(char *to, char *field, int maxlines);


int field = 1;
int field_p = 1;
int field_f = 0;
int field_num = 3;

#define FIELD_COUNT 4
int field_arr[FIELD_COUNT] = {
    0, 2, 3, 4 };

int main(int argc, char **argv) {
    void reverse(void **, int);
    int nlines;             /* count of lines read */
    int c;
    int left;
    
   // if (get_arguments(argc, argv) != 0) {
   //     printf("Usage: program_name -n -r -f -d\n");
   //     return 0;
   // }
    if ((nlines = readlines(lineptr, MAXPTR)) >= 0) {
        if (field == 0)
            my_qsort(lineptr, 0, nlines - 1);
        else {
            field_f = 1;
            my_qsort(lineptr, 0, nlines - 1);
           field_p++;
           field_f = 0;
            if (field_p != field_num) {
                int i = 0;
                field_p--;
                while (field_p < field_num) {
                    while (i < nlines)
                        if (search_equal(i, &left, MAXPTR) != 0) {
                            my_qsort(lineptr, i, left);
                            i = left + 1;
                        } else
                            i++;
                    field_p++;
                    i = 0;
                }
            }
        }
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("input too big to sort\n");
        return 1;
    }
}

/* my_strcmp: compare two strings */
int my_strcmp(char *s1, char *s2) {
    int i;
    char t1[MAXLINE], t2[MAXLINE];
    
    if (field) {
        if (field_f == 0)
            field_p++;
        save_field(t1, get_field(s1, field_arr[field_p]), MAXLINE - 1);
        save_field(t2, get_field(s2, field_arr[field_p]), MAXLINE - 1);
        if (field_f == 0)
            field_p--;
        return strcmp(t1, t2);
    } else 
        return strcmp(s1, s2);
}

char *get_field(char *s, int field_num) {
        if (s == NULL)
            return NULL;
        while (field_num != 1) {
            while (isspace(*s))
                s++;
            while (!isspace(*s)) {
                if (*s == '\0') {
                    printf("error: \'\\0\' is occured!\n");
                    return NULL;
                }
                s++;
            }
            if (isspace(*s))
                field_num--;
        }
        while (isspace(*s))
            s++;
        return (*s == '\0' ? NULL : s);
}

char *save_field(char *to, char *field, int maxlines) {
    char *p = to;
    
    if (field == NULL)
        return NULL;
    while (--maxlines > 0 && *field != '\0' && !isspace(*field))
        *to++ = *field++;
    if (maxlines == 0) {
        printf("error2: too many characters\n");
        return NULL;
    }
    *to = '\0';
    return p;
}

int search_equal(int i, int *left, int maxlines) {
    char s1[MAXLINE];
    char s2[MAXLINE];
    int right = i;
    *left = right;
    
    save_field(s1, get_field(lineptr[i], field_arr[field_p]), MAXLINE - 1);
    i++;
    while (i < maxlines) {
        if (save_field(s2, get_field(lineptr[i], field_arr[field_p]), 
                    MAXLINE - 1) == NULL)
            break;
        if (strcmp(s1, s2) == 0)
            i++;
        else
            break;
    }
    if (--i != right) {
        *left = i;
        return (i - right + 1);
    } else
        return 0;    
}
 


void my_qsort(char **ptr, int left, int right) {
    void swap(char **, int, int);
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
    printf("\n");
    while (maxptr-- > 0)
        printf("%s\n", *lineptr++);
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
void swap(char **ptr, int i, int j) {
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
