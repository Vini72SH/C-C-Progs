#include "racionais.h"
#include <stdlib.h>
#include <stdio.h>

int mdc (int a, int b){
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

	return ((a * b)/ mdc (a, b));

}

/*Retorna um ponteiro que aponta para um racional.*/
struct racional *cria_r (long int numerador, long int denominador){
	struct racional *r;

	r = (struct racional *)(malloc (sizeof(struct racional)));
	if (r == 0){

		return NULL;
	}

	r->num = numerador;
	r->den = denominador;

	simplifica_r (r);

	return r;
}

void destroi_r (struct racional *r){

	free(r);

}

int numerador_r (struct racional *r, long int *num){
	if (!(valido_r (r)))
		return 0;

	*(num) = r->num;

	return 1;
}

int denominador_r (struct racional *r, long int *den){
	if (!(valido_r (r)))
		return 0;

	*(den) = r->den;

	return 1;
}

int valido_r (struct racional *r){
	if ((r == NULL) || (r->den == 0)){
		return 0;
	}

	return 1;
}

void imprime_r (struct racional *r){
	if (r == NULL){
		printf("NULO");

		return;
	}

	if (!(valido_r(r))){
		printf ("INVALIDO");

		return;
	}

	simplifica_r (r);

	if ((r->num == 0) || (r->den == 1)){
		printf ("%ld", r->num);

		return;
	}

	printf ("%ld/%ld", r->num, r->den);

}

int compara_r (struct racional *r1, struct racional *r2){
	long int num1, num2;
	long int mmc_r = mmc (r1->den, r2->den);	

	if (!(valido_r(r1) && valido_r(r2))){
		return -2;
	}

	num1 = ((mmc_r/r1->den)*r1->num);
	num2 = ((mmc_r/r2->den)*r2->num);

	/*Compara os racionais com mesmo den.*/
    if (num1 > num2){
      return 1;
    }

    if (num1 < num2){
      return -1;
    }

   return 0;
}

/*Simplifica um racional.*/
int simplifica_r (struct racional *r){
	long int num, den, mdc_r;

	num = r->num;
	den = r->den;

	if (!(valido_r (r))){
		return 0;
	}

	num = r->num;
	den = r->den;
	mdc_r = mdc (r->num, r->den);

	if (((num < 0) && (den < 0)) || ((den < 0) && (num > 0))){
		num = num * (-1);
		den = den * (-1);
	}

	r->num = (num / labs(mdc_r));
	r->den = (den / labs(mdc_r));

	return 1;
}

/*Soma e simplifica dois racionais.*/
int soma_r (struct racional *r1, struct racional *r2, struct racional *r3){
	long int mmc_r;

	if (!(valido_r(r1) && valido_r(r2))){
		return 0;
	}

	mmc_r = mmc (r1->den, r2->den);

	r3->num = ((mmc_r / r1->den)*r1->num) + ((mmc_r / r2->den)*r2->num);
	r3->den = mmc_r;

	simplifica_r (r3);

	return 1;
}

/*Subtrai e simplifica dois racionais.*/
int subtrai_r (struct racional *r1, struct racional *r2, struct racional *r3){
	long int mmc_r;

	if (!(valido_r(r1) && valido_r(r2))){
		return 0;
	}

	mmc_r = mmc (r1->den, r2->den);

	r3->num = ((mmc_r / r1->den)*r1->num) - ((mmc_r / r2->den)*r2->num);
	r3->den = mmc_r;

	simplifica_r (r3);

	return 1;
}

/*Multiplica e simplifica dois racionais.*/
int multiplica_r (struct racional *r1, struct racional *r2, struct racional *r3){
	if (!(valido_r(r1) || !(valido_r(r2)))){

		return 0;
	}

	r3->num = (r1->num * r2->num);
	r3->den = (r1->den * r2->den);

	simplifica_r (r3);

	return 1;
}

/*Divide e simplifica dois racionais.*/
int divide_r (struct racional *r1, struct racional *r2, struct racional *r3){
	if (!(valido_r(r1) || !(valido_r(r2)))){

		return 0;
	}

	r3->num = (r1->num * r2->den);
	r3->den = (r1->den * r2->num);

	simplifica_r (r3);

	return 1;
}