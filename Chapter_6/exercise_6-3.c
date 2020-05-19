
/* Exercise 6.3
   The program uses structures to make tree of word from input. Then
   word will be printed with their counts and numbers of line, where
   they are in. Words like a, an, on etc. will be deleted(deleting of
   words by skipping them). */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* structure is node in tree of words */
struct tnode {
    char *word;
    int count;
    char *lines;
    char add_count;  /* number of how many times was alloced
			MAX_LINES bytes */
    struct tnode *left;
    struct tnode *right;
};

/* words that must be skipped */
char *skip_words[] = {
    "on", "in", "up", "down", "to", "from", "upon", "a", "an",
    "the", "of"
};
/* get number of words in skip_words[] array */
int max_words = (sizeof skip_words / sizeof skip_words[0]);

#define MAX_LINES 100  /* max length of string for numbers of line */
int current_line = 1;

#define MAXWORD 100
struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);
char *addline(struct tnode *,char *);
char *itoa(int, char *);
int is_skip_word(char *);

int main(void) {
    struct tnode *root;
    char word[MAXWORD];

    root = NULL;
    while (getword(word, MAXWORD) != EOF) {
	if (is_skip_word(word))  /* if word must be skipped */
	    continue;
        if (isalpha(word[0]))
            root = addtree(root, word);
    }
    treeprint(root);   /* print all tree in alphabet order */
    return 0;
}

struct tnode *talloc(void);

/* addtree: add new node in the tree or increase count of word by 1 */
struct tnode *addtree(struct tnode *p, char *w) {
    int cond;
    char array[MAXWORD];
    char *line = array;

    if (p == NULL) {
    	if ((p = talloc()) == NULL) {
    	    printf("error: in talloc() function.\n");
    	    exit(0);
    	}
    	if ((p->lines = (char *) malloc(MAX_LINES)) == NULL) {
    	    printf("error: in malloc() function.\n");
    	    exit(0);
    	}
    	p->lines = itoa(current_line, p->lines);
    	strcat(p->lines, ", ");  /* add ", " to end of p->lines */
            if ((p->word = (char *) malloc(strlen(w) + 1)) == NULL) {
    	    printf("error: in my_strdup() function.\n");
    	    exit(0);
    	}
    	strcpy(p->word, w);
    	p->count = 1;
    	p->add_count = 1;
            p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0) {
    	line = itoa(current_line, line);
    	strcat(line, ", ");
    	if (strstr(p->lines, line) == NULL)
    	    /* strstr: search string for first occurrence of 
    	       sequence of characters */
    	    /* add string with number to end of p->lines string */
    	    if ((p->lines = addline(p, line)) == NULL) {
    		printf("error: in addline() function.\n");
    		exit(0);
    	    }
            p->count++;
    } else if (cond < 0)
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
        *(strrchr(p->lines, ',')) = '\0';
        printf("%4d %s --> %s\n", p->count, p->word, p->lines);
        treeprint(p->right);
    }
}

/* talloc: return pointer to new struct tnode */
struct tnode *talloc(void) {
    return (struct tnode *) malloc(sizeof(struct tnode));
}

/* addline: add string to p->lines; if it need - alloc more 
   free space for it; return pointer to string */
char *addline(struct tnode *p, char *word) {
    if (strlen(p->lines) + strlen(word) + 1 > MAX_LINES * p->add_count) {
    	char *new_p = realloc(p->lines, (p->add_count + 1) * MAX_LINES); 
    	if (new_p == NULL)
    	    return NULL;
    	p->add_count++;   /* number of how many times realloc() function
    			     was called */
    	p->lines = new_p;
    	/* check lenght of p->lines */
    }
    strcat(p->lines, word);
    return p->lines;
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
	if (c == '\n')
	    current_line++;
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

char *itoa(int i, char *out) {
    static next = 0;
    static max_next = 1;

    if (i < 0) {
    	out[next++] = '-';
    	i = -i;
    	max_next++;
    }
    if (i / 10 != 0) {
    	max_next++;
    	itoa(i / 10, out);
    }
    out[next++] = i % 10 + '0';
    out[next] = '\0';
    if (max_next == next) {
    	next = 0;
    	max_next = 1;
    }
    return out;
}

int is_skip_word(char *word) {
    int i;

    for (i = 0; i < max_words; i++)
    	if (strcmp(word, skip_words[i]) == 0)
    	    return 1;
    return 0;
}

