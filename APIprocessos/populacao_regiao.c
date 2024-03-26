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
  int numDeCidades[5] = {0,0,0,0,0};

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
    int i=6;

    if (token[8] == 'C') //Regiao centro-oeste
      i = 0;
    else if (token[8] == 'N') {
      if (token[11] == 't') //Regiao norte
        i = 1;
      else //Regiao nordeste
        i = 2;
    }
    else if (token[10] == 'l') //Regiao sul
      i = 3;
    else if (token[10] == 'd') //Regiao sudeste
      i = 4;
    
    token = strtok(NULL, ";");
    valores[i] += atof(token);
    numDeCidades[i]++;
  }

  fclose(arquivo);

  float mediaRegiao[5] = {0.0,0.0,0.0,0.0,0.0};

  arquivo = fopen("populacao_regiao.txt", "w");

  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return 1;
  }

  fprintf(arquivo, "Região Centro-Oeste;%.2f\n", (valores[0]/numDeCidades[0]));
  fprintf(arquivo, "Região Norte;%.2f\n", (valores[1]/numDeCidades[1]));
  fprintf(arquivo, "Região Nordeste;%.2f\n", (valores[2]/numDeCidades[2]));
  fprintf(arquivo, "Região Sul;%.2f\n", (valores[3]/numDeCidades[3]));
  fprintf(arquivo, "Região Sudeste;%.2f\n", (valores[4]/numDeCidades[4]));

  fclose(arquivo);

  return 0;
}
