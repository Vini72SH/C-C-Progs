#include <stdio.h>
#include <stdlib.h>

struct noticia{
    char titulo[32];
    char texto[512];
    unsigned char idade;
    struct noticia *prox;
};

struct fila{
    unsigned char tam;
    struct noticia *prime;
    struct noticia *ult;
};

/* Retorna um ponteiro para uma nova fila. */
struct fila *criaFila(){
    struct fila *novaFila;

    /* Alocação de Memória. */
    novaFila = malloc(sizeof(struct fila));
    if (novaFila == NULL){
        return NULL;
    }

    novaFila->tam = 0;
    novaFila->prime = NULL;
    novaFila->ult = NULL;

    return novaFila;
}

/* Recolhe as informações para as notícias. */
void requisita(char *titulo, char *texto){
    getchar();
    printf("\nDigite o título: ");
    fgets(titulo, 33, stdin);
    printf("Digite o texto: ");
    fgets(texto, 513, stdin);
}

/* Indica se a fila está vazia. */
int fila_vazia(struct fila *f){

    if(f->tam == 0){
        return 1;
    }

    return 0;
}

/* Insere a notícia no último lugar da fila. */
void insere_not (struct fila *f){
    struct noticia *nova;

    nova = malloc(sizeof(struct noticia));
    if(nova == NULL){
        return;
    }
    
    nova->idade = 0;
    nova->prox = NULL;
    requisita(nova->titulo, nova->texto);    

    /* Insere no começo caso a fila esteja vazia. */
    if(fila_vazia(f)){
        f->prime = nova;
        f->ult = nova;

    }else{
        f->ult->prox = nova;
        f->ult = nova;
    }

    f->tam++;
}

/* Remove a primeira notícia da fila. */
int remove_not (struct fila *f){
    struct noticia *aux;

    if(fila_vazia(f)){
        return 0;
    }

    aux = f->prime;
    f->prime = aux->prox;
    free(aux);

    f->tam--;

    return 1;
}

/* Seleciona e publica a edição do jornal. */
/* Prioriza as Breaking News. */
/* Publica entre 0 e 2 notícias por edição. */
/* Publica apenas notícias com menos de 3 dias. */
void fechar_ed(struct fila *bn, struct fila *i){
    int k;

    /* Caso não aja notícias. */
    if((fila_vazia(bn)) && (fila_vazia(i))){
        printf("\nEsta edição foi pulada por falta de notícias!\n");

        return;
    }

    printf("=======================================================\n");

    k = 0;
    while((!(fila_vazia(bn))) && (k < 2)){
        if(bn->prime->idade <= 3){
            printf("%s\n", bn->prime->titulo);
            printf("%s\n", bn->prime->texto);
            k++;
        }
        remove_not(bn);

        if((k == 1) && ((!(fila_vazia(bn))) || (!(fila_vazia(i))))){
            printf("\n==\n\n");
        }
    }

    while((!(fila_vazia(i))) && (k < 2)){
        if(i->prime->idade <= 3){
            printf("%s\n", i->prime->titulo);
            printf("%s\n", i->prime->texto);
            k++;
        }
        remove_not(i);

        if((k == 1) && (!(fila_vazia(i)))){
            printf("\n==\n\n");
        }
    }

    printf("=======================================================\n");
}

/* Atualiza a idade de todas as notícias. */
void att_not(struct fila *f){
    struct noticia *aux;

    if(fila_vazia(f)){
        return;
    }

    aux = f->prime;
    while(aux != NULL){
        aux->idade++;
        aux = aux->prox;
    }
}

/* Destrói a fila, liberando memória. */
void destroi_fila (struct fila *f){

    while(!(fila_vazia(f))){
        remove_not(f);
    }

    free(f);
    f = NULL;

    return;
}

int main(){
    int ev, type;
    struct fila *bn, *i;

    bn = criaFila();
    i = criaFila();

    printf("Bem-vindo ao Jornal do DINF!\n");
    do{
        printf("\n=================MENU=================\n");
        printf("- (1) Cadastrar Notícia.\n");
        printf("- (2) Fechar Edição.\n");
        printf("- (3) Sair.\n");
        printf("Selecione a opção: ");
        scanf("%d", &ev);
        switch(ev){
            case 1:
                printf("Tipo da notícia (1-BN) (0-I): ");
                scanf("%d", &type);
                if(type){
                    insere_not(bn);
                }else{
                    insere_not(i);
                }
                break;
            case 2:
                fechar_ed(bn, i);
                att_not(bn);
                att_not(i);
                break;
            case 3:
                break;
            default:
                printf("Insira um valor válido.\n");
        }
    }while(ev != 3);

    destroi_fila(bn);
    destroi_fila(i);

    return 0;
}