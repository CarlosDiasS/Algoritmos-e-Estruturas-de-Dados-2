#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Aresta
{
    int no;
    struct Aresta *prox; // conexoes

} Aresta;

typedef struct ListaEncadeada
{
    Aresta *cabeca;
} ListaEncadeada;

Aresta *CriaAresta(int no)
{
    Aresta *aux = malloc(sizeof(Aresta));
    aux->prox = NULL;
    aux->no = no;
    return aux;
}

void MockAresta(ListaEncadeada *grafo, int x, int y)
{
    Aresta *novaAresta = CriaAresta(y);
    novaAresta->prox = grafo[x].cabeca;
    grafo[x].cabeca = novaAresta;
}

ListaEncadeada *CriaLista(int nos)
{

    ListaEncadeada *lista = malloc(sizeof(ListaEncadeada) * nos);
    if (!lista)
    {
        exit(1);
    }
    for (int i = 0; i < nos; i++)
    {
        lista[i].cabeca = NULL;
    }
    return lista;
}

/*
    Cria a lista com a função auxiliar
    Mock dos dados
*/
ListaEncadeada *MockValoresGrafo(int nos)
{

    int arestas, isOrientado = 0;

    ListaEncadeada *grafo = CriaLista(nos);
    scanf("%d %d", &arestas, &isOrientado);

    for (int i = 0; i < arestas; i++)
    {
        int x, y = 0;
        scanf("%d %d", &x, &y);
        MockAresta(grafo, x, y);

        // grafo orientado
        if (!isOrientado)
        {
            MockAresta(grafo, y, x);
        }
    }

    return grafo;
}

void ImpGrafo(ListaEncadeada *grafo, int nos)
{
    for (int i = 0; i < nos; i++)
    {
        printf("Nó %d:", i);
        Aresta *aux = grafo[i].cabeca;
        while (aux != NULL)
        {
            printf(" -> %d", aux->no);
            aux = aux->prox;
        }
        printf("\n");  
    }
}
/*
    Calculo grau de no unitario

*/
int GetGrauNo(ListaEncadeada *grafo, int no)
{

    int total = 0;
    Aresta *aux = grafo[no].cabeca;
    while (grafo[no].cabeca != NULL)
    {
        total++;
        aux = aux->prox;
    }
    return total;
}
/*
    Verifica se existe algum Vertices isolado(sem conexoes)

*/
bool isIsolado(ListaEncadeada *grafo, int no)
{
    if (GetGrauNo(grafo, no) == 0)
    {
        printf("O no %d esta isolado.\n", no);
        return true;
    }
    else
    {
        printf("O no %d nao esta isolado.\n", no);
        return false;
    }
}

int GetGrauMax(ListaEncadeada *grafo, int totalNos)
{
    int maxGrau = GetGrauNo(grafo, 0);
    for (int i = 0; i < totalNos; i++)
    {
        int aux = GetGrauNo(grafo, i);
        if (maxGrau > aux)
        {
            maxGrau = aux;
        }
    }
    printf("Grau maximo do grafo: %d\n", maxGrau);
    return maxGrau;
}
/*
    Calcula e retorna grau maximo do grafo

*/
int GetGrauMin(ListaEncadeada *grafo, int totalNos)
{
    int minGrau = GetGrauNo(grafo, 0);
    for (int i = 0; i < totalNos; i++)
    {
        int aux = GetGrauNo(grafo, i);
        if (minGrau > aux)
        {
            minGrau = aux;
        }
    }
    printf("Grau maximo do grafo: %d\n", minGrau);
    return minGrau;
}
/*
    Calcule se os vertices(no) tem o mesmo numero de conexoes(arestas)

*/
bool isRegular(ListaEncadeada *grafo, int totalNos)
{

    int aux, temp = 0;
    temp = GetGrauNo(grafo, 0);

    for (int i = 1; i < totalNos; i++)
    {
        aux = GetGrauNo(grafo, i);
        if (aux != temp)
        {
            printf("O grafo não é regular.\n");
            return false;
        }
    }
    printf("O grafo é regular.\n");
    return true;
}
/*
    Calculo se todos os vertices sao adjacentes aos outros
    (todos conectados de modo adjacente)

*/
bool isCompleto(ListaEncadeada *grafo, int totalNos)
{

    // total de arestas = n*(n+1) /2 n= numero de vertices
    // https://www.pucsp.br/~jarakaki/grafos/Aula2.pdf

    int totalArestas = 0;

    for (int i = 0; i < totalNos; i++)
    {

        while (grafo[i].cabeca != NULL)
        {
            Aresta *aux = grafo[i].cabeca;
            totalArestas++;
            aux = aux->prox;
        }
    }

    // condicional para a formula (grafo nao direcionado)
    if (totalArestas == (totalNos * (totalNos + 1)) / 2)
    {
        printf("O grafo é completo.\n");
        return true;
    }
    return false;
}

// funcao para liberar memoria

int main()
{
    int totalNos;
    scanf("%d", &totalNos);
    ListaEncadeada *grafo = MockValoresGrafo(totalNos);
    // printf("%d",grafo->cabeca->no);
    ImpGrafo(grafo, totalNos);

    for (int i = 2; i < totalNos; i++)
    {
        printf("Grau do nó %d: %d\n", i, GetGrauNo(grafo, i));
    }

    GetGrauMax(grafo, totalNos);
    GetGrauMin(grafo, totalNos);

    isRegular(grafo, totalNos);
    isCompleto(grafo, totalNos);

    return 0;
}
