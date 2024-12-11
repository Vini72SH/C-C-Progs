#include <stdio.h>
#include <stdlib.h>

int main () {
    int lin = 5;
    int valorAcima;
    int valorNovo;
    int pesos[] = {0, 5, 2, 7, 3};
    int valores[] = {0, 10, 10, 5, 20};
    int capacidadeDaMochila = 10;
    int col = capacidadeDaMochila + 1;

    int **matrix = malloc(lin * sizeof(int *));
    if (matrix == NULL) {
        printf("Não foi possível alocar a memória!\n");
        exit(1);
    }

    for (int i = 0; i < lin; ++i) {
        matrix[i] = malloc(col * sizeof(int));
        if (matrix[i] == NULL) {
            printf("Não foi possível alocar a memória!\n");
            exit(1);
        }
    }

    for (int i = 0; i < lin; ++i) {
        for (int j = 0; j < col; ++j) {
            matrix[i][j] = 0;
        }
    }

    printf("Valores e Pesos:\n");
    for (int i = 0; i < lin; ++i) {
        printf("Valor: %d Peso: %d\n", valores[i], pesos[i]);
    }

    for (int i = 1; i < lin; ++i) {
        for (int j = 1; j < col; ++j) {
            if (j >= pesos[i]) {
                valorAcima = matrix[i - 1][j];
                valorNovo = valores[i] + matrix[i - 1][j - pesos[i]];
                if (valorNovo >= valorAcima) {
                    matrix[i][j] = valorNovo;
                } else {
                    matrix[i][j] = valorAcima;
                }
            } else {
                matrix[i][j] = matrix[i - 1][j];
            }
        }
    }

    for (int i = 0; i < lin; ++i) {
        for (int j = 0; j < col; ++j) {
            printf("%3d ", matrix[i][j]);
        }
        printf("\n");
    }

    printf("Maior valor obtido: %d\n", matrix[lin - 1][col- 1]);

    // Liberando memória
    for (int i = 0; i < lin; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}