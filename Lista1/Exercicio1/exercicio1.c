#include <stdio.h>
#include <math.h>

int fatorial (int x) {
    int res=1;
    for ( x ; x > 1 ; x--) {
        res *= x;
    }
    return res;
}

double seno (double x, int qt) {
    int i=1, k=0;
    double ans=0;
    for ( i = 1; i <= qt; i+=2) {
        if ( k % 2 == 0 ) {
            //printf("Positivo + (%lf ^ %d)/%d! = %lf / %d = %lf\n", x, i, i, pow(x,i), fatorial(i), (pow(x,i)/fatorial(i)));
            ans += pow(x, i)/fatorial(i);
        }
        else {
            //printf("Negativo - (%lf ^ %d)/%d! = %lf / %d = %lf\n", x, i, i, pow(x,i), fatorial(i), (pow(x,i)/fatorial(i)));
            ans -= pow(x, i)/fatorial(i);
        }
        k++;
        //printf("Valor de ans = %lf\n", ans);
    }
    return ans;
}

int main () {
    double angulo = 0.0;
    int taylor = 0;
    printf("Defina o valor de X: ");
    scanf("%lf", &angulo);
    printf("Quantidade de operação da serie de taylor: ");
    scanf("%d", &taylor);
    
    printf("Valor de ans = %lf\n", seno(angulo, taylor));
    
    return 0;
}
