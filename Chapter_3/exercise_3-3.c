    
/* Exercise 3.3
   The program uses expand(s1, s2) that expands shorthand notations 
   like a-z in the string s1 into the equivalent complete list abc...xyz 
   in s2 */

#include <stdio.h>
#include <ctype.h>

#define N 100

int expand(char to[], char from[]);

int main(void) {
    char s1[N];
    char s2[] = "a-f6-93-";
    char s3[] = "-abcd1-4abfc";
    int i;

    for (i = 0; i < N; i++)
        s1[i] = '\0';

    printf("s2 = \"%s\"\n", s2);
    printf("s1 = \"%s\"\n", s1);
    printf("expand(s1, s2)\n");
    expand(s1, s2);
    printf("s1 = \"%s\"\n", s1);
    printf("s3 = \"%s\"\n", s3);
    printf("expand(s1, s3)\n");
    expand(s1, s3);
    printf("s1 = \"%s\"\n", s1);

    return 0;
}

/* expand: expands shorthand notations */
int expand(char to[], char from[]) {
    int c, i, j, p;
    char characters[0xFF];

    for (i = 0; i < 0xFF; i++)
        characters[i] = 0;   /* to no repetition; 
                if characters[i] == 1, character already exists in array */ 

    c = p = i = j = 0;
    if (from[i] == '-') {
        to[j++] = '-';
        i++;
    }
    while ((c = from[i]) != '\0') {
        if (isalpha(c) || isdigit(c)) {
            if (from[i + 1] == '-') {
                if ((p = from[i + 2]) > c && ((isdigit(c) && isdigit(p)) ||
                                            (isalpha(c) && isalpha(p))) ) {
                    while (c <= p) 
                        if (characters[c])
                            c++;   /* we miss character */
                        else {
                            characters[c] = 1;
                            to[j++] = c;
                            c++;
                        }
                    i += 3;
                } else if (p == '\0') {
                    to[j++] = c;
                    to[j++] = '-';
                    break;
                } else {
                    printf("Syntax error 1\n");
                    return -1;
                }
            }   /* if there is no '-' */
            else  {
                if (characters[c] == 0) {
                    characters[c] = 1;
                    to[j++] = c;
                }
                i++;
            }
        }   /* if c isn't digit or A-F symbols */
        else {
            printf("Syntax error 2\n");
            return -1;
        }
    }
    to[j] = '\0';

    return 0;
}

