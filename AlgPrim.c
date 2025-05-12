#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct No
{
    int valor;
    struct No *prox;
    int peso;

} No;

typedef struct ListaEncadeada
{
    No *cabeca;
} ListaEncadeada;

typedef struct DadosVetor
{
    No *antecessor;
    int chave; // menor peso
} DadosVetor;

typedef struct Fila
{
    int *vet;
    int size;
    int inicio;
    int fim;
    int tam;
} Fila;

DadosVetor *criaVetorDados(int totalNos)
{
    DadosVetor *aux = malloc(sizeof(DadosVetor) * totalNos);
    if (!aux)
        return NULL;
    for (int i = 0; i < totalNos; i++)
    {
        aux[i].antecessor = NULL;
        aux[i].chave = -1;
    }
    return aux;
}

No *CriaNo()
{
    No *aux = malloc(sizeof(No));
    aux->prox = NULL;
    return aux;
}

No *CriaNoNovo(int u)
{
    No *aux = malloc(sizeof(No));
    aux->prox = NULL;
    aux->valor = u;
    return aux;
}

No *CriaNoComPeso(int valor, int peso)
{
    No *aux = malloc(sizeof(No));
    aux->valor = valor;
    aux->peso = peso;
    aux->prox = NULL;
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
    int isPonderado = 0;
    scanf("%d", &isPonderado);

    ListaEncadeada *grafo = CriaLista(nos);

    for (int i = 0; i < totalArestas; i++)
    {
        int x, y, peso;
        scanf("%d %d %d", &x, &y, &peso);

        No *nova = CriaNoComPeso(y,peso);
        nova->prox = grafo[x].cabeca;
        grafo[x].cabeca = nova;
        grafo[x].cabeca->peso = x;

        if (!isOrientado)
        {
            No *nova2 = CriaNoComPeso(x,peso);
            nova2->prox = grafo[y].cabeca;
            grafo[y].cabeca = nova2;
        }
    }
    return grafo;
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

Fila *CriaFila(int nos)
{
    Fila *aux = malloc(sizeof(Fila));
    aux->size = nos;
    aux->inicio = 0;
    aux->fim = 0;
    aux->tam = 0;
    aux->vet = malloc(sizeof(int) * nos);

    return aux;
}

int Desenfilera(Fila *fila)
{
    if (fila->tam > 0)
    {
        fila->tam--;
        return fila->vet[fila->inicio++];
        insertionSort(fila->tam, fila->vet);
    }
    return -1; // erro
}
void Enfilera(Fila *fila, int no)
{

    if (fila->size < fila->tam)
    {
        fila->tam++;
        fila->vet[fila->fim++] = no;
        insertionSort(fila->tam, fila->vet);
        return;
    }
    insertionSort(fila->tam, fila->vet);
    return;
}

void troca(int *vet, int i, int j)
{
    int aux = vet[i];
    vet[i] = vet[j];
    vet[j] = aux;
}

void insertionSort(int n, int *vet)
{

    for (int i = 1; i < n; i++)
    { // o elemento vet[0] ja esta ordenado
        for (int j = i; j > 0 && vet[j] < vet[j - 1]; j--)
        { // se o elemento for menor que o anterior, sao invertidos
            troca(vet, j, j - 1);
        }
    }
}

DadosVetor *AgmPrim(ListaEncadeada *grafo, int totalNos)
{
    DadosVetor *dados = criaVetorDados(totalNos);
    Fila *fila = CriaFila(totalNos);

    for (int i = 0; i < totalNos; i++)
    {
        dados[i].chave = 99999; // inf
    }
    dados[0].chave = 0;
    Enfilera(fila, 0);

    while (fila->tam > 0)
    {
        int u = Desenfilera(fila);
        No *vizinho = grafo[u].cabeca;

        while (vizinho != NULL)
        {
            int v = vizinho->valor;
            int peso_uv = 1;

            if (dados[v].chave > peso_uv)
            {
                dados[v].chave = peso_uv;
                dados[v].antecessor = CriaNoNovo(u);
                Enfilera(fila, v);
            }

            vizinho = vizinho->prox;
        }
    }

    return dados;
}

int main(int argc, char const *argv[])
{
    int totalNos, totalArestas;
    scanf("%d", &totalNos);
    scanf("%d", &totalArestas);
    ListaEncadeada *grafo = MockValoresGrafo(totalNos, totalArestas);
    ImpGrafo(grafo, totalNos);

    printf("\n");

    DadosVetor *dados = AgmPrim(grafo, totalNos);
    printVetorDados(dados, totalNos);

    return 0;
}
