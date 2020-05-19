
/* Exercise 6.1
   The program counts words whose pattenrn are in key structures in keytab[]
   array. The program ignores '_' character, strings, comments, and 
   preprocessor directives. */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100	/* max length of input word */

struct key {
    char *word;
    int count;
} keytab[] = {
    /* structures must be sorted! */
    { "break", 0},
    { "char", 0},
    { "continue", 0},
    { "else", 0},
    { "for", 0},
    { "int", 0},
    { "main", 0},
    { "struct", 0},
    { "void", 0}
    /* ... */ 
};

void ungetch(int);
int getch(void);
int skip_unwanted(int);
int get_word(char *, int);
int binsearch(char *, struct key *, int);

/* to get number of structures in keytab[] array, use sizeof: */
#define NKEY (sizeof keytab / sizeof keytab[0])

int main(void) {
    int n;
    char word[MAXWORD];
    
    while (get_word(word, MAXWORD) != EOF)
	/* word must start with 'a-z', 'A-Z', or '_' */
        if (isalpha(*word) || *word == '_')
            if ((n = binsearch(word, keytab, NKEY)) >= 0)
                (*(keytab + n)).count++;
    for (n = 0; n < NKEY; n++) 
        if ((*(keytab + n)).count > 0)
            printf("%4d %s\n", keytab[n].count, keytab[n].word);
    return 0;
}

/* skip_unwanted: skip      strings, comments, and preprocessor directives;
   return new character */
int skip_unwanted(int c) {
    int skip_till_c(int);

    if (c == EOF)
        return c;
    else if (c == '\"' || c == '\'' || c == '#' || c == '/') {
        if (c == '\"') {
	    if ((c = skip_till_c('\"')) == EOF)
		return EOF;
	} else if (c == '\'') {
	    if ((c = skip_till_c('\'')) == EOF)
		return EOF;
	} else if (c == '#') {
	    while ((c = getch()) != '\n' && c != EOF)
		if (c == '\\')
		    if ((c = getch()) == '\n')
			continue;
		    else
			ungetch(c);
	} else {
	    if ((c = getch()) == '/') {
		while ((c = getch()) != '\n' && c != EOF)
		    ;
	    }
	    else if (c == '*') {
		while ((c = getch()) != EOF)
		    if (c == '*')
			if ((c = getch()) == '/')
			    break;
			else
			    ungetch(c);
	    }
	    else 
		return c;
	}
	/* skip spaces */
	while (isspace(c = getch()))
	    ;
	if (c == '\"' || c == '\'' || c == '#' || c == '/')
	    return skip_unwanted(c);
	else
	    return c;
    }
    else
        return c;
}

/* skip_till_c: skip till we have ch character */
int skip_till_c(int ch) {
    int c;

    while ((c = getch()) != ch && c != EOF)
	if (c == '\\') getch();
	/* if we have '\\' character, we must skip a character
	   that go after, because it may be '\"' or '\'' characters */
    return c;
}

/* get_word: get next word and put it to word[] array;
   return first array of the word, or EOF */
int get_word(char *word, int maxword) {
    int c, c2, getch(void);
    void ungetch(int);
    char *w = word;
    
    while (isspace(c = getch()))
        ;
    if (c != EOF)
        *w++ = c;
    if (!isalpha(c) && c != '_') {
	/* if c is '\"', or '\'', or '#', or '/'(comment) -> check it */
        c2 = skip_unwanted(c);
	/* if we take back EOF, exit */
        if (c2 == EOF) {
            *word = '\0';
	    return EOF;
        }
	/* if c != c2, we must change *word with new character */
        if (c != c2)
            *word = c2;
        if (!isalpha(c2) && c2 != '_') {
            *w = '\0';
            return c2;
        }
    }
    for (--maxword; --maxword > 0; w++)
        if (!isalnum(*w = getch()) && *w != '_') {
            ungetch(*w);
            break;
        }
    *w = '\0';
    return (*word);
}

/* binsearch: search tab[] array of structures for specific word;
   return index, or -1; function uses sorted array */
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

#define MAXBUF 10
int buf[MAXBUF];
int bp = 0;

/* getch: get character from buf[]; otherwise - use getchar() */
int getch(void) {
    return (bp == 0 ? getchar() : buf[--bp]);
}

/* ungetch: take c to buf[] buffer */
void ungetch(int c) {
    if (bp < MAXBUF)
        buf[bp++] = c;
    else
        printf("error: too many characters!\n");
}
