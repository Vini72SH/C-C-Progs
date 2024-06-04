#include <stdio.h>

int main (){
    int i = 1;
    while (i <= 10){
        printf ("%d ", i);
        i++;
    }
    printf ("\n");

    i = 10;
    do { 
        printf ("%d ", i);
        i--;
    }while (i >= 1);
    printf ("\n");
} 