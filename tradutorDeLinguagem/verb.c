// ************************************************************
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char *sufixo = "en";
char *trimString(char *str)
{
  char *end;
  while (isspace((unsigned char)*str))
    str++;
  if (*str == 0)
    return str;
  end = str + strlen(str) - 1;
  while (end > str && isspace((unsigned char)*end))
    end--;
  end[1] = '\0';
  return str;
}

char *pegaUltimosCaracteres(char *palavra, int qtd)
{
  int tamanhoPalavra = strlen(palavra);
  int posicao = tamanhoPalavra - qtd;
  char *novaPalavra;

  novaPalavra = (char *)malloc(qtd * sizeof(char));

  int cont = 0;
  while (posicao < tamanhoPalavra)
  {
    novaPalavra[cont] = palavra[posicao];
    cont++;
    posicao++;
  }
  return novaPalavra;
}

int is_tempo_verbal(char *presente, char *palavra)
{
  return strcmp(presente, pegaUltimosCaracteres(palavra, strlen(presente))) ? 1 : 0;
}

void descreveTempoVerbal(FILE *arqSaida, char *sufixoLista, char *palavra, char *tempoVerbal)
{
  char *prefixo = malloc(strlen(palavra));
  strncpy(prefixo, palavra, strlen(palavra) - strlen(sufixoLista));
  fprintf(arqSaida, "%s - verb %s, present tense, %s person \n", palavra, strca
}

void determinaTempoVerbal(FILE *arqSaida, char *palavra)
{
  char presente[6][5] = {"o", "os", "a", "om", "ons", "am"};
  char passado[6][5] = {"ei", "es", "e", "em", "est", "im"};
  char futuro[6][5] = {"ai", "ais", "i", "aem", "aist", "aim"};

  char tempoVerbal[6][5] = {"1st", "2nd", "3rd", "4th", "5th", "6th"};

  int cont; //variável de controle do loop
  for (cont = 0; cont < 6; cont++)
  {
    if (is_tempo_verbal(presente[cont], palavra) == 0)
    {
      descreveTempoVerbal(arqSaida, presente[cont], palavra, tempoVerbal[cont]);
      return;
    }
    else if (is_tempo_verbal(passado[cont], palavra) == 0)
    {
      descreveTempoVerbal(arqSaida, passado[cont], palavra, tempoVerbal[cont]);
      return;
    }
    else if (is_tempo_verbal(futuro[cont], palavra) == 0)
    {
      descreveTempoVerbal(arqSaida, futuro[cont], palavra, tempoVerbal[cont]);
      return;
    }
    else if (is_tempo_verbal(sufixo, palavra) == 0)
    {
      fprintf(arqSaida, "%s is a verb case\n", palavra);
      return;
    }
  }
  fprintf(arqSaida, "%s - not a verb case\n", palavra);
  return;
}

void main()
{
  FILE *arqEntrada;
  FILE *arqSaida;
  char str[100];
  char *finalPalavra;
  char *palavra = malloc(strlen(str));

  arqEntrada = fopen("verb.in", "r"); // Cria um arquivo texto para leitura
  if (arqEntrada == NULL)             // Se nào conseguiu criar
  {
    printf("Problemas na leitura do arquivo \n");
    return;
  }
  arqSaida = fopen("verb.out", "w"); // Cria um arquivo texto para gravação
  if (arqSaida == NULL)              // Se nào conseguiu criar
  {
    printf("Problemas na CRIACAO do arquivo\n");
    return;
  }

  while (!feof(arqEntrada))
  {
    if (fgets(str, 100, arqEntrada))
    {
      // tira o \n
      palavra = trimString(str);
      determinaTempoVerbal(arqSaida, palavra);
    }
  }

  fclose(arqEntrada);
  fclose(arqSaida);
}