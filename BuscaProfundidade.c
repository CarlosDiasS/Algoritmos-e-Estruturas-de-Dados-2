#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef enum Cor
{
    BRANCO,
    CINZA,
    PRETO
} Cor;
typedef struct No
{
    int valor;
    struct No *prox;
    struct No *ant;
    Cor cor;
    int timestampInic;
    int timestampFin;

} No;

typedef struct ListaEncadeada
{
    No *cabeca;
} ListaEncadeada;

typedef struct DadosVetor
{
    No *antecessor;
    Cor cor;
    int timestampInic;
    int timestampFin;
} DadosVetor;

DadosVetor *criaVetorDados(int totalNos)
{
    DadosVetor *aux = malloc(sizeof(DadosVetor) * totalNos);
    if (!aux)
        return NULL;
    for (int i = 0; i < totalNos; i++)
    {
        aux[i].antecessor = NULL;
        aux[i].cor = BRANCO; // nenhum foi visitado ainda;
        aux[i].timestampInic = 0;
        aux[i].timestampFin = 0;
    }
    return aux;
}

No *CriaNo()
{
    No *aux = malloc(sizeof(No));
    aux->prox = NULL;
    aux->ant = NULL;
    aux->timestampInic = 0;
    aux->timestampFin = 0;
    aux->cor = BRANCO;
    return aux;
}

No *CriaNoNovo(int u)
{
    No *aux = malloc(sizeof(No));
    aux->prox = NULL;
    aux->valor = u;
    aux->ant = NULL;
    aux->timestampInic = 0;
    aux->timestampFin = 0;
    aux->cor = BRANCO;
    return aux;
}
/*
    Mock de dados em uma No
*/
void MockNo(No *No, int valor)
{
    No->valor = valor;
    No->prox = NULL;
}
/*
    Aloca memória para a lista Enc

*/
ListaEncadeada *CriaLista(int nos)
{

    ListaEncadeada *lista = malloc(sizeof(ListaEncadeada) * nos);
    for (int i = 0; i < nos; i++)
    {
        lista[i].cabeca = NULL;
    }

    return lista;
}

/*
    Cria a lista com a função auxiliar
    Mock dos dados do arquivo txt
*/
ListaEncadeada *MockValoresGrafo(int nos, int totalArestas)
{

    int isOrientado = 0;
    scanf("%d", &isOrientado);

    ListaEncadeada *grafo = CriaLista(nos);

    for (int i = 0; i < totalArestas; i++)
    {
        int x, y;
        scanf("%d %d", &x, &y);

        No *nova = CriaNo();
        MockNo(nova, y);
        nova->prox = grafo[x].cabeca;
        grafo[x].cabeca = nova;

        if (!isOrientado)
        {
            No *nova2 = CriaNo();
            MockNo(nova2, x);
            nova2->prox = grafo[y].cabeca;
            grafo[y].cabeca = nova2;
        }
    }
    return grafo;
}

void ImpGrafo(ListaEncadeada *grafo, int nos)
{

    for (int i = 0; i < nos; i++)
    {
        No *aux = grafo[i].cabeca;
        while (aux != NULL)
        {
            if (aux->valor)
            {
                printf("no %d: arestas: %d\n", i, aux->valor);
            }

            aux = aux->prox;
        }
    }
}

void DfsRecursivo(int u, DadosVetor *dados, ListaEncadeada *grafo, int *temp)
{
    // Atualiza o nó atual como visitado (CINZA)
    dados[u].cor = CINZA;
    dados[u].timestampInic = ++(*temp);

    // Percorre todos os vizinhos do nó u
    No *vizinho = grafo[u].cabeca;
    while (vizinho != NULL)
    {
        if (dados[vizinho->valor].cor == BRANCO)
        {
            dados[vizinho->valor].antecessor = CriaNoNovo(u);
            // Define u como antecessor do vizinho (novo no)
            DfsRecursivo(vizinho->valor, dados, grafo, temp);
        }
        vizinho = vizinho->prox;
    }

    // Finaliza o nó (PRETO)
    dados[u].cor = PRETO;
    dados[u].timestampFin = ++(*temp);
}

DadosVetor *DFS(ListaEncadeada *grafo, int nos)
{

    DadosVetor *dados = criaVetorDados(nos);
    int temp = 0;
    printf("ok\n");
    for (int i = 0; i < nos; i++)
    {

        if (dados[i].cor == BRANCO)
        {
            printf("okcahamda\n");

            DfsRecursivo(i, dados, grafo, &temp);
            printf("recursao parcial\n");
        }
        printf("final recursao\n");
    }
    return dados;
}

void printVetorDados(DadosVetor *vetor, int totalNos)
{
    if (vetor != NULL)
    {
        for (int i = 0; i < totalNos; i++)
        {
            if (vetor[i].antecessor != NULL)
                printf("%d -> %d\n", i, vetor[i].antecessor->valor);
            else
                printf("%d -> NULL\n", i);
        }
    }
    printf("Vetor vazio.\n");
}

int main(int argc, char const *argv[])
{
    int totalNos, totalArestas;
    scanf("%d", &totalNos);
    scanf("%d", &totalArestas);
    ListaEncadeada *grafo = MockValoresGrafo(totalNos, totalArestas);
    ImpGrafo(grafo, totalNos);

    DadosVetor *vetorDados = DFS(grafo, totalNos);
    printVetorDados(vetorDados, totalNos);

    // seg fault na hora de retornar da ultimma recusao

    return 0;
}
