#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
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
}
