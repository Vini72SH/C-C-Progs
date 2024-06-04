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

    if(!machines) return 0;

    list = malloc(sizeof(teddy_machine));
    if(!list) return NULL;

    aux = list;
    list->id = machines;
    list->probability = 5;
    list->next = NULL;

    for(i = 0; i < machines - 1; i++){
        list->previous = malloc(sizeof(teddy_machine));
        if(!list->previous) return 0;
        list->previous->id = i;
        list->previous->probability = 5;
        list->previous->next = list;
        list = list->previous;
    }

    list->previous = aux;
    aux->next = list;

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

int empty_list(teddy_machine *list){

    if((list == NULL) || ((list->next == NULL) && (list->previous == NULL))){
        return 1;
    }

    return 0;
}

void destroy_list (teddy_machine *list){
    teddy_machine *aux, *aux2;

    if(list == NULL){
        return;
    }

    aux = list->next;
    while(aux != list){
        aux2 = aux;
        aux = aux->next;
        free(aux2);
    }

    free(list);
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

/* Att Function */

void att_machines(teddy_machine **list, unsigned int places, unsigned int attempt){
    teddy_machine *mach;

    mach = select_machine(*list, places);
    print_attempt(mach, attempt);

    if(attempt <= mach->probability){
        *list = remove_machine(*list, mach);
    }else{
        mach->probability += 2;
    }
}

/* Main function */

int main(int argc, char *argv[]){
    unsigned int machines, rounds, seed;
    int rv = 0;

    if (argc != 4) rv = -1;
    else {
        machines = atoi(argv[1]);
        if (!machines) rv = -2;
        else {
            rounds = atoi(argv[2]);
            if (!rounds) rv = -3;
            else {
                seed = atoi(argv[3]);
                if (!seed) rv = -4;
            }
        }
    }

    if (rv){
        printf("USO: main [NR. DE MAQUINAS] [NR. DE RODADAS] [SEMENTE DE RAND.]\n");
        return rv;
    }

    teddy_machine *list = create_list(machines);
    srand(seed);

    unsigned int machine_place, machine_attempt;
    for (unsigned int r = 0; r < rounds; r++){
        printf("\n============================ ROUND %u ============================\n", r+1);
        machine_place = get_place(machines); /* Define a localização da máquina da rodada, não considera máquinas sem urso */
        machine_attempt = get_attempt(); /* Define a tentativa da rodada; se for menor ou igual à probabilidade da máquina selecionada, o urso foi pego */

        att_machines(&list, machine_place, machine_attempt);

        print_available_machines(list);
        printf("==================================================================\n");
        
        if(empty_list(list)){
            break;
        }
    }

    destroy_list(list);

    return 0;
}
