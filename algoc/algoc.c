/* Lista recursiva */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// minha logica
// começa do numero fornecido
// se for impar diminui 1 (usa o -1)
// se for par divide por 2 e usa o resultado
// se usar (-1) coloca um INC
// se usar a divisão por 2 coloca o DUP
// faz até chegar em 1 ou -1 (pois esses são dos comandos PLUSONE e MINUSONE)

// criacao da estrutura para fazer uma pilha
struct no_lista
{
    char *comando;
    struct no_lista *anterior;
};

//funcao para adicionar item na pilha
struct no_lista *add(FILE *arqSaida, char *comando, struct no_lista *itemAnterior)
{
    struct no_lista *item = NULL;
    if (item == NULL)
    {
        item = malloc(sizeof(*item));
    }
    if (item == NULL)
    {
        printf("\nErro!");
        fprintf(arqSaida, "\nErro!");
        getchar();
        free(item);
        exit(EXIT_FAILURE);
    }
    item->comando = comando;
    item->anterior = itemAnterior;
    itemAnterior = item;
    return itemAnterior;
}

// funcao para listar os itens da pilha
void listar(FILE *arqSaida, struct no_lista *item)
{
    struct no_lista *itemAnterior = NULL;
    /* Mostra a lista */
    itemAnterior = item;
    while (itemAnterior != NULL)
    {
        printf("%s\n", itemAnterior->comando);
        fprintf(arqSaida, "%s\n", itemAnterior->comando);
        itemAnterior = itemAnterior->anterior;
    }
};

// faz a limpeza da pilha na memoria
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

// implementa a logica para criar os comandos do ALGOC
struct no_lista *trataNumero(FILE *arqSaida, int numero, struct no_lista *item)
{
    // logica de como vai ser tratado o numero para criar os comandos
    // começa do numero fornecido
    // se for impar diminui 1 (-1)
    // se for par divide por 2 e usa o resultado
    // se usar (-1) coloca um INC  (ou seja faz o contrario)
    // se usar a divisão por 2 coloca o DUP  (ou seja faz o contrario)
    // faz ate chegar em 1 ou -1
    if (numero == 1 || numero == -1) // é até aqui pois os comandos deles eh PLUSONE e MINUSONE que ja foram colocados no inicio da main
    {
        return item;
    }
    else
    {
        if (numero % 2 == 0)
        {                                      // eh par
            item = add(arqSaida, "DUP", item); // adiciona o item na pilha
            item = trataNumero(arqSaida, numero / 2, item);
        }
        else
        {                                      // eh impar
            item = add(arqSaida, "INC", item); // adiciona o item na pilha
            item = trataNumero(arqSaida, --numero, item);
        }
    }
}

// metodo principal que chama todos os metodos necessario para o programa funcionar corretamente
void main(void)
{
    // cria as variaveis e instancia algumas
    FILE *arqEntrada;
    FILE *arqSaida;
    struct no_lista *item = NULL;
    int constante;
    // fim da criacao das variaveis

    // nesse bloco faz a abertura dos arquivos, um apenas para leitura e outra para escrita
    arqEntrada = fopen("algoc.in", "r"); // Cria um arquivo texto para leitura
    if (arqEntrada == NULL)              // Se nao conseguiu criar
    {
        printf("Problemas na leitura do arquivo \n");
        return;
    }
    arqSaida = fopen("algoc.out", "w"); // Cria um arquivo texto para gravacao
    if (arqSaida == NULL)               // Se nao conseguiu criar
    {
        printf("Problemas na criacao do arquivo\n");
        return;
    }
    // fim do bloco de abertura dos arquivos

    while (!feof(arqEntrada)) // percorre o arquivo ate chegar no final do arquivo
    {
        fscanf(arqEntrada, "%d", &constante);
        if (constante != 0)                                // entra se a constante for positiva
        {                                                  // pega o conteudo de uma linha e coloca na variavel constante
            printf("Constant %d\n", constante);            //mosta no terminal a mensagem de titulo com a determinada constante
            fprintf(arqSaida, "Constant %d\n", constante); //mosta no arquivo de saida a mensagem de titulo com a determinada constante
            if (constante > 0)                             // entra se a constante for positiva
            {
                printf("PLUSONE\n");                           //mosta no terminal a mensagem PLUSONE
                fprintf(arqSaida, "PLUSONE\n");                // cria o primeiro item da pilha para .
                item = trataNumero(arqSaida, constante, NULL); // envia a contante para criar os comandos do ALGOC
            }
            else if (constante < 0) // entra se a constante for negativa
            {
                printf("MINUSONE\n");                          //mosta no terminal a mensagem MINUSONE
                fprintf(arqSaida, "MINUSONE\n");               // adiciona o item de quebra de linha na pilha para deixar uma linha em branco no final.
                item = trataNumero(arqSaida, constante, NULL); // envia a contante para criar os comandos do ALGOC
            }
        }
        else
        {
            printf("\n", constante);            //mosta no terminal a ultima linha em branco
            fprintf(arqSaida, "\n", constante); //mosta no arquivo de saida a ultima linha em branco
            break;
        }
        listar(arqSaida, item); // faz a listagem da pilha ou seja lista primeiro o ultimo que foi adicionado a pilha
        limpaLista(item);       // faz a limpeza da pilha na memoria
    }
    fclose(arqEntrada); // fecha o arquivo de entrada aberto
    fclose(arqSaida);   // fecha o arquivo de saida aberto
}
