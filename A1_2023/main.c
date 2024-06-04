#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define LINESIZE 1024

typedef struct {
  char *rotulo;
  char *tipo;
  char *categorias;
} atributo;

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
    int i;
    char line[LINESIZE+1];

    rewind(arff);

    i = 0;
    while(fgets(line, LINESIZE, arff) != NULL){
        if((strlen(line) > 1) && (strncmp(line, "@attribute", 10)) == 0){
            i++;
        }
    }

    rewind(arff);

    return i;
}

atributo* processa_atributos(FILE *arff){
    int i, qtd;
    char line[LINESIZE+1];
    char *token;
    atributo *v;    

    qtd = conta_atributos(arff);
    v = malloc(qtd * sizeof(atributo));
    if (!v) return NULL;

    i = 0;
    while(fgets(line, LINESIZE, arff) != NULL){
        if((strlen(line) > 1) && (strncmp(line, "@attribute", 10)) == 0){
            token = strtok(line, " "); // Ignora o primeiro token "@attribute"
            token = strtok(NULL, " "); // Obtém o rótulo do atributo
            v[i].rotulo = strdup(token);
            token = strtok(NULL, "\n"); // Obtém o tipo do atributo
            // Verifica se o tipo é "numeric" ou "string"
            if((strcmp(token, "numeric") == 0) || (strcmp(token, "string")) == 0){
                v[i].tipo = strdup(token);
                v[i].categorias = NULL;
            } else {
                v[i].tipo = strdup("categoric");
                v[i].categorias = strdup(token);
            }
            i++;
        }else{
            printf("Erro! Não há atributo nesta linha.\n");
        }
        if(strncmp(line, "@data", 5) == 0) return v;
    }

    // Se não encontrou "@data", o arquivo ARFF está incompleto
    // Libera memória alocada e retorna NULL
    for(int j = 0; j < i; j++){
        free(v[j].rotulo);
        free(v[j].tipo);
        free(v[j].categorias);
    }
    free(v);
    return NULL;
}


int main(int argc, char **argv){
  int i, opt, qtd;
  FILE *arq;
  atributo *vet;
  char exibicao = 0;
  char *entrada = 0;

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
  if (! arq){
    perror("Falha ao abrir arquivo.");
    exit(1);
  }
  // VOCÊ DEVE IMPLEMENTAR AS ROTINAS NECESSÁRIAS E A CHAMADA DE FUNÇÕES PARA PROCESSAR OS ATRIBUTOS ARFF AQUI

  vet = processa_atributos(arq);
  qtd = conta_atributos(arq);

  if (exibicao){
    exibe_atributos(vet, qtd);
  }

  for(i = 0; i < qtd; i++){
    free(vet[i].rotulo);
    free(vet[i].tipo);
    free(vet[i].categorias);
  }

  free(vet);
  free(entrada);
  fclose(arq);
  
  return 0 ;
}