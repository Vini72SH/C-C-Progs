#include <stdio.h>
#include <string.h>

int main(){
    int i;
    char string[1025];
    char *sep;

    printf("Digite a linha CSV (max. 1024 carac.):");
    scanf("%1025[^\n]", string);
    getchar();

    i = 1;
    sep = strtok(string, ",");
    while(sep != NULL){
        printf("Coluna %d: ", i);
        printf("%s\n", sep);
        sep = strtok (NULL, ",");
        i++;
    }

    return 0;
}