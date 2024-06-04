#include <stdlib.h>
#include <stdio.h>

int main (void){
    char b;
    FILE *mouse = fopen("/dev/input/mice", "rb");
    if(!(mouse)){
        return 1;
    }

    while(1){
        b = fgetc(mouse);
        printf("%d\n", b);
    }

    fclose(mouse);
    return 0;
}