#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define MAX_LINE_LENGTH 1024

int main () {
  FILE *arquivo;
  char linha[MAX_LINE_LENGTH];
  char *token;
  float valores[5] = {0,0,0,0,0};
  int numPorPorte[5] = {0,0,0,0,0};

  arquivo = fopen("dados_municipios.csv", "r");

  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return 1;
  }

  while (fgets(linha, MAX_LINE_LENGTH, arquivo) != NULL) {
    token = strtok(linha, ";");
    token = strtok(NULL, ";");
    token = strtok(NULL, ";");
    token = strtok(NULL, ";");
    token = strtok(NULL, ";");
    token = strtok(NULL, ";");
    token = strtok(NULL, ";");

    float backup = atof(token);

    token = strtok(NULL, ";");
    int i=6;

    if (token[0] == 'G') //Porte Grande
      i = 0;
    else if (token[0] == 'M') {
      if (token[3] == 'd') //Porte Medio
        i = 1;
      else if (token[2] == 't') //Porte Metropole
        i = 2;
    }
    else if (token[9] == 'I') //Porte Pequeno II
      i = 4;
    else if (token[8] == 'I'){ //Porte Pequeno I
      i = 3;
    }
    
    valores[i] += backup;
    numPorPorte[i]++;
  }

  fclose(arquivo);

  arquivo = fopen("populacao_porte.txt", "w");

  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return 1;
  }

  fprintf(arquivo, "Porte Grande;%.2f\n", (valores[0]/numPorPorte[0]));
  fprintf(arquivo, "Porte Médio;%.2f\n", (valores[1]/numPorPorte[1]));
  fprintf(arquivo, "Porte Metropole;%.2f\n", (valores[2]/numPorPorte[2]));
  fprintf(arquivo, "Porte Pequeno I;%.2f\n", (valores[3]/numPorPorte[3]));
  fprintf(arquivo, "Porte Pequeno II;%.2f\n", (valores[4]/numPorPorte[4]));

  fclose(arquivo);

  return 0;
}
