#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int verifyListInt (const char *s) {
    int i, k=0, contador=0;

    for (i=0; s[i] != '\0'; i++){
        if ((s[i] > 57 || s[i] < 48) && s[i] != ' ') {
            printf("String Invalida\n");
            return 0;
        }

        if ( s[i] == ' ' ) {
            k = 0;
            continue;
        }
        else {
            if ( k == 0 ) {
                k = 1;
                contador++;
            }
        }
    }
    //printf("Contador Vetor: %d\n", contador);
    return contador;
}

int* splitInt (const char *s, int *tamanho) {
    *tamanho = verifyListInt(s);

    if ( *tamanho == 0 ) {
        printf("Vetor vazio devido a falha\n");
        return 0;
    }

    int i, k=0, aux=0;
    int *vetor = (int*)malloc(*tamanho*sizeof(int));
    //vetor = (int*)malloc(*tamanho*sizeof(int));

    for (i = 0; s[i] != '\0'; i++) {

        if (s[i] == ' ') {
            k = 0;
            //printf("Espaço\n");
            continue;
        }
        else {
            //printf("Numero %d\n", (int)(s[i]-48));
            vetor[aux] = (int)(s[i]-48);
            while ( s[i+k+1] != ' ' && s[i+k+1] != '\0' ) {
                //printf("Numero = %d\n", (int)(s[i+k+1]-48));
                vetor[aux] *= 10;
                vetor[aux] += (int)(s[i+k+1]-48);
                k++;
            }
            aux++;
            i += k;
        }
    }
    for (i = 0; i < *tamanho; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");

    return vetor;
}

int main() {
    char entrada[100];

    scanf("%[^\n]s", entrada);
    int tamanho;
    int *vetorInt = splitInt(entrada, &tamanho);

    if (vetorInt == NULL) {
        printf("String inválida");
        return 1;
    }

    printf("Tamanho: %d\nVetor de Inteiros Retornado: ", tamanho);

    int i;
    for (i = 0; i < tamanho; i++) {
        printf("%d ", vetorInt[i]);
    }
    printf("\nManipulação de Inteiro: ");
    for (i = 0; i < tamanho; i++) {
        printf("%d ", vetorInt[i]*2);
    }
    printf("\n");
    free(vetorInt);
    return 0;
}

