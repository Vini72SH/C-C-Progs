#include <stdio.h>

int main (){
	printf ("Programa de Structs\n");
	struct notas_de_aluno{
		float nota1;
		float nota2;
		float nota3;
		float media;
	};
	struct notas_de_aluno aluno;
	printf ("Digite a nota na primeira prova: ");
	scanf ("%f", &aluno.nota1);
	printf ("Digite a nota na segunda prova: ");
	scanf ("%f", &aluno.nota2);
	printf ("Digite a nota na terceira prova: ");
	scanf ("%f", &aluno.nota3);
	aluno.media = (aluno.nota1 + aluno.nota2 + aluno.nota3) / 3;
	printf ("A média final deste aluno é de: %.2f\n", aluno.media);
	return 0;
}