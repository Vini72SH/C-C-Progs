#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct racional{
    unsigned short int valido; /* um racional eh invalido se den == 0 */
    int num;                   /* numerador do racional               */
    int den;                   /* denominador do racional             */
};

int aleat (int min, int max){
	/*srand(time(0)) na main*/
	return (rand() % (max+1-min));
}

int mdc(int a, int b){
	/* Maximo Divisor Comum entre a e b      */
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

int mmc (int a, int b){
	/* mmc = (a * b) / mdc (a, b)*/
	return ((a*b) / mdc (a, b));
}

struct racional simplifica_r (struct racional r){
	int mdc_r;
	mdc_r = mdc(r.num, r.den);

	/*Retorna o racional caso o numerador seja 0*/
	if (r.num == 0){
		return r;
	}

	/*Migra o sinal negativo para o numerador ou 
	transforma em racional positivo caso numerador e denominador sejam negativos. */
	if(((r.den < 0) && (r.num > 0)) || ((r.den < 0) && (r.num < 0))){
		r.den = r.den * (-1);
		r.num = r.num * (-1);
	}

	r.num = r.num / abs(mdc_r);
	r.den = r.den / abs(mdc_r);

	return r;
}

struct racional cria_r (int numerador, int denominador){
	struct racional r;
	r.num = numerador;
	r.den = denominador;
	return r;
}

/* Retorna um numero racional aleatorio na forma simplificada.
 * O numerador e o denominador devem ser inteiros entre 0 e n.
 * O racional deve conter a informacao se ele eh valido ou nao */
struct racional sorteia_r (int n){
	struct racional r;
	int num, den;

	num = aleat(0, n);
	den = aleat(0, n);
	r = cria_r (num, den);

	if ((r.den == 0))
		return r;

	r = simplifica_r (r);
	return r;
}

int valido_r (struct racional r){
	if ((r.den != 0))
		return 1;
	return 0;
}

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

/* Retorna a soma dos racionais r1 e r2.
 * Quem chama esta funcao deve garantir que os racionais r1 e r2 sao validos */
struct racional soma_r (struct racional r1, struct racional r2){
	struct racional r;

	r.den = mmc (r1.den, r2.den);
	r.num = ((r.den / r1.den) * r1. num) + ((r.den / r2.den) * r2.num);

	return r;
}

struct racional subtrai_r (struct racional r1, struct racional r2){
	/* Retorna a subtracao dos racionais r1 e r2*/
	struct racional r;

	r.den = mmc (r1.den, r2.den);
	/*Calcula o MMC dos denominadores.*/
	r.num = ((r.den / r1.den) * r1. num) - ((r.den / r2.den) * r2.num);
	/*Divide o novo numerador pelo antigo e multiplica pelo numerador
	somando com o mesmo procedimento do outro racional.*/

	return r;
}

/* Retorna a multiplicacao dos racionais r1 e r2.
 * Quem chama esta funcao deve garantir que os racionais r1 e r2 sao validos */
struct racional multiplica_r (struct racional r1, struct racional r2){
	struct racional r;

	r.num = r1.num * r2.num;
	r.den = r1.den * r2.den;
	
	return r;
}

/* Retorna a divisao dos racionais r1 e r2.
 * Quem chama esta funcao deve:
     - garantir que os racionais r1 e r2 sao validos
     - em seguida deve garantir que o racional retornado tambem seja valido */
struct racional divide_r (struct racional r1, struct racional r2){
	int aux;
	struct racional r;

	aux = r2.den;
	r2.den = r2.num;
	r2.num = aux;

	r = multiplica_r (r1, r2);

	return r;	
}


int main (){
	srand (time(0));
	struct racional r1, r2, mult, div, soma, sub;

	r1 = sorteia_r (29);
	r2 = sorteia_r (29);

	soma = soma_r (r1, r2);
	sub = subtrai_r (r1, r2);
	mult = multiplica_r (r1, r2);
	div = divide_r (r1, r2);

	imprime_r (r1);
	printf (" ");
	imprime_r (r2);
	printf ("\n");
	imprime_r (soma);
	printf ("\n");
	imprime_r (sub);
	printf ("\n");
	imprime_r (mult);
	printf ("\n");
	imprime_r (div);
	printf ("\n");

	return 0;

}