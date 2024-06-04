#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "racionais.h"

int main (){
    srand (time(0)); /*Inicializa a função aleatória*/
    int i, n, max;

    /*Leitura de N e Max*/
    scanf ("%d", &n);
    scanf ("%d", &max);

    for (i = 1; i <= n; i++){
        struct racional r1, r2, soma, sub, mult, div;
        
        /*Imprime o indíce da linha*/
        printf ("%d: ", i);

        /*Sorteia dois racionais*/
        r1 = sorteia_r (max);
        r2 = sorteia_r (max);

        /*Imprime os racionais sorteados*/
        imprime_r (r1);
        printf (" ");
        imprime_r (r2);
        printf (" ");

        /*Imprime a mensagem caso R1 ou R2 sejam
        racionais invalidos.*/
        if (!(valido_r (r1)) || (!(valido_r(r2)))){
            printf ("NUMERO INVALIDO\n");
            return 1;
        }

        /*Calcula a soma dos racionais*/
        soma = soma_r (r1, r2);

        /*Calcula a subtração dos racionais*/
        sub = subtrai_r (r1, r2);

        /*Calcula a multiplicação dos racionais*/
        mult = multiplica_r (r1, r2);

        /*Calcula a divisão dos racionais*/
        div = divide_r (r1, r2);

        /*Imprime a mensagem caso a divisão seja inválida.*/
        if (!(valido_r (div))){
            printf ("NUMERO INVALIDO\n");
            return 1;
        }

        /*Impressão das operações com racionais*/
        imprime_r (soma);
        printf(" ");
        imprime_r (sub);
        printf (" ");
        imprime_r (mult);
        printf (" ");
        imprime_r (div);
        printf ("\n");

    }

    return 0;

}
