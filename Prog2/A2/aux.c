#include "aux.h"

int conta_digitos(int num){
    int dig, div;

    if(num == 0)
        return 1;

    dig = 0;
    div = num;
    while(div != 0){
        dig++;
        div = div / 10;
    }

    return dig;
}

/* Separa a linha e retorna a palavra
 * antes da primeira vírgula. */
char* separa(const char *string){
    char *pos_virgula;

    if (!string) return 0;

    pos_virgula = strchr(string, ',');
    if (!pos_virgula) return 0;

    *pos_virgula = '\0';
    return pos_virgula + 1;
}

void cria_espacos(int num){
    int i;

    for(i = 0; i <= num; i++)
        printf(" ");
}

void cria_vetor(char **v, int tam, char *linha){
    int i;
    char *token, *campo;
    char line[LINESIZE + 1];

    strcpy(line, linha);
    token = line;
    for(i = 0; i < tam; i++){
        campo = token;
        token = separa(campo);
        v[i] = strdup(campo);
    }
}

void libera_strings(char **v, int tam){
    int i;

    for(i = 0; i < tam; i++)
        free(v[i]);
}

/* Preenche um vetor com tamanho tam
 * com o caracter c. */
void preenche_vetor(char v[], int tam, char c){
    int i;
    for(i = 0; i < tam; i++){
        v[i] = c;
    }
    v[tam] = '\0';
}