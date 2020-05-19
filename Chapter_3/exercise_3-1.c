
/* Exercise 3.1
   The program uses new_binsearch() function that does a binary search
   for some number. */

#include <stdio.h>
#define N 100

int new_binsearch(int x, int v[], int n);

int main(void) {
    int arr[N];
    int i;

    for (i = 0; i < N; i++)
        arr[i] = i;

    printf("new_binsearch(50, arr, N) returns %d\n", 
                           new_binsearch(50, arr, N));
    arr[50] = arr[49];
    printf("new_binsearch(50, arr, N) returns %d\n", 
                           new_binsearch(50, arr, N));

    return 0;
}

/* new_binsearch: do binary search for some number */
int new_binsearch(int x, int v[], int n) {
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low < high) {
        mid = (low + high) / 2;
        if (x <= v[mid])
            high = mid;
        else
            low = mid + 1;
    }

    if (x == v[low])
        return low;
    else
        return -1;
}

