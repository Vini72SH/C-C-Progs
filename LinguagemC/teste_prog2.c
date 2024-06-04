#include <stdio.h>
#include <stdlib.h>


typedef struct{
    char char_qualquer;
    int int_qualquer;
    double double_qualquer;

} meus_dados;

int main(){
    unsigned char vetor_char[16];
    meus_dados *pnt_struct;
    pnt_struct = (meus_dados*) vetor_char;
    pnt_struct->char_qualquer = 'a';
    pnt_struct->int_qualquer = 1024;
    pnt_struct->double_qualquer = 255.255;
    printf("char_qualquer: %c\n", pnt_struct->char_qualquer);
    printf("int_qualquer: %d\n", pnt_struct->int_qualquer);
    printf("double_qualquer: %lf\n", pnt_struct->double_qualquer);

    return 0;
}