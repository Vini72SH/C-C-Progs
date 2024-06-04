#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include "trie.h"

int main(int argc, char *argv[]){
    int i;
    FILE *arq;
    int status;
    Trie ArvTrie;
    char *linha = NULL;
    char* result = NULL;
    char teste[LINESIZE];
    unsigned long tamLinha;
    
    //muda o locale para mostrar os simbolos "certos"
        char* local = setlocale(LC_ALL, "pt_BR.UTF-8");
        if (local == NULL) return -1;
        
    // abre arquivo de entrada
    if( argc != 2 ){
        printf( "Erro nos argumentos da chamada\n" );
        printf( "Chamada: ./qualFilme nomeArqFilmes\n" );
        return 0;
    }
    arq= fopen( argv[1], "r" );
    if( arq == NULL ){
        printf( "Erro na abertura do arquivo\n" );
        return 0;
    }

    criaArv(&ArvTrie);

    while ((status = getline(&linha, &tamLinha, arq) != -1)){
        result = padronizaString(linha);
        ArvTrie = insere(result, ArvTrie); 
        free(result);
    }

    i = 0;
    while(i < 100){
        scanf("%[^\n]", teste);
        if(strlen(teste) >= 2)
            printf("%s\n", teste);
        getchar();
        functionUnity(ArvTrie, teste);
        i++;
    }

    freeArv(ArvTrie);

    free(linha);
    fclose(arq);

    return 1;
}