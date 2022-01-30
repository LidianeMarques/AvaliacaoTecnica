// ********************
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define true 1
#define false 0

char *sufixo = "en";

// metodo para retirar espacos vasios no inicio e no fim da palavra
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

// pega a substring do final de acordo com o valor qtd passado( exemplo qtd = 3 pega os 3 ultimos caracteres)
char *pegaUltimosCaracteres(char *palavra, int qtd)
{
  int tamanhoPalavra = strlen(palavra);
  int posicao = tamanhoPalavra - qtd;
  char *sufuxoPalavra = (char *)malloc(qtd * sizeof(char));
  strncpy(sufuxoPalavra, palavra + posicao, qtd);
  return sufuxoPalavra;
}

// faz a verificacao se a palavra eh um verbo conjugado ou nao se for retorna 1 se nao retorna 0).
int is_tempo_verbal(char *presente, char *palavra)
{
  return strcmp(presente, pegaUltimosCaracteres(palavra, strlen(presente))) ? false : true;
}

// monta a frase de acordo com o tempo verbal encontrado
void descreveTempoVerbal(FILE *arqSaida, char *sufixoLista, char *palavra, char *tempoVerbal)
{
  char *prefixo = malloc(strlen(palavra));
  strncpy(prefixo, palavra, strlen(palavra) - strlen(sufixoLista));
  fprintf(arqSaida, "%s - verb %s, present tense, %s person \n", palavra, strcat(prefixo, sufixo), tempoVerbal);
}

// faz a verificacao se a palavra eh um verbo e de qual eh o tempo verbal pertence e chama
// o metodo para montar a frase e coloca no arquivo de saida
int determinaTempoVerbal(FILE *arqSaida, char *palavra)
{
  char presente[6][5] = {"o", "os", "a", "om", "ons", "am"};
  char passado[6][5] = {"ei", "es", "e", "em", "est", "im"};
  char futuro[6][5] = {"ai", "ais", "i", "aem", "aist", "aim"};

  char tempoVerbal[6][5] = {"1st", "2nd", "3rd", "4th", "5th", "6th"};

  int cont; //variável de controle do loop
  for (cont = 0; cont < 6; cont++)
  {
    if (is_tempo_verbal(presente[cont], palavra) == true) // verifica se está em alguma regra de tempo verbal do presente
    {
      // cria a frase de acordo com o tempo verbal
      descreveTempoVerbal(arqSaida, presente[cont], palavra, tempoVerbal[cont]);
      return true;
    }
    else if (is_tempo_verbal(passado[cont], palavra) == true) // verifica se está em alguma regra de tempo verbal do passado
    {
      // cria a frase de acordo com o tempo verbal
      descreveTempoVerbal(arqSaida, passado[cont], palavra, tempoVerbal[cont]);
      return true;
    }
    else if (is_tempo_verbal(futuro[cont], palavra) == true) // verifica se está em alguma regra de tempo verbal do futuro
    {
      descreveTempoVerbal(arqSaida, futuro[cont], palavra, tempoVerbal[cont]);
      return true;
    }
    else if (is_tempo_verbal(sufixo, palavra) == true) // verifica se é um verbo sem conjugacao
    {
      fprintf(arqSaida, "%s is a verb case\n", palavra);
      return true;
    }
  }
  //  caso nao seja verbo mostra essa frase abaixo
  fprintf(arqSaida, "%s - not a verb case\n", palavra);
  return false;
}

void main()
{
  FILE *arqEntrada;
  FILE *arqSaida;
  char palavra[20];

  arqEntrada = fopen("verb.in", "r"); // pega um arquivo texto para leitura
  if (arqEntrada == NULL)             // verifica se nào conseguiu encontrar
  {
    printf("Problemas na leitura do arquivo verb.in\n");
  }
  arqSaida = fopen("verb.out", "w"); // pega ou cria um arquivo texto para gravação (caso ja tenha algo apaga tudo)
  if (arqSaida == NULL)              // verifica se nào conseguiu criar
  {
    printf("Problemas na CRIACAO do arquivo verb.out\n");
  }

  // percorre todo arquivo pegando cada linha (palavra) que contem até o final
  while (!feof(arqEntrada))
  {
    fscanf(arqEntrada, "%s", palavra);
    // 'trimString' faz um tratamento pra tirar os espacos do inicio e do fim da linha para pegar apenas a palavra
    determinaTempoVerbal(arqSaida, trimString(palavra)); // 'determinaTempoVerbal' chama a funcao para executar a logica se eh ou nao verbo e conjugalo caso seja
  }
  // fecha os arquivos abertos
  fclose(arqEntrada);
  fclose(arqSaida);
}