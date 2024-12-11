#include <stdio.h>

int PFVO(int v[], int a, int b) {
    int m;

    if(a > b){
        return a - 1;
    }

    m = (a + b)/2;
    if(v[m] <= m){
        return PFVO(v, m+1, b);
    }
    
    return PFVO(v, a, m-1);
}

int find_special_index(int arr[], int size) {
    return PFVO(arr, 0, size - 1);
}

int main() {
    int arr[] = {-10, -5, 2, 4, 7, 9, 12, 14};
    int size = sizeof(arr) / sizeof(arr[0]);
    int result = find_special_index(arr, size);
    printf("O índice ou posição desejada é: %d\n", result);
    return 0;
}
