#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

char* strrchr2 (char *x, char *y) {
    char *p = NULL;
    int i = 0;
    
    if ( p != NULL ) {
        printf("Opa\n");
    }
    else {
        for ( i = strlen(x)-1; i >= 0; i--) {
            if ( x[i] == *y ) {
                p = &x[i];
                printf("Posicao do ultima ocorrencia: %d\n", i+1);
                return &x[i];
            }
        }
    }
    return NULL;
}

int main() {
    char *frase = (char*)malloc(200*sizeof(char)); 
    char *verif = (char*)malloc(sizeof(char));
    printf("Digite uma frase: ");
    scanf("%s", frase);
    printf("Digite um caractere a ser procurado: ");
    scanf(" %c", verif);
    
    char *pont = strrchr2(frase, verif);
    printf("Endereço de memoria: %p\nCaractere apontado: %c\n", pont, *pont);
    free(frase);
    free(verif);
    return 0;
}
