#include "list.hpp"

Lista::~Lista(){
    Nodo *aux, *aux2;

    aux = prime;
    while(aux != nullptr){
        aux2 = aux->prox;
        delete aux;
        aux = aux2;
    }

    prime = nullptr;
    ult = nullptr;
    tam = 0;
}

// Funções Principais
int Lista::insereLista(int i){
    Nodo *no = new Nodo();
    no->item = i;

    if(prime == nullptr){
        prime = no;
        ult = no;
        return 1;
    }

    ult->prox = no;
    ult = no;
    tam++;

    return 1;
}

int Lista::removeLista(int i){
    Nodo *aux, *aux2;

    aux = prime;
    if((aux != nullptr) && (aux->item == i)){
        aux2 = aux;
    }else{
        while((aux->prox != nullptr) && (aux->prox->item != i)){
            aux = aux->prox;
        }
        aux2 = aux->prox;
    }

    if(!(aux2)) return 0;

    if(aux2 == prime)
        prime = aux2->prox;
    else
        aux->prox = aux2->prox;

    if(aux2 == ult)
        ult = nullptr;

    delete aux2;

    tam--;
    
    return 1;
}

Nodo* Lista::buscaLista(int i){
    Nodo *aux;

    aux = prime;
    while(aux != nullptr){
        if(aux->item == i)
            return aux;
        aux = aux->prox;
    }

    return nullptr;
}

int Lista::listaVazia(Lista *l){
    if(l == nullptr)
        return 1;

    if(!(l->tam))
        return 1;
    
    return 0;
}

void Lista::imprimeLista(Lista *l){
    if(l == nullptr)
        return;

    printf("\n[ ");

    Nodo *aux;
    aux = l->prime;
    while(aux != nullptr){
        printf("%d ", aux->item);
        aux = aux->prox;
    }

    printf("]\n");
}