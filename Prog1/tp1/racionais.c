#include "racionais.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

/* retorna um numero aleatorio entre min e max, inclusive.*/
int aleat (int min, int max){
	
	return (rand() % (max+1-min));

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

/*Simplifica o racional conforme as propriedades matématicas.*/
struct racional simplifica_r (struct racional r){
	int mdc_r;
	mdc_r = mdc (r.num, r.den);

	/*Retorna o racional caso o numerador seja 0*/
	if (r.num == 0){
		return r;
	}

	/*Migra o sinal negativo para o numerador e 
	transforma em racional positivo caso numerador e denominador sejam negativos. */
	if(((r.den < 0) && (r.num > 0)) || ((r.den < 0) && (r.num < 0))){
		r.den = r.den * (-1);
		r.num = r.num * (-1);
	}

	/*Simplifica atráves da divisão pelo mdc de ambos os números.*/
	r.num = r.num / abs(mdc_r);
	r.den = r.den / abs(mdc_r);

	return r;
}

/* Cria um numero racional com base nas informacoes dos parametros. */
struct racional cria_r (int numerador, int denominador){
	struct racional r;

	/*Numerador e Denominador são associados corretamente*/
	r.num = numerador; 
	r.den = denominador;
	/*Retorna o número racional criado*/

	return r;
}

/* Retorna um numero racional aleatorio na forma simplificada.*/
struct racional sorteia_r (int n){
	struct racional r;
	int num, den;
	
	/*Sorteia o numerador e numerador*/
	num = aleat(0, n);
	den = aleat(0, n);
	/*Cria o racional r*/
	r = cria_r (num, den);

	/*Retorna o racional aleatório caso seja inválido*/
	if ((r.den == 0))
		return r;

	r = simplifica_r (r);
	
	return r;	
}

/*Imprime um racional*/
void imprime_r (struct racional r){
	/*Evita a divisão por zero, simplificando
	apenas racionais cujo den não é zero.*/
	if (r.den != 0){
		r = simplifica_r (r);
	}

	if (r.den == 0){
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

	return;
}

/* Retorna 1 se o racional r eh valido ou 0 caso contrario
 * Um racional eh invalido se o denominador for nulo */
int valido_r (struct racional r){
	if (r.den == 0)
		return 0;
	return 1;
}

/* Retorna a soma dos racionais r1 e r2.*/
struct racional soma_r (struct racional r1, struct racional r2){
	
	struct racional r;

	r.den = mmc (r1.den, r2.den);
	/*Calcula o MMC dos denominadores.*/
	r.num = ((r.den / r1.den) * r1. num) + ((r.den / r2.den) * r2.num);
	/*Divide o novo numerador pelo antigo e multiplica pelo numerador
	somando com o mesmo procedimento do outro racional.*/

	return r;
}

/* Retorna a subtracao dos racionais r1 e r2*/
struct racional subtrai_r (struct racional r1, struct racional r2){
	
	struct racional r;

	r.den = mmc (r1.den, r2.den);
	/*Calcula o MMC dos denominadores.*/
	r.num = ((r.den / r1.den) * r1. num) - ((r.den / r2.den) * r2.num);
	/*Divide o novo numerador pelo antigo e multiplica pelo numerador
	subtraindo com o mesmo procedimento do outro racional.*/

	return r;
}

/* Retorna a multiplicacao dos racionais r1 e r2.*/
struct racional multiplica_r (struct racional r1, struct racional r2){
	
	struct racional r;
	
	/*Para multiplicar racionais, basta multiplicar os numeradores e os 
	denominadores de um racional pelos numeradores e denominadores do outro.*/
	r.num = r1.num * r2.num;
	r.den = r1.den * r2.den;

	return r;
}

/* Retorna a divisao dos racionais r1 e r2. */
struct racional divide_r (struct racional r1, struct racional r2){
	
	int aux;
	struct racional r;

	/*Troca o numerador com o denominador*/
	aux = r2.den;
	r2.den = r2.num;
	r2.num = aux;

	/*Multiplica o primeiro racional pelo inverso
	do segundo racional, efetuando a divisão*/
	r = multiplica_r (r1, r2);

	return r;
}
