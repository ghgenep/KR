
/* The program counts words whose pattenrn are in key structures in keytab[]
   array. This version uses pointers to structures. */

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
struct key *binsearch(char *, struct key *, int);

/* count of key structures in keytab[] array */
#define NKEY (sizeof keytab / sizeof keytab[0])

int main(void) {
    struct key *n;
    char word[MAXWORD];
    
    while (get_word(word, MAXWORD) != EOF)
        if (isalpha(*word))
            if ((n = binsearch(word, keytab, NKEY)) != NULL)
                n->count++;
    for (n = keytab; n < (keytab + NKEY); n++) 
        if (n->count > 0)
            printf("%4d %s\n", n->count, n->word);
    return 0;
}

/* binsearch: search sorted tab[] array for special word */ 
struct key *binsearch(char *word, struct key *tab, int n) {
    int cond;
    struct key *low = &tab[0];
    struct key *high = &tab[n];
    struct key *mid;
    
    while (low < high) {
        mid = low + (high - low) / 2;
	/* high - low    -> give count of elements between them */
        if ((cond = strcmp(word, mid->word)) < 0)
            high = mid;
        else if (cond > 0)
            low = mid + 1;
        else
            return mid;
    }
    return NULL;
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

