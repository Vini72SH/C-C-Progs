#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TAM 20

struct conjunto {
    int max;    /* tamanho maximo do vetor atualmente alocado     */
    int card;   /* cardinalidade, isto eh, tamanho usado ate max  */
    int ptr;    /* ponteiro para algum indice do vetor (iterador) */
    int *v;     /* vetor de inteiros com no maximo max elementos  */
};

/*
 * Cria um conjunto vazio e o retorna, se falhar retorna NULL.
 * max eh o tamanho maximo do conjunto, isto eh, o tamanho maximo do vetor
 */
struct conjunto *cria_cjt (int max){
    struct conjunto *novoConjunto;

    novoConjunto = malloc(sizeof(struct conjunto));
    if(novoConjunto == NULL){
        return NULL;
    }

    novoConjunto->max = max;
    novoConjunto->card = 0;
    novoConjunto->ptr = 0;

    novoConjunto->v = malloc(max * sizeof(int));
    if(novoConjunto->v == NULL){
        free(novoConjunto);

        return NULL;
    }

    return novoConjunto;
}

/*
 * Remove todos os elementos do conjunto, libera espaco e devolve NULL.
 */
struct conjunto *destroi_cjt (struct conjunto *c){

    if((c == NULL) || (c->v == NULL)){
        return NULL;
    }

    free(c->v);
    free(c);

    return NULL;
}

/*
 * Retorna 1 se o conjunto esta vazio e 0 caso contrario.
 */
int vazio_cjt (struct conjunto *c){

    if((c == NULL) || (c->card != 0)){
        return 0;
    }

    return 1;
}

/*
 * Retorna a cardinalidade do conjunto, isto eh, o numero de elementos presentes nele.
 */
int cardinalidade_cjt (struct conjunto *c){

    return c->card;
}

/*
 * Insere o elemento no conjunto, garante que nao existam repeticoes.
 * Retorna 1 se a operacao foi bem sucedida. Se tentar inserir elemento existente,
 * nao faz nada e retorna 1 tambem. Retorna 0 em caso de falha por falta de espaco.
 */
int insere_cjt (struct conjunto *c, int elemento){
    int i, j;

    /*Caso não tenha espaço no vetor.*/
    if(c->card == c->max){
        return 0;
    }

    if(vazio_cjt(c)){
        c->v[c->card] = elemento;
        c->card++;
        return 1;
    }

    i = 0;
    while((i < c->card) && (c->v[i] < elemento)){
        i++;
    }

    if((i < c->card) && (c->v[i] == elemento)){
        return 1;
    }

    for(j = c->card-1; j >= i; j--){
        c->v[j+1] = c->v[j];
    }

    c->v[i] = elemento;
    c->card++;

    return 1;
}

/*
 * Remove o elemento 'elemento' do conjunto caso ele exista.
 * Retorna 1 se a operacao foi bem sucedida e 0 se o elemento nao existe.
 */
int retira_cjt (struct conjunto *c, int elemento){
    int i, j;

    i = 0;
    while((i < c->card) && (c->v[i] != elemento)){
        i++;
    }
    if(i >= c->card){
        return 0;
    }

    for(j = i; j < c->card-1; j++){
        c->v[j] = c->v[j+1];
    }

    c->card--;

    return 1;
}

/*
 * Retorna 1 se o elemento pertence ao conjunto e 0 caso contrario.
 */
int pertence_cjt (struct conjunto *c, int elemento){
    int i;

    i = 0;
    while((i < c->card) && (c->v[i] != elemento)){
        i++;
    }

    if((i < c->card) && (c->v[i] == elemento)){
        return 1;
    }

    return 0;
}

/*
 * Retorna 1 se o conjunto c1 esta contido no conjunto c2 e 0 caso contrario.
 */
int contido_cjt (struct conjunto *c1, struct conjunto *c2){
    int i;

    if(c1->card > c2->card){
        return 0;
    }

    for(i = 0; i < c1->card; i++){
        if(!(pertence_cjt(c2, c1->v[i]))){
            return 0;
        }
    }

    return 1;
}

/*
 * Retorna 1 se o conjunto c1 eh igual ao conjunto c2 e 0 caso contrario.
 */
int sao_iguais_cjt (struct conjunto *c1, struct conjunto *c2){
    int i;

    if(c1->card != c2->card){
        return 0;
    }

    i = 0;
    while((i < c1->card)){
        if(c1->v[i] != c2->v[i]){
            return 0;
        }
        i++;
    }

    return 1;
}

/*
 * Cria e retorna o conjunto uniao entre os conjunto c1 e c2.
 * Retorna NULL se a operacao falhou.
 */
struct conjunto *uniao_cjt (struct conjunto *c1, struct conjunto *c2){
    int i;
    struct conjunto *uniao;

    uniao = cria_cjt(c1->max + c2->max);
    if(uniao == NULL){
        return NULL;
    }

    if(uniao->v == NULL){
        return NULL;
    }

    for(i = 0; i < c1->card; i++){
        insere_cjt(uniao, c1->v[i]);
    }

    for(i = 0; i < c2->card; i++){
        insere_cjt(uniao, c2->v[i]);
    }

    return uniao;
}

/*
 * Cria e retorna o conjunto interseccao entre os conjuntos c1 e c2.
 * Retorna NULL se a operacao falhou.
 */
struct conjunto *interseccao_cjt (struct conjunto *c1, struct conjunto *c2){
    struct conjunto *intersec = cria_cjt(c1->max); // Crie um novo conjunto para a interseção

    if (intersec == NULL) {
        return NULL; // Falha na alocação, retorna NULL.
    }

    for (int i = 0; i < c1->card; i++) {
        if (pertence_cjt(c2, c1->v[i])) {
            insere_cjt(intersec, c1->v[i]); // Insira elementos comuns na interseção.
        }
    }

    return intersec; // Retorna o conjunto interseção.
}

/*
 * Cria e retorna uma copia do conjunto c e NULL em caso de falha.
 */
struct conjunto *copia_cjt (struct conjunto *c){
    int i;
    struct conjunto *copia;

    copia = cria_cjt(c->max);
    if(copia == NULL){
        return NULL;
    }

    for(i = 0; i < c->card; i++){
        insere_cjt(copia, c->v[i]);
    }

    return copia;
}

/*
 * Cria e retorna o conjunto diferenca entre c1 e c2, nesta ordem.
 * Retorna NULL se a operacao falhou.
 */
struct conjunto *diferenca_cjt (struct conjunto *c1, struct conjunto *c2){
    int i;
    struct conjunto *dif;

    dif = copia_cjt(c1);
    if(dif == NULL){
        return NULL;
    }

    for(i = 0; i < c2->card; i++){
        retira_cjt(dif, c2->v[i]);
    }

    return dif;

}

/*
 * Cria e retorna um subconjunto com elementos aleatorios do conjunto c.
 * Se o conjunto for vazio, retorna um subconjunto vazio.
 * Se n >= cardinalidade (c) entao retorna o proprio conjunto c.
 * Supoe que a funcao srand () tenha sido chamada antes.
 */
struct conjunto *cria_subcjt_cjt (struct conjunto *c, int n){
    int i;
    struct conjunto *subcon;

    if(n >= c->card){
        subcon = copia_cjt(c);

        return subcon;
    }

    subcon = cria_cjt(n);
    if(n == 0){

        return subcon;
    }
    while(subcon->card < n){
        i = rand() % c->card;
        insere_cjt(subcon, c->v[i]);
    }

    return subcon;
}

/*
 * Imprime os elementos do conjunto sempre em ordem crescente,
 * mesmo que a estrutura interna nao garanta isso.
 * Na impressao os elementos sao separados por um unico espaco
 * em branco entre os elementos, sendo que apos o ultimo nao
 * deve haver espacos em branco. Ao final imprime um \n.
 */
void imprime_cjt (struct conjunto *c){
    int i;

    if(vazio_cjt(c)){
        printf("Conjunto vazio.\n");

        return;
    }

    for(i = 0; i < c->card; i++){
        printf("%d ", c->v[i]);
    }
    printf("\n");
}

/*
 * As funcoes abaixo implementam um iterador que vao permitir
 * percorrer os elementos do conjunto.
 * O ponteiro ptr da struct (iterador) pode ser inicializado para apontar 
 * para o primeiro elemento e incrementado ate' o ultimo elemento 
 * do conjunto.
 */

/*
 * Inicializa ptr usado na funcao incrementa_iterador 
 */
void inicia_iterador_cjt (struct conjunto *c){

    if(c != NULL){
        c->ptr = 0;
    }
}

/*
 * Devolve no parametro ret_iterador o elemento apontado e incrementa o iterador.
 * A funcao retorna 0 caso o iterador ultrapasse o ultimo elemento, ou retorna
 * 1 caso o iterador aponte para um elemento valido (dentro do conjunto).
 */
int incrementa_iterador_cjt (struct conjunto *c, int *ret_iterador){

    if((c != NULL) && (c->ptr < c->card)){
        *ret_iterador = c->v[c->ptr];
        c->ptr++;

        return 1;
    }

    return 0;
}

/*
 * Escolhe um elemento qualquer do conjunto para ser removido, o remove e
 * o retorna.
 * Nao faz teste se conjunto eh vazio, deixa para main fazer isso       
 */
int retira_um_elemento_cjt (struct conjunto *c){
    int i, elemento;

    if(c )

    i = rand() % c->card;
    elemento = c->v[i];

    retira_cjt(c, elemento);

    return elemento;

}

int main(void){
    srand(0);
    int n, i, e;
    struct conjunto *c1, *c2, *uni, *dif, *inter, *sub;

    printf("Tamanho max dos conjuntos: ");
    scanf("%d", &n);

    c1 = cria_cjt(n);
    c2 = cria_cjt(n);

    printf("Digite os elementos do conjunto 1: ");
    for(i = 0; i < c1->max; i++){
        scanf("%d", &e);
        insere_cjt(c1, e);
    }

    printf("Digite os elementos do conjunto 2: ");
    for(i = 0; i < c2->max; i++){
        scanf("%d", &e);
        insere_cjt(c2, e);
    }

    printf("Conjunto 1:\n");
    imprime_cjt(c1);

    printf("Conjunto 2:\n");
    imprime_cjt(c2);

    uni = uniao_cjt(c1, c2);
    printf("Conjunto união:\n");
    imprime_cjt(uni);

    dif = diferenca_cjt(c1, c2);
    printf("Diferença de conjuntos:\n");
    imprime_cjt(dif);

    inter = interseccao_cjt(c1, c2);
    printf("Intersecção de conjuntos:\n");
    imprime_cjt(inter);

    printf("Digite o tamanho do subconjunto: ");
    scanf("%d", &n);
    sub = cria_subcjt_cjt(c1, n);
    printf("Subconjunto do conjunto 1:\n");
    imprime_cjt(sub);

    if(sao_iguais_cjt(c1, c2)){
        printf("Os conjuntos são iguais!\n");
    }else{
        printf("Os conjuntos não são iguais!\n");
    }

    printf("Retirando um elemento aleatório do conjunto 2:\n");
    e = retira_um_elemento_cjt(c2);
    printf("Elemento removido: %d\n", e);
    imprime_cjt(c2);

    destroi_cjt(c1);
    destroi_cjt(c2);
    destroi_cjt(uni);
    destroi_cjt(dif);
    destroi_cjt(inter);
    destroi_cjt(sub);

    return 0;
}