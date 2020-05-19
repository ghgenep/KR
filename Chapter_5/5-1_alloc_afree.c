
/* The program uses alloc() and afree() functions, that works
   with memory. */

#include <stdio.h>
#define BUFSIZE 10000

char alloc_buf[BUFSIZE]; /* memory buffer for alloc() and afree() */
char *alloc_p = alloc_buf;  /* point to next free memory block */

/* alloc: return pointer to a next n bytes of free memory if 
   it's possible */
char *alloc(int n) {
    if ((BUFSIZE - (alloc_p - alloc_buf)) >= n) {
        /* alloc_p - alloc_buf == count of used bytes */
        alloc_p += n;
        return (alloc_p - n);
    }
    else
        return NULL;    /* it's not possible */
}

/* afree: free a memory, starting from p */
void afree(char *p) {
    if (p >= alloc_buf && p < (alloc_buf + BUFSIZE)) 
        alloc_p = p;   
}

/* strlen: return the length of the string */
int strlen(char *s) {
    int n;

    for (n = 0; *s != '\0'; s++)
        n++;
        
    return n;
}

/* P1 and P2 are counts of needed bytes */
#ifndef P1
 #define P1 5
#endif
#ifndef P2
 #define P2 4
#endif

int main(void) {
    int i;
    char *p1, *p2;

    printf("\"%s\" %d\n", alloc_buf, strlen(alloc_buf));
    
    /* output: "" 0 */
    p1 = alloc(P1);               /* get pointer */
    for (i = 0; i < P1; i++)
        *(p1 + i) = '1';          /* fill with '1' character */
    printf("\"%s\" %d\n", alloc_buf, strlen(alloc_buf)); 
    /* output: "11111" 5 */
    
    p2 = alloc(P2);
    for (i = 0; i < P2; i++)
        *(p2 + i) = '2';
    printf("\"%s\" %d\n", alloc_buf, strlen(alloc_buf));
    /* output: "111112222" 9 */
    
    afree(p2);
    *p2 = '\0';
    printf("\"%s\" %d\n", alloc_buf, strlen(alloc_buf));
    /* output: "11111" 5 */
    
    afree(p1);
    *p1 = '\0';
    printf("\"%s\" %d\n", alloc_buf, strlen(alloc_buf));
    /* output: "" 0 */

    return 0;
}

