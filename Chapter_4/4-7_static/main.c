
/* The program uses class of memory static. 
   The program consist of
   following files:
   - main.c
   - static.c
   - not_static.c */

#include <stdio.h>

extern void printf_my(void);    /* from not_static.c file; if this
                file is absent, there will be an error */
extern void printf_new(void);   /* from static.c file */
void use_static(void);

int main(void) {
    int i = 0;

    while (i++ < 10)
        use_static();      
    /* the main function will use printf_my() function from
       not_static.c file; in static.c file there is the same name
       function: printf_my(), but it is static, so it can be used
       out of static.c file */
    printf_my();
    /* the printf_new() function uses printf_my() function from
       static.c file; it is visible only there and printf_new 
       function is visible everywhere */
    printf_new();
    /* the same things happens with variables: static variables are
       invisible out of file ... */

    return 0;
}

/* use_static() function is used for testing static variables, which is not
   deleted after the function is finished */
void use_static(void) {
    static int c = 0;  /* static variables are initialized only once */
    
    printf("static external c = %d\t", c);
    
    {
        static int c  = 9;
        printf("static internal c = %d\n", c);
        c--;
    }
    c++;   
}

