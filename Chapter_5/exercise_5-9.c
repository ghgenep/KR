
/* Exercise 5.9
   The program uses multidimensional arrays in day_of_year() and month_day()
   functions, that are improved(this one checks input data). This version uses
   pointers to take values from multidimensional array. */

#include <stdio.h>

int day_of_year(int year, int month, int day);
int month_day(int year, int yearday, int *month, int *day);

int main(void) {
    int m = 0, d = 0, day_of_year_out;
    
    if (month_day(1988, 60, &m, &d) == -1 || 
        (day_of_year_out = day_of_year(1988, 2, 29)) == -1) {
        printf("error: incorect input data\n");
    return 0;
        }
        printf("day_of_year(1988, 2, 29) returns %d\n", day_of_year_out);
        printf("month_day(1988, 60, &m, &d) returns %dm %dd\n", m ,d);
        return 0;
}

static char daytable[2][13] = {
    {0, 31,   28  , 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31,   29  , 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/* day_of_year: calculate and return day of year using year, month and 
   day given; if input data are incorrect, return -1 */
int day_of_year(int year, int month, int day) {
    int leap, i;
    
    /* check correctness of input data */
    if (year < 0 || month < 1 || month > 12 || day < 1)
        return -1;
    else {
        leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
        if (day > (*(daytable + leap))[month])
            return -1;
    }
    
    for (i = 1; i < month; i++)
        day += (*(daytable + leap))[month];
    return day;
}

/* month_day: calculate month and day of year using year and count of 
   days given; if input data are incorrect, return -1 */
int month_day(int year, int yearday, int *month, int *day) {
    int leap, i;
    register int monthday;
     
    /* check correctness of input data */
    if (year < 0 || yearday < 1)
        return -1;
    else {
        leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
        if ((leap && yearday > 366) || (!leap && yearday > 356))
            return -1;            
    }
 
    for (i = 1; yearday > (monthday = (*(daytable + leap))[i]); i++)
        yearday -= monthday;
    *month = i;
    *day = yearday; 
    return 0;
}
 
