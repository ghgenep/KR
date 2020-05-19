
/* The program uses binsearch() function that does a 
   binary search for some number. */

#include <stdio.h>
#define N 100

int binsearch(int x, int v[], int n);

int main(void) {
    int arr[N];
    int i;

    for (i = 0; i < N; i++)
        arr[i] = i;

    printf("binsearch(50, arr, N) returns %d\n", binsearch(50, arr, N));
    arr[50] = arr[49];
    printf("binsearch(50, arr, N) returns %d\n", binsearch(50, arr, N));

    return 0;
}

/* binsearch: do binary search for some number */
int binsearch(int x, int v[], int n) {
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if (x < v[mid])
            high = mid - 1;
        else if (x > v[mid])
            low = mid + 1;
        else
            return mid;
    }

    return -1;
}

