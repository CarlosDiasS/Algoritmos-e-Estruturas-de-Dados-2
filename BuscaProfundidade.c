#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct No
{
    int valor;
    struct No *prox;
    struct No *antecessor;
    // conexoes

} No;

typedef struct ListaEncadeada
{
    No *cabeca;
} ListaEncadeada;

typedef enum Cor{
    BRANCO,
    CINZA,
    PRETO
}Cor;

typedef struct DadosVetor{
    int antecessor;
    Cor cor;
    int timestamp;
}DadosVetor;

DadosVetor *criaVetorDados(int totalNos){
    DadosVetor *aux = malloc(sizeof(int)*totalNos);
    if(!aux) return NULL;
    for(int i=0;i<totalNos;i++){
        aux[i].antecessor = NULL;
        aux[i].cor = BRANCO; // nenhum foi visitado ainda;
        aux[i].timestamp = 0;
    }
    return aux;
}

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

void DfsRecursivo(No *u){

}


DFS(ListaEncadeada * grafo,int nos){

    DadosVetor *dados = criaVetorDados(nos);

    for(int i=0;i<nos;i++){
        if()
    }


}














int main(int argc, char const *argv[])
{
    int totalNos, totalArestas;
    scanf("%d", &totalNos);
    scanf("%d", &totalArestas);
    ListaEncadeada *grafo = MockValoresGrafo(totalNos, totalArestas);
    ImpGrafo(grafo, totalNos);







    // testes

    return 0;
}
