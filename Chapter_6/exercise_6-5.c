
/* Exercise 6.5
   The program uses structures to make a hash table. New undef()
   function deletes name from table. */

#include <stdio.h>
#include <string.h>
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
void print_hashtab(struct nlist **);

#define HASHSIZE 101
static struct nlist *hashtab[HASHSIZE];   /* table of pointers */

int main(void) {
    install ("ON", "3");
    install ("NO", "1");
    install ("YES", "2");
    print_hashtab(hashtab);
    undef("NO");
    print_hashtab(hashtab);
    return 0;
}

/* print_hashtab: print all hashtab */
void print_hashtab(struct nlist **tab) {
    int i;

    for (i = 0; i < HASHSIZE; i++) {
    	if (tab[i] == NULL)
    	    continue;
    	printf("name = \"%s\" defn = \"%s\"\n", tab[i]->name, tab[i]->defn);
    	if (tab[i]->next != NULL) {
    	    struct nlist *p = tab[i]->next;
    	    do {
    		  printf("\tname = \"%s\" defn = \"%s\"\n", p->name, p->defn);
    		  p = p->next;
    	    } while (p != NULL);
    	}
    }
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

