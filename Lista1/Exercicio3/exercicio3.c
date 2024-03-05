#include <stdio.h>
#include <math.h>
#include <string.h>

char* strrchr2 (char x[], char y) {
    char *p = NULL;
    int i = 0;
    
    if ( p != NULL ) {
        printf("Opa\n");
    }
    else {
        for ( i = strlen(x)-1; i >= 0; i--) {
            if ( x[i] == y ) {
                p = &x[i];
                return &x[i];
            }
        }
    }
    return NULL;
}

int main() {
    char frase[200]; 
    char verif;
    printf("Digite uma frase: ");
    scanf("%s", frase);
    printf("Digite um caractere a ser procurado: ");
    scanf(" %c", &verif);
    
    char *pont;

    pont = strrchr2(frase, verif);
    printf("Endereço de memoria: %p\nCaractere apontado: %c\n", pont, *pont);

    return 0;
}
