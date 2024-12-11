#include <stdio.h>
#include <math.h>

double raizCubica(double x, double e, double a, double b){
    double m, q;

    m = (a + b)/2.0;
    q = m*m*m;

    if(fabs(b - a) <= e || q == x){
        return m;
    }

    if(q > x){
        return raizCubica(x, e, a, m);
    }

    return raizCubica(x, e, m, b);
}

double raizQuadrada(double x, double e, double a, double b) {
    double m = (a + b) / 2.0;
    double q = m * m;

    if (fabs(b - a) <= e || q == x) {
        return m;
    }

    if (q > x) {
        return raizQuadrada(x, e, a, m);
    }

    return raizQuadrada(x, e, m, b);
}

int main() {
    double x, resultado, rc;

    // Entrada do valor 'x' e da precisão 'e'
    printf("Digite o valor de x: ");
    scanf("%lf", &x);

    // Limites iniciais [a, b] (geralmente 0 e x)
    double a = 0.0;
    double b = x;
    double e = 0.0000000001;
    if (x < 0) {
        printf("Não é possível calcular a raiz quadrada de um número negativo.\n");
    } else {
        resultado = raizQuadrada(x, e, a, b);
        printf("A raiz quadrada de %.2lf com precisão %.10lf é aproximadamente %.10lf\n", x, e, resultado);
        rc = raizCubica(x, e, a, b);
        printf("Raiz Cúbica: %.10lf\n", rc);
    }


    return 0;
}
