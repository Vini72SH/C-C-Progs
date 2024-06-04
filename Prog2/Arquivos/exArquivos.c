#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nodo{
    int qtd;
    char string[100];
    struct nodo *prox;
};

struct lista{
    int tam;
    struct nodo *prime;
    struct nodo *ult;
};

struct lista *criaLista (){
    struct lista *l;

    l = malloc(sizeof(struct lista));
    if (!l) return NULL;

    l->tam = 0;
    l->prime = NULL;
    l->ult = NULL;

    return l;
}

int listaVazia(struct lista *l){
    if(!l) return 0;

    if(l->tam == 0) return 1;
    
    return 0;
}

struct nodo *criaNodo (char *s){
    struct nodo *novo;

    novo = malloc(sizeof(struct nodo));
    if(!novo) return NULL;

    novo->qtd = 1;
    strcpy(novo->string, s);
    novo->prox = NULL;

    return novo;
}

int insereL(struct lista *l, char *s){
    struct nodo *aux, *no;

    if(!l) return 0;

    aux = l->prime;
    while((aux != NULL) && ((strcmp(s, aux->string)) != 0)){
        aux = aux->prox;
    }

    if(aux != NULL){
        aux->qtd++;

        return 1;
    }

    no = criaNodo(s);
    if(!no) return 0;
    if(listaVazia(l)){
        l->prime = no;
        l->ult = no;
    }else{
        l->ult->prox = no;
        l->ult = no;
    }

    l->tam++;

    return 1;
}

struct lista *destroiLista(struct lista *l){
    struct nodo *aux, *no;

    if(!l) return NULL;

    aux = l->prime;
    while(aux != NULL){
        no = aux->prox;
        free(aux);
        aux = no;
    }

    free(l);
    
    return NULL;
}

void imprimePalavras(struct lista *l){
    struct nodo *aux;

    if(!l) return;

    aux = l->prime;
    while(aux != NULL){
        printf("Palavra: %s ---- Repetições: %2d\n", aux->string, aux->qtd);
        aux = aux->prox;
    }

    return;
}

int resultado(struct lista *l, char *s){
    int maior;
    char rep[100];
    struct nodo *aux;

    if(!l) return 0;

    aux = l->prime;
    maior = aux->qtd;
    while(aux != NULL){
        if(maior <= aux->qtd){
            maior = aux->qtd;
            strcpy(rep, aux->string);
        }
        aux = aux->prox;
    }

    strcpy(s, rep);

    return maior;
}

int main(){
    int ret, rep;
    FILE *arq;
    char word[100];
    struct lista *l;

    l = criaLista();
    if(!l){
        perror("Erro ao criar a lista.");
        return 1;
    }

    arq = fopen("RobinHood.txt", "r");
    if(!arq){
        perror("Erro ao abrir arquivo.");
        exit(1);
    }

    ret = fscanf(arq, "%s", word);
    while(ret != EOF){
        insereL(l, word);
        ret = fscanf(arq, "%s", word);
    } 

    //imprimePalavras(l);

    rep = resultado(l, word);
    printf("Palavra mais repetida: %s\n", word);
    printf("N° de repetições: %d\n", rep);

    fclose(arq);
    l = destroiLista(l);

    return 0;
}