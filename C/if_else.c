#include <stdio.h>

int main (){

    printf ("Programa Testador de Alunos Aprovados por Média >= 7.0 \n");
    float nota1, nota2, nota3, media;
    printf ("Digite as notas nas três provas: ");
    scanf ("%f %f %f", &nota1, &nota2, &nota3);
    media = (nota1 + nota2 + nota3)/3;
    
    if (media < 40.00){
        printf ("Aluno Reprovado \n");
    }else if(media < 70.0){
        printf ("Exame Final \n");
        }else{
            printf ("Aluno aprovado \n");
        }
}