#include <stdio.h>
#include <stdlib.h>

/*

ex3 - Slide 3

rotacoes rr,ll, lr e rl (repassar a mao mudança de ponteiros)
inserção e remocão
balanceamento utilizando as rotações s

*/

typedef struct noAvl
{
    int info;
    int fb;
    struct noAvl *esq;
    struct noAvl *dir;
    struct noAvl *pai;
} noAvl;


void RR(noAvl *no)
{
    noAvl *aux;
    no->esq = aux;
    aux->dir->pai = no;
    no->esq = aux->dir;
    aux->dir = no;
    aux->pai = no->pai;
    no->pai = aux;
    no = aux;
}


void LL(noAvl *no)
{
    noAvl *aux;
    no->dir = aux;
    aux->esq->pai = no;
    no->dir = aux->esq;
    aux->esq = no;
    aux->pai = no->pai;
    no->pai = aux;
    no = aux;
}

void RL(noAvl *no){
    RR(no->dir);
    LL(no);
}

void LR(noAvl *no){
    LL(no->esq);
    RR(no);
}

noAvl *createNoAvl(){
    noAvl *aux = malloc(sizeof(noAvl));
    aux->pai = NULL;
    aux->esq = NULL;
    aux->dir = NULL;
    aux->fb = 0;
    return aux;
}

int isBalanceado(noAvl *no){

    if(no->fb != -1 && no->fb != 1 && no->fb !=0){
        printf("no %d desbalaceado, fator %d.",no->info,no->fb);
        return 1;
    }
    return 0;
}

void balanceamento(noAvl *no){

    if(no->fb == 2){
        if(no->esq->fb == -1){ //dupla rotacao LR
            LR(no);
        }
    }
    if(no->fb == -2){
        if(no->dir->fb == 1){
            RL(no);
        }
    }
}

void addNo(int n){

    //verificar bf
    //add
    //rotacao se necessario

}

void removeNo(int n){

    //verificar bf
    //add
    //rotacao se necessario

}

void printArvore(noAvl *no){

}

noAvl antecessor(noAvl *no){

}

noAvl sucessor(noAvl *no){
    
}

void imprimeArvore(noAvl *raiz, int espaco, char *prefixo, int isEsquerda) {
    if (raiz == NULL) return;

    // Ajusta prefixo para exibir a estrutura correta
    printf("%s", prefixo);
    printf("%s── %d\n", isEsquerda ? "├" : "└", raiz->info);

    // Atualiza o prefixo para os filhos
    char novoPrefixo[100];
    snprintf(novoPrefixo, sizeof(novoPrefixo), "%s%s   ", prefixo, isEsquerda ? "│" : " ");

    if (raiz->dir) imprimeArvore(raiz->dir, espaco + 1, novoPrefixo, 1);
    if (raiz->esq) imprimeArvore(raiz->esq, espaco + 1, novoPrefixo, 0);
}

void imprimeFormatado(noAvl* arv){
    imprimeArvore(arv,0,"",0);
}



int main()
{





    return 0;
}
