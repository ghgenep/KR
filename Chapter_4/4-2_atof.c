
/* The program uses atof(s) function, that translates double-string
   into double-number. */

#include <stdio.h>
#include <ctype.h>

#define MAXLINE 1000

double atof(char num[]);
int my_getline(char line[], int lim);

int main(void) {
    char s[MAXLINE];

    while (my_getline(s, MAXLINE) > 0)
        printf("\t%.5f\n", atof(s));

    return 0;
}

/* atof: translate double-string into double-number */
double atof(char num[]) {
    int i, sign;
    double out, power;    

    i = 0;
    while (isspace(num[i]))  /* miss the spaces */
        i++;
    sign = 1;   /* if there is no sign character */
    if (num[i] == '+' || num[i] == '-') {
        sign = (num[i] == '-') ? -1 : 1;
        i++;
    }
/* or
    sign = (num[i] == '-') ? -1 : 1;
    if (num[i] == '+' || num[i] == '-')
        i++;
*/
    /* taking the float-number */ 
    for (out = 0.0; isdigit(num[i]); i++)
        out = out * 10.0 + (num[i] - '0'); 
    if (num[i] == '.')
        i++;
    for (power = 1.0; isdigit(num[i]); i++) {
        out = out * 10.0 + (num[i] - '0');
        power *= 10.0;
    }

    return (out * sign / power);
}

/* my_getline: get string and return a count of letters, or 0 */
int my_getline(char line[], int lim) {
    int i, c;

    i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        line[i++] = c;
    if (c == '\n')
        line[i++] = '\n';
    else if (lim == 0)
        printf("line is too long.\n");
    line[i] = '\0';

    /* if c == EOF && i == 0, line is void */
    return i;
}

