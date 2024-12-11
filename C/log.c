#include <stdio.h>
#include <math.h>

double expo(double x, double n) {
    if (n <= 0.0) {
        return 1.0;
    }
    if (n == 1.0) {
        return x;
    }

    return x * expo(x, n - 1);
}

double lg(double x, double e, double a, double b) {
    double m, q;
    
    do {
        m = (a + b) / 2.0;
        q = expo(2, m);
        
        if (fabs(b - a) <= e || q == x) {
            return m;
        }
        
        if (q > x) {
            b = m;
        } else {
            a = m;
        }
    } while (1);
}


int main() {
    double x, e, a, b, r;

    scanf("%lf", &x);

    e = 0.000000001;
    a = 0.0;
    b = x;

    r = lg(x, e, a, b);

    printf("O log %.2lf é: %.3lf\n", x, r);

    return 0;
}

