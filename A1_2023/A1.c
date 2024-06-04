#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
  char *rotulo;
  char *tipo;
  char *categorias;
} atributo;

void exibe_atributos(atributo *infos, int quantidade){
    if (infos == 0){
        printf("O arquivo ARFF fornecido é inválido!\n");
        exit(0);
    }

    printf("==== ATRIBUTOS DO ARQUIVO ====\n");
    for(int i = 0; i < quantidade; i++){
        printf("-> Atributo #%d\n", i+1);
        printf("Rótulo: %s\n", infos[i].rotulo);
        printf("Tipo: %s\n", infos[i].tipo);
        if (infos[i].categorias) printf("Categorias: %s\n", infos[i].categorias);
        if (i < quantidade-1) printf("------------------------------\n");
    }
    printf("===============================\n");
}

int conta_atributos(FILE *arff){
  int quantidade = 0;
  char buffer[1024], *resultado;

  while (1){
    resultado = fgets(buffer, 1024, arff);
    if (resultado != buffer){
      fprintf(stderr, "Existem erros no arquivo fornecido!\n");
      exit(4);
    }

    if (!strncmp(buffer, "@attribute ", 11)) quantidade++;
    else if (buffer[0] == '\n') continue;
    else if ((!strcmp(buffer, "@data")) || (!strcmp(buffer, "@data\n")))return quantidade;
    else return 0;
  }
}

atributo* processa_atributos(FILE *arff, int quantidade){
  atributo *dados = (atributo*) malloc(quantidade * sizeof(atributo));
  char buffer[1024], *resultado, *base;
  int indice = 0, subindice;

  while (1){
    resultado = fgets(buffer, 1024, arff);
    if (resultado != buffer){
      fprintf(stderr, "Existem erros no arquivo fornecido!\n");
      exit(4);
    }

    if (!strncmp(buffer, "@attribute ", 11)){
      base = &buffer[11];
      subindice = 0;
      resultado = strstr(base, " ");
      while (resultado != 0){
        resultado[0] = '\0';
        if (!subindice) dados[indice].rotulo = strdup(base);
        else if (subindice == 1){
          if (base[0] != '{'){
            dados[indice].tipo = strdup(base);
            dados[indice].categorias = 0;
          }
          else{
            dados[indice].tipo = strdup("categoric");
            dados[indice].categorias = strdup(base);
          }
        }
        subindice++;
        
        base = &resultado[1];
        if (base[0] != '{'){
          resultado = strstr(base, " ");
          if (!resultado){
            resultado = strstr(base, "\n");
          }
        }
        else resultado = strstr(base, "}") + 1;
      }
      
      if ((resultado) || (subindice != 2)) return 0;
      indice++;
    }
    else if (buffer[0] == '\n') continue;
    else if ((!strcmp(buffer, "@data")) || (!strcmp(buffer, "@data\n"))) return dados;
    else return 0;
  }
}

int main(int argc, char **argv){
  int opt;
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

  if (!entrada){
    fprintf(stderr, "Forma de uso: ./arff -i <arq_in> [-p]\n");
    exit(2);
  }

  FILE *arquivo = fopen(entrada, "r");
  if (!arquivo){
    fprintf(stderr, "Não foi possível abrir o arquivo informado!\n");
    exit(3);
  }

  int qntd_atributos = conta_atributos(arquivo);
  if (!qntd_atributos){
    fprintf(stderr, "Existem erros no arquivo fornecido!\n");
    exit(4);
  }
  fseek(arquivo, 0, SEEK_SET);
  atributo *dados_atributos = processa_atributos(arquivo, qntd_atributos);

  if (exibicao){
    exibe_atributos(dados_atributos, qntd_atributos);
  }

  return 0 ;
}
