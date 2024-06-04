#include <stdlib.h>
#include <stdio.h>

//== ESTRUTURA

typedef struct {
	char titulo[33];
	char texto[513];
	char idade;

	struct noticia *proximo;
} noticia;

typedef struct {
	noticia *primeiro;
	noticia *ultimo;
} fila;

//== FILA

void adiciona(fila *sentinela, noticia *insercao){

	if (sentinela->primeiro == 0) sentinela->primeiro = insercao;
	else sentinela->ultimo->proximo = (struct noticia*) insercao;
	insercao->proximo = 0;
	sentinela->ultimo = insercao;
}

noticia* deleta(fila *sentinela){
	noticia *removido;

	if (sentinela->primeiro != 0){
		removido = sentinela->primeiro;
		sentinela->primeiro = (noticia*) sentinela->primeiro->proximo;
		if (sentinela->primeiro == 0) sentinela->ultimo = 0;
		return removido;
	}
	return 0;
}

//== JORNAL

void requisita(char *titulo, char *texto){
    getchar();
	printf("\nDigite o título: ");
	fgets(titulo, 33, stdin);
	printf("Digite o texto: ");
	fgets(texto, 513, stdin);
}

void envelhece(fila *sentinela){
	for (noticia *i = sentinela->primeiro; i != 0; i = (noticia*) i->proximo) i->idade++;
}

void limpa(fila *sentinela){
	while ((sentinela->primeiro != 0) && (sentinela->primeiro->idade > 3)) free(deleta(sentinela));
}

void nova(fila *bnews, fila *informes){
	noticia *nova_noticia = (noticia*) malloc(sizeof(noticia));
	int tipo;

	requisita(nova_noticia->titulo, nova_noticia->texto);
	nova_noticia->idade = 0;
	printf("Digite o tipo (0-BN; 1-Inf.): ");
	scanf("%d", &tipo);

	if (!tipo) adiciona(bnews, nova_noticia);
	else if (tipo == 1) adiciona(informes, nova_noticia);
	else {
		printf("O tipo selecionado é inválido!\n");
		free(nova_noticia);
		return;
	}
}

noticia* seleciona(fila *bnews, fila *informes){
	noticia *selecionada;

	selecionada = deleta(bnews);
	if (selecionada == 0) selecionada = deleta(informes);
	return selecionada;
}

void edicao(fila *bnews, fila *informes){
	noticia *selecionada;

	limpa(bnews);
	limpa(informes);

	selecionada = seleciona(bnews, informes);
	if (selecionada == 0){
		printf("Esta edição foi pulada por falta de notícias!\n");
		return;
	}

	printf("=======================================================\n");
	printf("%s\n\n", selecionada->titulo);
	printf("%s\n", selecionada->texto);

	free(selecionada);
	selecionada = seleciona(bnews, informes);
	if (selecionada != 0){
		printf("\n==\n%s\n\n", selecionada->titulo);
		printf("%s\n", selecionada->texto);
		free(selecionada);
	}
	printf("=======================================================\n");

	envelhece(bnews);
	envelhece(informes);
}


int main(){
	fila bnews, informes;
	int opcao;

	bnews.primeiro = 0;
	bnews.ultimo = 0;
	informes.primeiro = 0;
	informes.ultimo = 0;

	while(1){
		printf("\n============= MENU =============\n");
		printf("(1): Nova notícia\n");
		printf("(2): Fechar edição\n");
		printf("Opção: ");
		scanf("%d", &opcao);

		if (opcao == 1) nova(&bnews, &informes);
		else if (opcao == 2) edicao(&bnews, &informes);
		else printf("\nA opção selecionada é inválida!\n");
	}

	return 0;
}
