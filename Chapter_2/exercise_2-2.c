
/* Exercise 2.2
   The program reads and prints the line(no using '&&' and '||' in FOR cycle). */

int main(void) {
    int c, i;
    char s[N];

    /* for (i = 0; i < N-1 && (c = getchar()) != EOF && c != '\n'; ++i) */
    for (i = 0; i < N-1; i++) 
        if ((c = getchar()) != '\n') 
            if (c != EOF)
                s[i] = c;
    printf("%s\n", out);

    return 0;
}

