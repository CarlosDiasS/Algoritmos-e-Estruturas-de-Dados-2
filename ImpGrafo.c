#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
 criar matriz adjacencia

1- Criar matriz(ler arquivo passado na main)

2-imp Matriz

3-Calculo grau de um no

4 -verificar se o grafo tem vertice isolado

5- Calculo grau max e min do grafo

6 - Verificar se o grafo é regular

7 - Verificar se o grafo é completo

* passar arquivo : gcc/.. < arquivo.txt

*verificar se é orientado (condicional)


//ajustar, aresta nao serve para limite em laços, apenas os nos
grafos sao matrizes no X no

//alterar onde tem arestas para nos
arestas nao influenciam nas funcoes que fazem calculo
o que determina o tamanho da matriz sao os NÓS

/*
    Cria matriz quadrada NxN
*/
int **criarMatriz(int n)
{

    int **aux = malloc(sizeof(n * sizeof(int)));

    if (!aux)
    {
        printf("Erro ao alocar memoria.");
        exit(1);
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            aux[i] = malloc(sizeof(n * sizeof(int)));
            aux[i][j] = 0;
        }
    }
    return aux;
}

/*
    Le arquivo passado como parametro
    Chama criaMatriz
    Preenche com os dados do txt
*/
int **novaMatriz(const char *arquivo, int *nos, int *arestas, int *isOrientado)
{
    FILE *texto = fopen(arquivo, "r");
    fscanf(texto, "%d"
                  "%d"
                  "%d",
           nos, arestas, isOrientado);

    int **aux = criarMatriz(*nos);
    int x, y = 0;

    for (int i = 0; i < *arestas; i++)
    {
        fscanf(texto, "%d %d", &x, &y);
        // conexao
        aux[x - 1][y - 1] = 1;

        // caminho contrario
        // matriz orientada
        if (isOrientado)
        {
            aux[y - 1][x - 1] = 1;
        }
    }
    fclose(texto);
    return aux;
}

/*
    Impressao matriz NxN

*/
void impMatriz(int **matriz, int nos)
{

    for (int i = 0; i < nos; i++)
    {
        for (int j = 0; j < nos; j++)
        {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

/*
    calcular total de arestas(conexoes)
    soma
    retorna

*/
int GrauNos(int **matriz, int nos, int arestas)
{

    int total = 0;
    for (int i = 0; i < nos; i++)
    {
        for (int j = 0; j < arestas; j++)
        {
            if (matriz[i][j])
                total++;
        }
        printf("grau do no %d: %d\n", i + 1, total);
        total = 0;
    }
}
/*
    Calculo grau de no unitario

*/
int GrauNo(int **matriz, int no, int arestas)
{

    int total = 0;
    for (int j = 0; j < arestas; j++)
    {
        if (matriz[no - 1][j])
            total++;
    }
    return total;
}

/*
    Verifica se existe algum Vertices isolado(sem conexoes)

*/
bool isIsolado(int **matriz, int nos, int arestas)
{

    int total = 0;
    for (int i = 1; i < nos; i++)
    {
        for (int j = 1; j < arestas; j++)
        {
            if (matriz[i][j])
                total++;
        }
        if (total == 0)
        {
            printf("O vertice %d está isolado no grafo.\n", i);
            return true;
        }
        total = 0;
    }
    printf("Nao ha vertices isolados no grafo.\n");
    return false;
}
/*
    Calcula e retorna grau maximo do grafo

*/
int printGrauMax(int **matriz, int no, int arestas)
{

    int grau = GrauNo(matriz, 1, arestas);
    int aux = 0;
    for (int i = 0; i < no; i++)
    {
        aux = GrauNo(matriz, i + 1, arestas);
        if (grau < aux)
        {
            printf("Grau Maximo: %d\n", aux);
            return aux;
        }
    }
}
/*
    Calcula e retorna grau minimo do grafo
    arrumar limite superior
*/
int printGrauMin(int **matriz, int no, int arestas)
{

    int grau = GrauNo(matriz, 1, arestas);
    int aux = 0;
    for (int i = 0; i < no; i++)
    {
        aux = GrauNo(matriz, i + 1, arestas);
        if (grau > aux)
        {
            printf("Grau Minimo: %d\n", aux);
            return aux;
        }
    }
}
/*
    Calcule se os vertices(no) tem o mesmo numero de conexoes(arestas)

*/
bool isRegular(int **matriz, int no, int arestas)
{

    int aux, temp = 0;
    aux = GrauNo(matriz, 1, arestas);

    for (int i = 1; i < no; i++)
    {
        temp = GrauNo(matriz, i, arestas);
        if (temp != aux)
        {
            printf("O grafo é irregular.\n");
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
bool isCompleto(int **matriz, int no, int arestas)
{
    int aux, temp = 0;

    for (int i = 1; i < no; i++)
    {
        int aux = GrauNo(matriz, 1, arestas);
        temp = GrauNo(matriz, i + 1, arestas);
        if (aux != temp)
        {
            printf("O grafo não é completo.\n");
            return false;
        }
    }
    printf("O grafo é completo.\n");
    return true;
}

void freeMatriz(int **matriz, int nos)
{
    for (int i = 0; i < nos; i++)
    {
        free(matriz[i]);
    }
    free(matriz);
}

int main()
{

    const char *arquivo = "G1.txt";
    int nos, arestas, isOrientado = 0;

    int **matriz = novaMatriz(arquivo, &nos, &arestas, &isOrientado);

    impMatriz(matriz, nos);
    printf("%d", GrauNos(matriz, nos, arestas));
    printf("\n");
    isIsolado(matriz, nos, arestas);
    printf("\n");

    // REMOVER ARESTAS DO PARAMETRO, CALCULO APENAS COM NOS

    printGrauMax(matriz, nos, arestas);
    printGrauMin(matriz, nos, arestas);
    isRegular(matriz, nos, arestas);
    isCompleto(matriz, nos, arestas);

    // FUNCAO PARA LIBERAR ARQUVIO E MALLOCS

    freeMatriz(matriz, nos);
    return 0;
}
