#include <stdlib.h>
#include <stdio.h>

/* Structs */

typedef struct teddy_machine{
    unsigned int id;
    unsigned int probability;

    struct teddy_machine *next;
    struct teddy_machine *previous;
} teddy_machine;

/* List functions */

teddy_machine* create_list (unsigned int machines){
    unsigned int i;
    teddy_machine *list, *aux, *no;

    list = malloc(sizeof(teddy_machine));
    if(list == NULL){
        return NULL;
    }

    list->id = 1;
    list->probability = 5;
    list->next = NULL;
    list->previous = NULL;

    for(i = 1; i < machines; i++){
        aux = malloc(sizeof(teddy_machine));
        if(aux == NULL){
            return NULL;
        }

        aux->id = i + 1;
        aux->probability = 5;
        aux->next = NULL;

        no = list;
        while(no->next != NULL){
            no = no->next;
        }

        no->next = aux;
        aux->previous = no;
    }

    aux->next = list;
    list->previous = aux;

    return list;
}

teddy_machine* select_machine (teddy_machine *list, unsigned int place){
    unsigned int i;
    teddy_machine *aux;

    aux = list;
    for(i = 0; i < place; i++){
        aux = aux->next;
    }

    return aux;

}

teddy_machine* remove_machine (teddy_machine *list, teddy_machine *remove) {
    teddy_machine *aux, *aux2;

    if((list == NULL) || (remove == NULL)){
        return NULL;
    }

    if((remove == list) && (list->next == list)){
        free(remove);

        return NULL;
    }

    aux = remove->previous;
    aux2 = remove->next;

    aux->next = aux2;
    aux2->previous = aux;

    if(list == remove){
        list = aux2;
    }

    free(remove);

    return list;
}

void destroy_list (teddy_machine *list){
    teddy_machine *aux;

    if((list == NULL) || ((list->next == NULL) && (list->previous == NULL))){
        free(list);

        return;
    }

    aux = list->next;
    while(aux != list){
        aux = aux->next;
        free(aux->previous);
    }

    free(aux);
}

void printMachines(teddy_machine *head) {
    teddy_machine *current = head;
    
    // Verifica se a lista está vazia
    if (head == NULL) {
        printf("Lista vazia\n");
        return;
    }
    
    // Percorre a lista até retornar ao início
    do {
        // Imprime os detalhes da máquina atual
        printf("ID: %u, Probability: %u\n", current->id, current->probability);
        // Avança para o próximo nó
        current = current->next;
    } while (current != head);
}

/* Randomization functions */

unsigned int get_place(unsigned int machines){
    return rand() % machines;
}

unsigned int get_attempt(){
    return rand() % 100 + 1;
}

/* Printing functions */

void print_attempt(teddy_machine *machine, unsigned int attempt){

    if (attempt <= machine->probability) printf("O URSO DA MAQUINA %u [FOI] OBTIDO!\n", machine->id);
    else printf("O URSO DA MAQUINA %u [NAO FOI] OBTIDO!\n", machine->id);
}
void print_available_machines(teddy_machine *list){

    if (!list) printf("NAO HA MAQUINAS DISPONIVEIS!\n");
    else{
        teddy_machine *i = list;
        do {
            printf("PROBABILIDADE DA MAQUINA %u: %u\n", i->id, i->probability);
            i = (teddy_machine*) i->next;
        } while((i) && (i != list));
    }

}

/* Main function */

int main(){
    unsigned int i = 2;
    teddy_machine *list, *mq;

    list = create_list(i);

    printMachines(list);

    mq = select_machine(list, i + 4);
    printf("%d\n", mq->id);

    list = remove_machine(list, mq);
    printMachines(list);

    mq = select_machine(list, i + 4);
    printf("%d\n", mq->id);

    list = remove_machine(list, mq);
    printMachines(list);


    destroy_list(list);


    return 0;
}
