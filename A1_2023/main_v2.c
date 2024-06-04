#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
  char *rotulo;
  char *tipo;
  char *categorias;
} atributo;

#define LINESIZE 1024

void exibe_atributos(atributo *infos, int tamanho){
    if (infos == 0){
        printf("O arquivo ARFF fornecido é inválido!\n");
        exit(0);
    }

    printf("==== ATRIBUTOS DO ARQUIVO ====\n");
    for(int i = 0; i < tamanho; i++){
        printf("-> Atributo #%d\n", i+1);
        printf("Rótulo: %s\n", infos[i].rotulo);
        printf("Tipo: %s\n", infos[i].tipo);
        if (infos[i].categorias) printf("Categorias: %s\n", infos[i].categorias);
        if (i < tamanho-1) printf("------------------------------\n");
    }
    printf("===============================\n");
}

int conta_atributos(FILE *arff){
    int qtd;
    char line[LINESIZE + 1];

    qtd = 0;
    fgets(line, LINESIZE, arff);
    while(!(feof(arff))){
      if((strlen(line) > 1) && (strncmp(line, "@attribute", 10) == 0)){
        qtd++;
      }
      fgets(line, LINESIZE, arff);
    }

    rewind(arff);

    return qtd;
}

atributo* processa_atributos(FILE *arff){
    int tam, i;
    atributo *v;
    char *token;
    char line[LINESIZE + 1];

    /* Aloca um vetor com tamanho suficiente para receber os atributos.*/
    tam = conta_atributos(arff);
    v = malloc(tam * (sizeof(atributo)));
    if(!v) return NULL;

    i = 0;
    /* Executa lendo todas as linhas do arquivo. */
    while((fgets(line, LINESIZE, arff) != NULL)){
        /* Se a linha tem tamanho maior que 1 e
         * possui a chave "@attribute", então é válida. */
        if((strlen(line) > 1) && (strncmp(line, "@attribute", 10) == 0)){
            token = strtok(line, " "); /* Recebe o "@attribute" */
            token = strtok(NULL, " "); /* Recebe o rotulo do atributo.*/
            v[i].rotulo = strdup(token);
            token = strtok(NULL, "\n"); /* Recebe a informaçao final. */
            /* Verifica o tipo do atributo, inserindo a string corretamente. */
            if((strcmp(token, "numeric") == 0) || (strcmp(token, "string") == 0)){
                v[i].tipo = strdup(token);
                v[i].categorias = NULL;
            }else{
                v[i].tipo = strdup("categoric");
                v[i].categorias = strdup(token);
            }
            i++;
        }else{
            if((strncmp(line, "@attribute", 10)) && (strlen(line) > 6)){
                printf("Atributo invalido!\n");
                break;
            }
        }

        if(strncmp(line, "@data", 5) == 0){
            return v;
        }
    }

    printf("Arquivo invalido.\n");
    for(i = 0; i < tam; i++){
        free(v[i].rotulo);
        free(v[i].tipo);
        free(v[i].categorias);
    }

    free(v);

    return NULL;

}

int main(int argc, char **argv){
  int opt, qtd, i;
  FILE *arq;
  char exibicao = 0;
  char *entrada = 0;
  atributo *infos;

  while ((opt = getopt(argc, argv, "pi:")) != -1) {
    switch (opt) {
    case 'i':
      entrada = strdup(optarg);
      break;
    case 'p':
      exibicao = 1;
      break;
    default:
      fprintf(stderr, "Forma de uso: ./arff -i <arq_in> [-p]\n");
      exit(1);
    }
  }

  if ( ! entrada ) {
    fprintf(stderr, "Forma de uso: ./arff -i <arq_in> [-p]\n");
    exit(2);
  }

  arq = fopen(entrada, "r");
  if(!arq){
    perror("Erro ao abrir arquivo.\n");
    exit(1);
  }

  qtd = conta_atributos(arq);
  infos = processa_atributos(arq);

  if (exibicao){
    exibe_atributos(infos, qtd);
  }

  for(i = 0; i < qtd; i++){
    free(infos[i].rotulo);
    free(infos[i].tipo);
    free(infos[i].categorias);
  }

  free(entrada);
  free(infos);
  fclose(arq);

  return 0 ;
}
