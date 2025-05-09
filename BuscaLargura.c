#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
    Implementacao Busca em largura


*/

typedef enum Cor
{
    BRANCO,
    CINZA,
    PRETO
} Cor;

typedef struct No
{
    int valor;
    Cor cor;
    int distancia;
    struct No *prox;
    struct No *antecessor;
    // conexoes

} No;

typedef struct ListaEncadeada
{
    No *cabeca;
} ListaEncadeada;

typedef struct Fila
{
    int *vet;
    int size;
    int inicio;
    int fim;
    int tam;
} Fila;

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
    }
    return -1; // erro
}
void Enfilera(Fila *fila, No *no)
{

    // add
    // realocar
    // incremento tamanho
    if (fila->size < fila->tam)
    {
        fila->tam++;
        fila->vet[fila->fim++] = no->valor;
    }
}

/*
    Aloca memória para uma No(que ira compor a lista)

*/
No *CriaNo()
{
    No *aux = malloc(sizeof(No));
    aux->prox = NULL;
    aux->antecessor = NULL;
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
ListaEncadeada *MockValoresGrafo(int nos)
{

    int Nos, isOrientado = 0;
    scanf("%d", &Nos);
    scanf("%d", &isOrientado);

    ListaEncadeada *grafo = CriaLista(nos);

    for (int i = 0; i < Nos; i++)
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

    for (int i = 0; i <= nos; i++)
    {
        No *aux = grafo[i].cabeca;
        while (aux != NULL)
        {
            if (aux->valor)
            {
                printf("no %d: Nos: %d\n", i, aux->valor);
            }

            aux = aux->prox;
        }
    }
}

// vetor de distancias
// vetor de antecessores
// vetor de cores
// vetor(pilha) de proximos nos na busca(FIFO)

// instancias genericas
int *criaVetor(int nos)
{
    int *aux = malloc(sizeof(int) * nos);
    return aux;
}

No *criaVetorAntec(int nos)
{
    No *aux = malloc(sizeof(No) * nos);
    return aux;
}

void inicializaVetDados(No *vetor, int nos)
{

    const int inf = 9999999;

    for (int i = 0; i < nos; i++)
    {
        vetor[i].valor = inf;
        vetor[i].antecessor = NULL;
        vetor[i].cor = BRANCO;
    }
}

No *Bfs(ListaEncadeada *grafo, int valorBuscado, int nos)
{

    // um vetor com as 3 infos
    No *vetorDados = criaVetorAntec(nos);
    inicializaVetDados(vetorDados, nos);

    vetorDados[valorBuscado].cor = CINZA;
    vetorDados[valorBuscado].distancia = 0;
    vetorDados[valorBuscado].antecessor = NULL;

    Fila *fila = CriaFila(nos);
    No *noBuscado = CriaNo(valorBuscado);
    Enfilera(fila, noBuscado);
    while (fila->tam > 0)
    {
        int temp = Desenfilera(fila);
        No *aux = grafo[temp].cabeca;

        while (aux != NULL)
        {
            int temp2 = aux->valor;
            if (vetorDados[temp2].cor == BRANCO)
            {
                vetorDados[aux->valor].cor = CINZA;
                vetorDados[aux->valor].distancia++;
                vetorDados[aux->valor].antecessor = &vetorDados[temp];
                Enfilera(fila, aux->prox);
            }
            aux = aux->prox;
        }
        vetorDados[temp].cor = PRETO;
    }
    return vetorDados;
}

int main()
{

    int totalNos;
    scanf("%d", &totalNos);

    ListaEncadeada *grafo = MockValoresGrafo(totalNos);

    No *vetorDados = Bfs(grafo, 5, totalNos);

    return 0;

    /*
    
    refazer */
}
