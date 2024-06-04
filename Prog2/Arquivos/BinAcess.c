#include <stdio.h>
#include <stdlib.h>

struct citzen{
  char name[11];
  int hacking;
  int criminal;
};
typedef struct citzen citzen;

struct population{
  citzen *person;
  struct population *next;
};
typedef struct population population;

population *read_file(char *file_name){
    FILE *arq;
    population *head, *tail, *aux;

    head = NULL; tail = NULL;
    arq = fopen(file_name, "r");
    if(!arq) return NULL;

    while(1){
        aux = malloc(sizeof(population));
        aux->person = malloc(sizeof(citzen));

        if(!(fread(aux->person, sizeof(citzen), 1, arq))){
            free(aux->person);
            free(aux);
            break;
        }

        aux->next = NULL;
        if(head == NULL){
            head = aux;
            tail = aux;
        }else{
            tail->next = aux;
            tail = aux;
        }
    }

    fclose(arq);
    return head;
}

void print_information(population *head){
    float med;
    int qtd, cincoM;
    population *aux;

    qtd = 0; med = 0; cincoM = 0;
    aux = head;
    printf("=================== CyberPunk 2077 ===================\n");
    printf("----------------- Imprimindo Pessoas -----------------\n");
    while(aux != NULL){
        printf("-------------------\n");
        printf("Nome: %s\n", aux->person->name);
        printf("Hacking: %d\n", aux->person->hacking);
        printf("-------------------\n");
        qtd++;
        med = med + aux->person->hacking;
        if(aux->person->criminal > 5) cincoM++;
        aux = aux->next;
    }   
    printf("----------------------------------\n");
    med = med / (float)qtd;

    printf("--> TOTAL DE CIDADAOS: %d\n", qtd);
    printf("--> MEDIA DE HAB. DE HACKING: %2.f\n", med);
    printf("--> CIDADAOS PERIGOSOS: %d\n", cincoM);
    printf("========================================================\n");
}

void free_population(population *head){
    population *i;

    i = head;
    while(head){
        i = head->next;
        free(head->person);
        free(head);
        head = i;
    }
}

int main(){
    population *head;

    head = read_file("citizens.bin");
    print_information(head);
    free_population(head);

    return 0;
}