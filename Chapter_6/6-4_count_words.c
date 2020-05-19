
/* The program counts words whose pattenrn are in key structures in keytab[]
   array. */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100

/* structure key has name of word and his count in text */
struct key {
    char *word;
    int count;
} keytab[] = {
    { "auto",       0},
    { "break",      0},
    { "case",       0},
    { "char",       0},
    { "const",      0},
    { "continue",   0},
    { "default",    0},
    /* ... */
    { "unsigned",   0},
    { "void",       0},
    { "volatile",   0},
    { "while",      0}
};

int get_word(char *, int);
int binsearch(char *, struct key *, int);

/* count of key structures in keytab[] array */
#define NKEY (sizeof keytab / sizeof keytab[0])

int main(void) {
    int n;
    char word[MAXWORD];
    
    while (get_word(word, MAXWORD) != EOF)
        if (isalpha(*word))
            if ((n = binsearch(word, keytab, NKEY)) >= 0)
                (*(keytab + n)).count++;
    for (n = 0; n < NKEY; n++) 
        if ((*(keytab + n)).count > 0)
            printf("%4d %s\n", keytab[n].count, keytab[n].word);
    return 0;
}
/* binsearch: search sorted tab[] array for special word */ 
int binsearch(char *word, struct key *tab, int n) {
    int cond;
    int low, high, mid;
    
    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if ((cond = strcmp(word, tab[mid].word)) < 0)
            high = mid - 1;
        else if (cond > 0)
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}

/* get_word: get word and put it into word[] array; return its
   first symbol */
int get_word(char *word, int maxword) {
    int c, getch(void);
    void ungetch(int);
    char *w = word;
    
    while (isspace(c = getch()))
        ;
    if (c != EOF)
        *w++ = c;
    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }
    for (; --maxword > 0; w++)
        if (!isalnum(*w = getch())) {
            ungetch(*w);
            break;
        }
    *w = '\0';
    return (*word);
}

#define MAXBUF 10

int buf[MAXBUF];
int bp = 0;

/* getch: return character from buffer, or use getchar() */
int getch(void) {
    return (bp == 0 ? getchar() : buf[--bp]);
}

/* ungetch: return character to buffer */
void ungetch(int c) {
    if (bp < MAXBUF)
        buf[bp++] = c;
    else
        printf("error: too many characters!\n");
}

