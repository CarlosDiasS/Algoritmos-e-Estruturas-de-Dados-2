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
/*
    Aloca memória para uma aresta(que ira compor a lista)

*/
Aresta *CriaAresta()
{
    Aresta *aux = malloc(sizeof(Aresta));
    aux->prox = NULL;
    aux->no = -1;
    return aux;
}
/*
    Mock de dados em uma aresta
*/
void MockAresta(Aresta *aresta, int no)
{
    aresta->no = no;
    aresta->prox = NULL;
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
ListaEncadeada *MockValoresGrafo(int nos)
{

    int arestas, isOrientado = 0;
    scanf("%d", &arestas);
    scanf("%d", &isOrientado);

    ListaEncadeada *grafo = CriaLista(nos);

    for (int i = 0; i < arestas; i++)
    {
        int x, y;
        scanf("%d %d", &x, &y);

        Aresta *nova = CriaAresta();
        MockAresta(nova, y);
        nova->prox = grafo[x].cabeca;
        grafo[x].cabeca = nova;

        if (!isOrientado)
        {
            Aresta *nova2 = CriaAresta();
            MockAresta(nova2, x);
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
        Aresta *aux = grafo[i].cabeca;
        while (aux != NULL)
        {
            if (aux->no)
            {
                printf("no %d: arestas: %d\n", i, aux->no);
            }

            aux = aux->prox;
        }
    }
}
/*
    Calculo grau de no unitario

*/
int GetGrauNo(ListaEncadeada *grafo, int no)
{

    int total = 0;
    Aresta *aux = grafo[no].cabeca;
    while (aux != NULL)
    {
        total++;
        aux = aux->prox;
    }
    return total;
}
/*
    Verifica se existe algum Vertice isolado(sem conexoes)

*/
bool isIsolado(ListaEncadeada *grafo, int no)
{
    if (!GetGrauNo(grafo, no))
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
/*
    Calcula e retorna grau maximo do grafo

*/
int GetGrauMax(ListaEncadeada *grafo, int no, int totalNos)
{
    // grau 1 apenas para comparacao
    int grau = GetGrauNo(grafo, no);
    int aux = 0;
    for (int i = 1; i < totalNos; i++)
    {
        aux = GetGrauNo(grafo, i);
        if (grau < aux)
        {
            printf("Grau maximo do grafo: %d\n", aux);
            aux = grau;
            return aux;
        }
    }
    return aux;
}
/*
    Calcula e retorna grau minimo do grafo
    Similar a GetGrauMax

*/
int GetGrauMin(ListaEncadeada *grafo, int no, int totalNos)
{
    int grau = GetGrauNo(grafo, no); // no 1
    int aux = 0;
    for (int i = 1; i < totalNos; i++)
    {
        aux = GetGrauNo(grafo, i);
        if (grau > aux)
        {
            printf("Grau minimo do grafo: %d\n", aux);
            aux = grau;
        }
    }
    return aux;
}
/*
    Calcule se os vertices(no) tem o mesmo numero de conexoes(arestas)

*/
bool isRegular(ListaEncadeada *grafo, int totalNos)
{

    int aux, temp = 0;
    temp = GetGrauNo(grafo, 1);

    for (int i = 1; i < totalNos; i++)
    {
        aux = GetGrauNo(grafo, i + 1);
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

    int totalArestas = 0;

    for (int i = 0; i < totalNos; i++)
    {
        Aresta *aux = grafo[i].cabeca;
        while (aux != NULL)
        {
            totalArestas++;
            aux = aux->prox;
        }
    }

    // condicional para a formula
    if (totalArestas == (totalNos * (totalNos + 1)) / 2)
    {
        printf("O grafo é completo.\n");
        return true;
    }
    printf("O grafo não é completo.\n");
    return false;
}

int main()
{
    int totalNos;
    scanf("%d", &totalNos);
    ListaEncadeada *grafo = MockValoresGrafo(totalNos);
    ImpGrafo(grafo, totalNos);
    printf("\n");
    for (int i = 1; i < totalNos; i++)
    {
        printf("Grau do no %d: %d \n", i, GetGrauNo(grafo, i));
    }
    printf("\n");
    printf("%d\n", GetGrauMax(grafo, 1, totalNos));

    isIsolado(grafo, 2);
    isRegular(grafo, totalNos);
    isCompleto(grafo, totalNos);

    return 0;
}
