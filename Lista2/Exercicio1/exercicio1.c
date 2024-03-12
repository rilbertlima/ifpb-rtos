#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "pacote.h"

/*typedef struct {
    int id;
    int type;
    long long int source;
    long long int destination;
    unsigned int* payload;
    int size;
} Packet;

Packet* createDataPacket (int id, long long int source, long long int destination, int size) {
    Packet *pacote = (Packet *)malloc(sizeof(Packet));
    pacote->type = 1;
    pacote->id = id;
    pacote->source = source;
    pacote->destination = destination;
    pacote->size = size;
    pacote->payload = (unsigned int*)malloc(size*sizeof(unsigned int));
    
    return pacote;
}

Packet* createACKPacket (int id, long long int source, long long int destination) {
    Packet *pacote = (Packet *)malloc(sizeof(Packet));
    pacote->type = 0;
    pacote->id = id;
    pacote->source = source;
    pacote->destination = destination;
    pacote->size = 0;
    pacote->payload = NULL;
    
    return pacote;
}

void writeData (Packet *pacote, unsigned int *dados, int *tamanho) {
    int i;
    for (i=0; i < pacote->size; i++) {
        if ( i >= *tamanho ) {
            pacote->payload[i] = 0;
        }
        else {
            pacote->payload[i] = dados[i];
        }
    }
}

void printPacketInformation (Packet *pacote) {
    printf("Packet type: ");
    if (pacote->type == 0) { //ACK Packet
        printf("ACK\nID: %d\nSource Address: %lld\nDestination Address: %lld\n", pacote->id, pacote->source, pacote->destination);
    }
    else {                  //Data Packet
        printf("DATA\nID: %d\nSource Address: %lld\nDestination Address: %lld\nPayload Size: %d\nPayload:", pacote->id, pacote->source, pacote->destination, pacote->size);
        int i;
        for (i=0; i<pacote->size; i++) {
            
            printf(" %d", pacote->payload[i]);
        }
        printf("\n");
    }
}

void deletePacket (Packet *pacote) {
    free(pacote->payload);
    free(pacote);
}*/

int main() {
    printf("Criando pacote de dados\n");
    Packet *testeDATA = createDataPacket (1, 10, 20, 20);

    printf("Criando pacote de reconhecimento\n");
    Packet *testeACK = createACKPacket (2, 30, 40);

    //Valores para escrever no pacote de dados
    unsigned int valores[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int tamanho = 10;
    
    printf("Escrevendo no pacote de dados\n");
    writeData (testeDATA, valores, &tamanho);
    
    printf("\nMostrando o pacote de dados\n\n");
    printPacketInformation (testeDATA);

    printf("\n\nMostrando o pacote de reconhecimento\n\n");
    printPacketInformation (testeACK);
    
    printf("\n\nDeletando os pacotes de dados e de reconhecimento\n\n");
    deletePacket (testeDATA);
    deletePacket (testeACK);
    
    return 0;
}
