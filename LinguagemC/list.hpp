#ifndef __LISTA__
#define __LISTA__

#include <iostream>

class Nodo{
    public:
        int item;
        Nodo *prox;

        // Construtor
        Nodo() : item(0), prox(nullptr) {}
};

class Lista{
    private:
        int tam;
        Nodo *prime;
        Nodo *ult;
    
    public:
        // Construtor
        Lista() : tam(0), prime(nullptr), ult(nullptr) {}

        // Destrutor
        ~Lista();

        // Funções Principais
        int insereLista(int i);
        int removeLista(int i);
        Nodo* buscaLista(int i); 
        int listaVazia(Lista *l);
        void imprimeLista(Lista *l);
};

#endif