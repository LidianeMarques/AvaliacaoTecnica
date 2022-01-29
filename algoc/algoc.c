/* Lista recursiva */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// minha ligica
// começa do numero fornecido
// se for impar diminui 1 (usa o -1)
// se for par divide por 2 e usa o resultado
// se usar (-1) coloca um INC
// se usar a divisão por 2 coloca o DUP
// faz até chegar em 1 ou -1 (pois esses são dos comandos PLUSONE e MINUSONE)

struct no_lista
{
    char *comando;
    struct no_lista *anterior;
};

struct no_lista *add(char *comando, struct no_lista *itemAnterior)
{
    struct no_lista *item = NULL;
    if (item == NULL)
    {
        item = malloc(sizeof(*item));
    }
    if (item == NULL)
    {
        printf("\nErro!");
        getchar();
        free(item);
        exit(EXIT_FAILURE);
    }
    item->comando = comando;
    item->anterior = itemAnterior;
    itemAnterior = item;
    return itemAnterior;
}

void listar(struct no_lista *item)
{
    struct no_lista *itemAnterior = NULL;
    /* Mostra a lista */
    itemAnterior = item;
    while (itemAnterior != NULL)
    {
        printf("%s\n", itemAnterior->comando);
        itemAnterior = itemAnterior->anterior;
    }
};

void limpaLista(struct no_lista *item)
{
    struct no_lista *itemAnterior = NULL;
    /* Apaga a lista */
    while (item != NULL)
    {
        itemAnterior = item->anterior;
        free(item);
        item = itemAnterior;
    }
};

struct no_lista *trataNumero(int numero, struct no_lista *item)
{
    if (numero == 1 || numero == -1)
    {
        return item;
    }
    else
    {
        if (numero % 2 == 0)
        { // he par
            item = add("DUP", item);
            item = trataNumero(numero / 2, item);
        }
        else
        { // he impar
            item = add("INC", item);
            item = trataNumero(--numero, item);
        }
    }
}
void main(void)
{
    FILE *arqEntrada;
    char *tecla;
    struct no_lista *item = NULL;
    int constante;

    arqEntrada = fopen("algoc.in", "r"); // Cria um arquivo texto para leitura
    if (arqEntrada == NULL)              // Se nào conseguiu criar
    {
        printf("Problemas na leitura do arquivo \n");
        return;
    }
    while (!feof(arqEntrada))
    {

        fscanf(arqEntrada, "%d", &constante);

        printf("Constant %d\n", constante);
        if (constante > 0)
        {
            printf("PLUSONE\n");
            item = add("\n", NULL);
            item = trataNumero(constante, item);
        }
        else if (constante < 0)
        {
            printf("MINUSONE\n");
            item = add("\n", NULL);
            item = trataNumero(constante, item);
        }
        else
        {
            printf("Fim da execução pois foi colocado a Constante %d\n", constante);
            break;
        }
        listar(item);
        limpaLista(item);
    }
    fclose(arqEntrada);
}
