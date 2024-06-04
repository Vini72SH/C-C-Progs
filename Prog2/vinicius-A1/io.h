#define LINESIZE 1024

typedef struct atributos{
    char *nome;
    char *sexo;
    char *idade;
    char *profis;
    char *salario;
    char *EC;
}atributos;

/* Informa os campos e retorna a quantidade de
 * variáveis. */
int le_atributos(FILE* csv);

/* Retorna a quantidade de atributos. */
int conta_linhas(FILE *csv);

/* Processa os dados do arquivo.
 * retorna um ponteiro para um vetor. */
atributos *processa_dados(FILE *csv, int tam);
    
/* Imprime os dados processados. */
void imprime_dados(atributos *infos, int tam);

/* Libera toda a memória alocada.*/
void libera_mem(atributos *v, int tam);