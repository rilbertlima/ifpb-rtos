#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define MAX_LINE_LENGTH 1024

int main () {
  FILE *arquivo;
  char linha[MAX_LINE_LENGTH];
  char *token;
  float valores[27] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  int numPorEstado[27] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

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

    int i=28;

    if (!strcmp(token, "AC"))
      i = 0;
    else if (!strcmp(token, "AL"))
      i = 1;
    else if (!strcmp(token, "AM"))
      i = 2;
    else if (!strcmp(token, "AP"))
      i = 3;
    else if (!strcmp(token, "BA"))
      i = 4;
    else if (!strcmp(token, "CE"))
      i = 5;
    else if (!strcmp(token, "DF"))
      i = 6;
    else if (!strcmp(token, "ES"))
      i = 7;
    else if (!strcmp(token, "GO"))
      i = 8;
    else if (!strcmp(token, "MA"))
      i = 9;
    else if (!strcmp(token, "MG"))
      i = 10;
    else if (!strcmp(token, "MS"))
      i = 11;
    else if (!strcmp(token, "MT"))
      i = 12;
    else if (!strcmp(token, "PA"))
      i = 13;
    else if (!strcmp(token, "PB"))
      i = 14;
    else if (!strcmp(token, "PE"))
      i = 15;
    else if (!strcmp(token, "PI"))
      i = 16;
    else if (!strcmp(token, "PR"))
      i = 17;
    else if (!strcmp(token, "RJ"))
      i = 18;
    else if (!strcmp(token, "RN"))
      i = 19;
    else if (!strcmp(token, "RO"))
      i = 20;
    else if (!strcmp(token, "RR"))
      i = 21;
    else if (!strcmp(token, "RS"))
      i = 22;
    else if (!strcmp(token, "SC"))
      i = 23;
    else if (!strcmp(token, "SE"))
      i = 24;
    else if (!strcmp(token, "SP"))
      i = 25;
    else if (!strcmp(token, "TO"))
      i = 26;

    token = strtok(NULL, ";");
    token = strtok(NULL, ";");
    token = strtok(NULL, ";");

    valores[i] += atof(token);
    numPorEstado[i]++;
  }

  fclose(arquivo);

  arquivo = fopen("populacao_estado.txt", "w");

  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return 1;
  }

  fprintf(arquivo, "AC;%.2f\n", (valores[0]/numPorEstado[0]));
  fprintf(arquivo, "AL;%.2f\n", (valores[1]/numPorEstado[1]));
  fprintf(arquivo, "AM;%.2f\n", (valores[2]/numPorEstado[2]));
  fprintf(arquivo, "AP;%.2f\n", (valores[3]/numPorEstado[3]));
  fprintf(arquivo, "BA;%.2f\n", (valores[4]/numPorEstado[4]));
  fprintf(arquivo, "CE;%.2f\n", (valores[5]/numPorEstado[5]));
  fprintf(arquivo, "DF;%.2f\n", (valores[6]/numPorEstado[6]));
  fprintf(arquivo, "ES;%.2f\n", (valores[7]/numPorEstado[7]));
  fprintf(arquivo, "GO;%.2f\n", (valores[8]/numPorEstado[8]));
  fprintf(arquivo, "MA;%.2f\n", (valores[9]/numPorEstado[9]));
  fprintf(arquivo, "MG;%.2f\n", (valores[10]/numPorEstado[10]));
  fprintf(arquivo, "MS;%.2f\n", (valores[11]/numPorEstado[11]));
  fprintf(arquivo, "MT;%.2f\n", (valores[12]/numPorEstado[12]));
  fprintf(arquivo, "PA;%.2f\n", (valores[13]/numPorEstado[13]));
  fprintf(arquivo, "PB;%.2f\n", (valores[14]/numPorEstado[14]));
  fprintf(arquivo, "PE;%.2f\n", (valores[15]/numPorEstado[15]));
  fprintf(arquivo, "PI;%.2f\n", (valores[16]/numPorEstado[16]));
  fprintf(arquivo, "PR;%.2f\n", (valores[17]/numPorEstado[17]));
  fprintf(arquivo, "RJ;%.2f\n", (valores[18]/numPorEstado[18]));
  fprintf(arquivo, "RN;%.2f\n", (valores[19]/numPorEstado[19]));
  fprintf(arquivo, "RO;%.2f\n", (valores[20]/numPorEstado[20]));
  fprintf(arquivo, "RR;%.2f\n", (valores[21]/numPorEstado[21]));
  fprintf(arquivo, "RS;%.2f\n", (valores[22]/numPorEstado[22]));
  fprintf(arquivo, "SC;%.2f\n", (valores[23]/numPorEstado[23]));
  fprintf(arquivo, "SE;%.2f\n", (valores[24]/numPorEstado[24]));
  fprintf(arquivo, "SP;%.2f\n", (valores[25]/numPorEstado[25]));
  fprintf(arquivo, "TO;%.2f\n", (valores[26]/numPorEstado[26]));

  fclose(arquivo);

  return 0;
}
