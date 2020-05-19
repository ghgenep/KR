
/* The program uses structures to make tree of word from input. Then
   word will be printed with their counts. */

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

int main(void) {
    struct tnode *root;
    char word[MAXWORD];

    root = NULL;
    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
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

/* treeprint: print all tree in alphabet order */
void treeprint(struct tnode *p) {
    if (p != NULL) {
        treeprint(p->left);  /* go to the leftest node */
        printf("%4d %s\n", p->count, p->word);
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

/* getword: return first character of new word; write new word 
   to w[] array */
int getword(char *w, int lim) {
    char *word  = w;
    int c;

    while (isspace(c = getch()))
        ;
    if (c != EOF)
        *w++ = c;
    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }
    for (--lim; --lim > 0; w++) 
        if (!isalnum(*w = getch())) {
            ungetch(*w);
            break;
        }
    *w = '\0';
    return *word;
}

