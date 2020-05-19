
/* The program uses q_sort() function, that sorts array by using 
   recursion. */

#include <stdio.h>

#define N 10

void swap(int i[], int first, int last);
void q_sort(int v[], int left, int right);

int main(void) {
    int arr[N] = {1, 3, 5, 12, 6, 8, 2, 4, 8};
    int i = 0;
    
    while (i < N) {
        printf("%d ", arr[i++]);
    }
    printf("\n");
    
    i = 0;
    q_sort(arr, 0, N - 1);
    while (i < N)
        printf("%d ", arr[i++]);
    printf("\n");    
        
    return 0;
}

/* swap: exchange two arguments in i[] array */
void swap(int i[], int first, int last) {
    int temp = i[first];
    i[first] = i[last];
    i[last] = temp;
}

/* q_sort: sort v[] array by using recursion */
void q_sort(int v[], int left, int right) {
    int last, i;
    
    if (left >= right)  /* if v[] has only one element */
        return;
    swap(v, left, (right + left) / 2);
    last = left;  /* last == index of last number, that is less
                                    than v[left] */
    for (i = left + 1; i <= right; i++) 
        if (v[i] < v[left])
            swap(v, i, ++last);
    /* if last == left, v[left] is the smallest number in array;
       that's why "if (left >= right)" has ">=", not "=" */
    swap(v, left, last);
    q_sort(v, left, last - 1);  
    q_sort(v, last + 1, right);
}    

