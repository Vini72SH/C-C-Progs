#include <iostream>
#include "list.hpp"

#define FIM 0

int main(){
    int n;
    Lista *l = new Lista();

    printf("Inserção de Valores: ");
    scanf("%d", &n);
    while(n != FIM){
        l->insereLista(n);
        scanf("%d", &n);
    }

    l->imprimeLista(l);

    printf("Remoção de Valores: ");
    scanf("%d", &n);
    while(n != FIM){
        l->removeLista(n);
        scanf("%d", &n);
    }

    l->imprimeLista(l);

    delete l;
}