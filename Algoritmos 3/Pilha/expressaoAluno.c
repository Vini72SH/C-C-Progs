/*---------------------------------------------------------
PROGRAMA: expressao.c

Programa que le uma expressao em notação Polonesa reversa e a avalia 
utilizando o TAD Pilha.  A expressão termina com a palavra "fim".

Exemplo:
21 3 * 11.36 89 * 25.7 5.3 * - / fim

Saida: Valor = 0.072014

Dicas:
-----------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char ItemPilha[50];
#include "itemString.h"
#include "pilha.h"

/* ----------------------------------------------------- */
/* Determina se uma string contem um operador (+ - * / )
   Entrada: string s
   Saida: 1 se s é um operador e 0, caso contrario */
int ehOperador( Item s ){
  if( eq(s, "/") ||  eq(s, "+") || eq(s, "-") || eq(s, "*") )
    return 1;
  else
    return 0;
}

/* ----------------------------------------------------- */
/* Avalia a operação op com os operadores s1 e s2 e coloca o
   resultado em res (todos os parâmetros são strings).
   DICA:
   use as funções
   atof( string): retorna um double representado na string
   sprintf( string, "%f", double ) converte o double em string
*/
void avalia( Item op, Item s1, Item s2, Item *res ){
    float op1, op2, result;

    op1 = atof(s1);
    op2 = atof(s2);

    if(eq(op, "/")){
        result = op1 / op2;
    }else if(eq(op, "*")){
        result = op1 * op2;
    }else if(eq(op, "+")){
        result = op1 + op2;
    }else{
        result = op1 - op2;
    }

    sprintf((*res), "%f", result);
}


/* ----------------------------------------------------- */
/* Programa: cria uma árvore binária que representa uma expressao
   aritmetica na notação Polonesa  e avalia a expressao.
*/
int main(int argc, char *argv[]){
    float s;
    Pilha pilha;
    Item v, s1, s2, res;

    criaPilha(&pilha);
    read(v);
    while(!eq(v, FIM)){
        if(!(ehOperador(v))){
          empilha(v, &pilha);
        }else{
            desempilha(&pilha, &s2);
            desempilha(&pilha, &s1);
            avalia(v, s1, s2, &res);
            empilha(res, &pilha);
        }
        read(v);
    }

    desempilha(&pilha, &res);
    write(res);
    printf("\n");

    return 0;
}