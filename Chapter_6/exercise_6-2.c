
/* Exercise 6.2
   The program uses structures to make tree of word from input. Then
   word will be printed with their counts. Must be one argument, that
   mean a number of significant characters. Printed words will be grouped
   by that significant characters; other characters are unnecessary 
   and don't consider. */

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* structure is node in tree of words */
struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

#define MAXWORD 100
struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);
int n = 0;	/* count of significant characters */

int main(int argc, char **argv) {
    struct tnode *root;
    char word[MAXWORD];

    /* get argument */
    if (argc != 2) {
    	printf("error: usage: ./a.out n\nn is count significant characters.\n");
    	return 0;
    } else {
    	n = atoi(*(argv + 1));
    	if (errno == ERANGE) {
    	    printf("error: argument of program is too big or small.\n");
    	    return 0;
    	}
    }

    root = NULL;
    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]) || word[0] == '_')
            root = addtree(root, word);
    treeprint(root);   /* print all tree in alphabet order */
    return 0;
}

struct tnode *talloc(void);
char *my_strdup(char *);

/* addtree: add new node in the tree or increase count of word by 1 */
struct tnode *addtree(struct tnode *p, char *w) {
    int cond;

    if (p == NULL) {
	if (strlen(w) < n)
	    return p;
        p = talloc();
        p->word = my_strdup(w);
        p->count = 1;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0)
        p->count++;
    else if (cond < 0)
        p->left = addtree(p->left, w);
        /* if p->left is NULL, new node will be created and his 
           pointer will be returned;
           if p->left exist, repeat from the beginnig of function
           with p->left argument */
    else
        p->right = addtree(p->right, w);
    return p;   /* if p in beginning of function is NULL, new p node
                   will be created */
}

/* last word that was printed */
char last_word[MAXWORD] = "";

/* treeprint: print all tree in alphabet order */
void treeprint(struct tnode *p) {
    if (p != NULL) {
        treeprint(p->left);  /* go to the leftest node */

	/* print word and newline, if it needs */
	if (strncmp(p->word, last_word, n) != 0)
	    printf("\n");
        printf("%4d %s\n", p->count, p->word);

	strcpy(last_word, p->word);
        treeprint(p->right);
    }
}

/* talloc: return pointer to new struct tnode */
struct tnode *talloc(void) {
    return (struct tnode *) malloc(sizeof(struct tnode));
}

/* my_strdup: return pointer to string, where s word has been written */
char *my_strdup(char *s) {
    char *p;

    p = (char *) malloc(strlen(s) + 1);
    if (p != NULL)
        strcpy(p, s);
    return p;
}

#define BUFSIZE 10
int buf[BUFSIZE];
int bp = 0;

/* getch: return character from the buffer, or use getchar() */
int getch(void) {
    return (bp > 0 ? buf[--bp] : getchar()); 
}

/* ungetch: return c character to the buffer */
void ungetch(int c) {
    if (bp < BUFSIZE)
        buf[bp++] = c;
    else
        printf("error: buffer is full!\n");
}

int skip_unwanted(int c) {
    int skip_till_c(int);

    if (c == EOF)
        return c;
    else if (c == '\"' || c == '\'' || c == '#' || c == '/') {
	/* skip it */
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
	    } else if (c == '*') {
		while ((c = getch()) != EOF)
		    if (c == '*')
			if ((c = getch()) == '/')
			    break;
			else
			    ungetch(c);
	    } else 
		return c;
	}
	/* skip spaces */
	while (isspace(c = getch()))
	    ;
	/* now c is new character, after comment, string, ... */
	if (c == '\"' || c == '\'' || c == '#' || c == '/')
	    return skip_unwanted(c);
	else
	    return c;
    } else /* if c is not start of whatever we must skip */
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

/* getword: get next word and put it to word[] array;
   return first array of the word, or EOF */
int getword(char *word, int maxword) {
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
            return c;
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

