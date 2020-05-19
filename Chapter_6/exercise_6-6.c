
/* Exercise 6.6
   The program uses structures to make a hash table. The undef()
   function deletes name from table. Imitation of #define with
   no arguments. Usage: #define name [value] [\] */
                       
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

struct nlist {  /* record in a hash table */
    struct nlist *next;
    char *name;
    char *defn;
};

unsigned int hash(char *);
struct nlist *lookup(char *);
char *my_strdup(char *);
struct nlist *install(char *, char *);
void undef(char *);
int getword(char *, int);
int getch(void);
int get_definition(char *, char *);
void ungetch(int);

#define HASHSIZE 101
static struct nlist *hashtab[HASHSIZE];   /* table of pointers */

#define MAXWORD 100

int main(void) {
    int n, c;
    char word[MAXWORD];
    struct nlist *p;
    int in = '\0';

    while ((c = getch()) != EOF) {
		if (isspace(c)) {
		    printf("%c", c);
		    continue;
		}
		ungetch(c);    /* not space character */
		if (getword(word, MAXWORD) != EOF) {
		    if (isalpha(*word) || *word == '_') {
				/* if the word has been used in #define directive,
				   print definition of constant */
				if ((p = lookup(word)) != NULL) 
				    printf("%s", p->defn); 
				else
				    printf("%s", word);
		    } else if (*word == '/') {  /* if comment, skip comment */
				printf("/");
				if ((c = getch()) == '*') {
				    printf("*");
				    while ((c = getch()) != EOF) {
					printf("%c", c);
					if (c == '*') 
					    if ((c = getch()) == '/') {
						printf("/");
						break;
					    } else
						ungetch(c);
				    }
				} else if (c == '/') {
				    printf("/");
				    while ((c = getch()) != EOF) {
					printf("%c", c);
					if (c == '\n') 
					    break;
				    }
				}	    
		    } else if (*word == '#') {
				char name[MAXWORD], defn[MAXWORD * 10];
				int out; /* keep return value of get_definition() function */
				/* possible return values:
				   - -3, if it's not #define directive;
				   - -2, if uncorrect name in #define directive;
				   - EOF, if EOF have been occured;
				   - 0, no name, no value of the name;
				   - 1, if only the name has got;
				   - 2, if both name and the value of name have got.
				   The #define constant in end of file are skipped.
				*/

				if ((out = get_definition(name, defn)) == 2)
				    install(name, defn);
				else if (out == 1)
				    install(name, "");
				else if (out == EOF) {
				    /* out == EOF when: it's last line with empty # directive,
				       or it's #define directive in last line; whatever,
				       they are skipped */
				    return 0;
				} else if (out == -2) {
				    printf("\n### error: uncurrect name in definition\n");
				    return 0;
				} else if (out == -3)
				    /* now, defn[] contain a name of directive: if, include etc. */
				    printf("#%s", defn);
				else if (out == 0) {
				    printf("\n### error: no name, no value of the name in #define directive\n");
				    return 0;
				}
		    } else if (*word == '\"' || *word == '\'') {
				in = *word;
				printf("%s", word);
				while ((c = getch()) != EOF) {
				    printf("%c", c);
				    if (c == '\\') {
					if ((c = getch()) != EOF)
					    printf("%c", c);
				    } else if (c == in)
					break;
				}
		    } else
			printf("%s", word);
		}
    }
    return 0;
}

/* get_definition: get name and value of the name in #define directive 
   Possible return values:
   - -3, if it's not #define directive;
   - -2, if uncorrect name in #define directive;
   - EOF, if EOF have been occured;
   - 0, no name, no value of the name;
   - 1, if only the name has got;
   - 2, if both name and the value of name have got.
   The #define constant in end of file are skipped. */
int get_definition(char *name, char *defn) {
    char *p = defn;
    int c;

    *p = '\0';

    if (getword(defn, MAXWORD) == EOF)
		return EOF;  /* last # in last line with no directive; skip */
    if (strcmp(defn, "define") != 0)
		return -3;   /* it's not the #define directive; print it */
    while ((c = getch()) != EOF) {   /* find first letter of the name */
		if (isspace(c))  /* skip spaces */
		    if (c == '\n')
				return 0;
		    else
				continue;
		else if (!isalpha(c) && c != '_') {
		    if (c == '\\')
				if ((c = getch()) == '\n')
			    	continue;  /* multiline constant */
		    return -2;
		} else
		    break;
    }
    if (c == EOF)
		return 0;  /* no name, no value of the name in directive */
    ungetch(c);
    getword(name, MAXWORD);  /* take the name into name[] array */

    /* get value of the name */
    while (isspace(c = getch()))
		if (c == '\n')
	    	return 1;  /* only name, no value of the name(default: "") */
    if (c == EOF)
		return EOF;  /* last line, with correct #define directive; skip */
    do {
		if (c == '\\')
		    if ((c = getch()) == '\n')  /* if multiline constant */   
				*defn++ = '\n';
		    else {
				*defn++ = '\\';         /* just '\\' character */
				ungetch(c);
		    } else if (c == '\n')        /* the end of multi-line constant */
		    	break;	
		else
		    *defn++ = c;
    } while ((c = getch()) != EOF);
    	*defn = '\0';
    if (c == EOF)  /* last line, with correct #define directive; skip */
		return EOF;
    if (*p != '\0')
		return 2;
    else
		return 1;
}

/* getword: get word from input stream; return first symbol */
int getword(char *word, int maxword) {
    int c, c2;
    char *w;

    w = word;
    c = getch();
    if (c != EOF)
	*w++ = c;
    if (!isalpha(c) && c != '_') {
		*w = '\0';
		return c;
    }
    for (maxword--; --maxword > 0; w++)
		if (!isalnum(*w = getch()) && *w != '_') {
		    ungetch(*w);
		    break;
		}
    *w = '\0';
    return *word;
}

/* hash: take string and return its hash-index */
unsigned int hash(char *s) {
    unsigned int hashval;

    for (hashval = 0; *s != '\0'; s++)
	// hashval = *s + 31 * hashval;
	hashval = *s + hashval;
    return hashval % HASHSIZE;
    /* we use HASHSIZE, not HASHSIZE - 1, because
       we need a number in [0-100] range */
}

/* lookup: search hash table for s string */
struct nlist *lookup(char *s) {
    struct nlist *np;

    /* look over strings with same hash-index */
    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
	if (strcmp(s, np->name) == 0)
	    return np;
    return NULL;
}

/* my_strdup: alloc spave for string s */
char *my_strdup(char *s) {
    char *out;

    out = (char *) malloc(strlen(s) + 1);
    if (out != NULL)
	strcpy(out, s);
    return out;
}

/* install: add new name into hash table */
struct nlist *install(char *name, char *defn) {
    struct nlist *np;
    unsigned int hashval;

    if ((np = lookup(name)) == NULL) {  /* there is no name in hash table */
		np = (struct nlist *) malloc(sizeof(*np));
		if (np == NULL || (np->name = my_strdup(name)) == NULL)
		    return NULL;
		hashval = hash(name);	       /* may be other names with 
						  same hashval */
		np->next = hashtab[hashval];   /* in first */
		hashtab[hashval] = np;         /* in second, not vice versa */
    } else
		free((void *) np->defn);   /* redefine name */
    if ((np->defn = my_strdup(defn)) == NULL)
		return NULL;
    return np;
}

/* undef: delete name from hash table */
void undef(char *name) {
    struct nlist *p;
    unsigned int hashval;

    if ((p = lookup(name)) != NULL) {
		if (p == hashtab[hashval = hash(name)])
		    hashtab[hashval] = p->next;
		else {
		    while (hashtab[hashval]->next != p)
			hashval++;
		    hashtab[hashval]->next = p->next;
		}
    }
}

#define BUFSIZE 100
char buf[BUFSIZE];
int bp = 0;

int getch(void) {
    return (bp > 0 ? buf[--bp] : getchar());
}

void ungetch(int c) {
    if (bp < BUFSIZE)
	buf[bp++] = c;
    else
	printf("error: buffer is full!\n");
}

