#include <stdio.h>
#include <math.h>
#include <string.h>

/*int valorChar (char x) {
    printf("%d refere-se ao numero: %d\n", x, (int)(x-48));
    switch (x) {
        case '0':
            return 0;
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;
        case '8':
            return 8;
        case '9':
            return 9;
    }
}*/

double atof2 (char x[]) {
    double value = 0;
    int i = 0, checkDot = 0, k=0;
    
    for (i=0; i<strlen(x); i++) {
        if (x[i] == '.') {
            checkDot = i;
        }
    }
    
    if (checkDot == 0) {
        for ( i=0; i<strlen(x); i++) {
            value += (int)(x[strlen(x)-i-1]-48) * pow(10,i);
            //value += valorChar(x[strlen(x)-i-1]) * pow(10,i);
        }
    }
    else {
        for ( i = 0; i<checkDot; i++) {
            value += (int)(x[checkDot-i-1]-48) * pow(10, i);
            //value += valorChar(x[checkDot-i-1]) * pow(10, i);
        }
        
        for ( i = checkDot+1; i < strlen(x); i++) {
            value += (int)(x[i]-48) * pow(10, (checkDot-i));
            //value += valorChar(x[i]) * pow(10, (checkDot-i));
        }
    }
    return value;
}

int main() {
    char valor[200];
    double value = 0;
    printf("Entre com o valor double: ");
    scanf("%s", valor);
    value = atof2(valor);
    
    printf("Valor final: %lf\n", value);
    printf("Manipulação de valor matematico: %lf\n", value*2);
    
    return 0;
}

