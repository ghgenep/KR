
/* Exercise 4.2
   The program uses atof(s) function, that translates double-string
   into double-number and understands an exponential notation. */

#include <stdio.h>
#include <ctype.h>

double atof(char num[]);
int ten_power(int i);

int main(void) {

    printf("atof(\"\t12e2\") returns %.7f\n", atof("\t12e2"));
    printf("atof(\"\t-12e2\") returns %.7f\n", atof("\t-12e2"));
    printf("atof(\"\t12e-2\") returns %.7f\n", atof("\t12e-2"));
    printf("atof(\"\t-12e-2\") returns %.7f\n", atof("\t-12e-2"));
    printf("atof(\"\t12.3e2\") returns %.7f\n", atof("\t12.3e2"));
    printf("atof(\"\t-12.3e2\") returns %.7f\n", atof("\t-12.3e2"));
    printf("atof(\"\t12.3e-2\") returns %.7f\n", atof("\t12.3e-2"));
    printf("atof(\"\t-12.3e-2\") returns %.7f\n\n", atof("\t-12.3e-2"));
    printf("atof(\"\t-12.3e0\") returns %.7f\n", atof("\t-12.3e0"));
    printf("atof(\"\t12.3e-\") returns %.7f\n", atof("\t12.3e-"));

    return 0;
}

/* atof: translate double-string into double-number */
double atof(char num[]) {
    int i, sign, j, power;
    double out;  
  
    /* missing the spaces */
    for (i = 0; isspace(num[i]); i++)
        ;

    /* taking the sign */
    sign = (num[i] == '-') ? -1 : 1;
    if (num[i] == '+' || num[i] == '-')
        i++;

    /* taking the float-number */
    for (out = 0.0; isdigit(num[i]); i++)
        out = out * 10.0 + (num[i] - '0'); 
    if (num[i] == '.')
        i++;
    for (power = 1; isdigit(num[i]); i++) {
        out = out * 10.0 + (num[i] - '0');
        power *= 10;
    }

    /* float-number without the exponential notation */
    out = (out * sign) / power; 

    /* decoding of the exponential notation */
    if (num[i] == 'E' || num[i] == 'e') {
        i++;
        sign = (num[i] == '-') ? -1 : 1;
        if (num[i] == '+' || num[i] == '-')
            i++;

        for (power = 0, j = i; isdigit(num[j]); j++)
            power = power * 10 + (num[j] - '0');
        if (j != i) {
        /* if j == i, there is no power; go out of decoding block */
            if (sign == 1)  /* E3 or E+3 */
                return (out * ten_power(power));
            else  /* E-3 */
                return (out / ten_power(power));
        }
    }

    return out;  /* no the exponential notation */
}

/* ten_power: return power of 10 */
int ten_power(int i) {
    int out = 1;

    while (i-- > 0)
        out = out * 10;

    return  out;
}

