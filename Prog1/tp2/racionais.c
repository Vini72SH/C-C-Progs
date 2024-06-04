#include "racionais.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

/* retorna um numero aleatorio entre min e max, inclusive. */
int aleat (int min, int max){

	return (rand() % (max-min+1))+min;

}

/* Maximo Divisor Comum entre a e b*/
int mdc(int a, int b){
	/* calcula o mdc pelo metodo de Euclides */
	int resto;

	resto = a % b;
	while (resto != 0){
		a = b;
		b = resto;
		resto = a % b;
	}

	return b;

}

/* Minimo Multiplo Comum entre a e b */
int mmc (int a, int b){
	/* mmc = (a * b) / mdc (a, b)*/

	return ((a * b) / mdc (a, b));

}

/* Cria um numero racional com base nas informacoes dos parametros. */
struct racional cria_r (int numerador, int denominador){
    struct racional r;

    r.valido = 1;
    /*Numerador e Denominador são associados corretamente*/
    r.num = numerador; 
    r.den = denominador;
    /*Retorna o número racional criado*/

    if (r.den == 0)
        r.valido = 0;

    return r;
}

/* Retorna um numero racional aleatorio na forma simplificada.
 * O numerador e o denominador devem ser inteiros entre -max e max.
 * O racional deve conter a informacao se ele eh valido ou nao. */
struct racional sorteia_r (int max){
	struct racional r;
	int num, den;
	
	/*Sorteia o numerador e numerador*/
	num = aleat(-max, max);
	den = aleat(-max, max);

	/*Cria o racional r*/
	r = cria_r (num, den);	

	/*Define se o racional é inválido e 
	retorna o racional*/
	if (r.valido == 0){

		return r;
	}

	simplifica_r (&r);
	
	return r;
}

/* Retorna o numerador de um racional */
int numerador_r (struct racional r){

	return r.num;

}

/* Retorna o denominador de um racional */
int denominador_r (struct racional r){

	return r.den;

}

/* Retorna 1 se o racional r eh valido ou 0 caso contrario
 * Um racional eh invalido se o denominador for nulo */
int valido_r (struct racional r){

	if (r.valido == 0){
		return 0;
	}

	return 1;

}

void imprime_r (struct racional r){
    if (r.valido == 0){
    /*Imprime que o racional é invalido.*/
        printf ("INVALIDO");

    }else if ((r.num == 0) || (r.den == 1)){
    /*Retorna 0 caso numerador seja 0 e retorna
    o numerador caso o denominador seja 1*/
        printf ("%d", r.num);

    }else if (r.num == r.den){
    /*Retorna 1 caso denominador e numerador
    sejam iguais.*/
        printf ("%d", 1);

    }else{
        /*Imprime o racional simplificado.*/
        printf ("%d/%d", r.num, r.den);
    }
}

/* Retorna -1 se r1 < r2; 0 se r1 = r2; 1 se r1 > r2 */
int compara_r (struct racional r1, struct racional r2){
    int mdc_r = mdc (r1.den, r2.den);
    /*Atribui o mdc aos denominadores*/
    r1.den = mdc_r;
    r2.den = mdc_r;

    /*Escreve ambos os racionais com o mesmo den*/
    r1.num = (mdc_r / r1.den)*r1.num;
    r2.num = (mdc_r / r2.den)*r2.num;

    /*Faz as impressões corretas.*/
    if (r1.num > r2.num){
        return 1;
    
    }else if (r1.num == r2.num){
        return 0;
    
    }else if (r1.num < r2.num){
        return -1;
    
    }

    return 0;
}

int simplifica_r (struct racional *r){
    int mdc_r, num, den;
    
    /*Retorna 0 caso o racional seja inválido*/
    if (r->valido == 0){
        return 0;
    }

    num = r->num;
    den = r->den;

    mdc_r = mdc (num, den);

    /*Migra o sinal negativo para o numerador e 
    transforma em racional positivo caso numerador e denominador sejam negativos. */
    if(((den < 0) && (num > 0)) || ((den < 0) && (num < 0))){
        den = den * (-1);
        num = num * (-1);
    }

    /*Simplifica atráves da divisão pelo mdc de ambos os números.*/
    r->num = (num / abs(mdc_r));
    r->den = (den / abs(mdc_r));

    /*Retorna 1 caso a simplificação seja efetuada 
    com sucesso*/
    return 1;
}

/* Retorna a soma dos racionais r1 e r2 no parametro *r3 e 
 * Retorna 1 se a operacao foi bem sucedida ou 0 caso algum dentre
 * r1, r2, r3 forem invalidos */
int soma_r (struct racional r1, struct racional r2, struct racional *r3){
	int num, den;

    den = mmc (r1.den, r2.den);
    num = ((den / r1.den) * r1. num) + ((den / r2.den) * r2.num);

    r3->num = num;
    r3->den = den;

    /*Retorna 0 caso um dos racionais seja inválido*/
    if (!(r1.valido) || !(r2.valido) || (r3->den == 0)){
        r3->valido = 0;
        return 0;
    }

    r3->valido = 1;

    /*Operação bem-sucedida*/
    return 1;
}

/* Retorna a subtracao dos racionais r1 e r2 no parametro *r3 e
 * Retorna 1 se a operacao foi bem sucedida ou 0 caso algum dentre
 * r1, r2, r3 forem invalidos */
int subtrai_r (struct racional r1, struct racional r2, struct racional *r3){
    int num, den;

    den = mmc (r1.den, r2.den);
    num = ((den / r1.den) * r1. num) - ((den / r2.den) * r2.num);

    r3->num = num;
    r3->den = den;

    /*Retorna 0 caso um dos racionais seja inválido*/
    if (!(r1.valido) || !(r2.valido) || (r3->den == 0)){
        r3->valido = 0;
        return 0;
    }

    r3->valido = 1;

	/*Operação bem-sucedida*/
    return 1;
}

/* Retorna a multiplicacao dos racionais r1 e r2 no parametro *r3 e
 * Retorna 1 se a operacao foi bem sucedida ou 0 caso algum dentre
 * r1, r2, r3 forem invalidos */
int multiplica_r (struct racional r1, struct racional r2, struct racional *r3){
	r3->num = r1.num * r2.num;
    r3->den = r1.den * r2.den;

    /*Retorna 0 caso um dos racionais seja inválido*/
    if (!(r1.valido) || !(r2.valido) || (r3->den == 0)){
        r3->valido = 0;
        return 0;
    }

    r3->valido = 1;

    /*Operação bem-sucedida*/
    return 1;
}

/* Retorna a divisao dos racionais r1 e r2 no parametro *r3 e
 * Retorna 1 se a operacao foi bem sucedida ou 0 caso algum dentre
 * r1, r2, r3 forem invalidos */
int divide_r (struct racional r1, struct racional r2, struct racional *r3){
	int aux;
    aux = r2.den;
    r2.den = r2.num;
    r2.num = aux;

    multiplica_r (r1, r2, r3);

    /*Retorna 0 caso um dos racionais seja inválido*/
    if (!(r1.valido) || !(r2.valido) || (r3->den == 0)){
        r3->valido = 0;
        return 0;
    }

    r3->valido = 1;

    /*Operação bem-sucedida*/
    return 1;
}