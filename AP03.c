#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int val, pos;
    struct no *prox;
} TNO;

typedef TNO* PNO;

void merge(PNO *lista, PNO esq, PNO dir) {
  PNO lista_aux = NULL, novo, aux = NULL;
  int cont = 1;
  while(esq != NULL && dir != NULL) {
    novo = malloc(sizeof(TNO));
    if(esq->val <= dir->val) {
      novo->val = esq->val;
      esq = esq->prox;
    } 
    else{
      novo->val = dir->val;
      dir = dir->prox;
    }
    novo->pos = cont;
    novo->prox = NULL;
    cont++;
    if(lista_aux == NULL) {
      lista_aux = novo;
      aux = novo;
    } 
    else{
      aux->prox = novo;
      aux = aux->prox;
    }
  }
  while(esq != NULL) {
    novo = malloc(sizeof(TNO));
    novo->val = esq->val;
    novo->prox = NULL;
    novo->pos = cont;
    aux->prox = novo;
    aux = aux->prox;
    cont++;
    esq = esq->prox;
  }
  while(dir != NULL) {
    novo = malloc(sizeof(TNO));
    novo->val = dir->val;
    novo->prox = NULL;
    novo->pos = cont;
    aux->prox = novo;
    aux = aux->prox;
    cont++;
    dir = dir->prox;
  }
  *lista = lista_aux;
}

int mergesort(PNO *lista, int N, int nivel) {
  if(N <= 1) {
    return nivel;
  }
  int n = (N + 1) / 2;
  PNO meio = *lista;
  for(int i = 0; i < n - 1; i++) {
      meio = meio->prox;
  }
  PNO esq = *lista;
  PNO dir = meio->prox;
  meio->prox = NULL;
  int nivel_esq = mergesort(&esq, n, nivel + 1);
  int nivel_dir = mergesort(&dir, N - n, nivel + 1);
  merge(lista, esq, dir);
  if(nivel_esq > nivel_dir){
    return nivel_esq;
  }
  else{
    return nivel_dir;
  }
}

void libera(PNO lista) {
  PNO lixo;
  while(lista != NULL) {
    lixo = lista;
    lista = lista->prox;
    free(lixo);
  }
}

int main(void) {
  int N, v, nivel_max;
  PNO lista = NULL, novo, aux = NULL;
  scanf("%d", &N);
  for(int i = 0; i < N; i++) {
    scanf("%d", &v);
    novo = (PNO)malloc(sizeof(TNO));
    novo->val = v;
    novo->pos = i + 1;
    novo->prox = NULL;
    if(lista == NULL) {
      lista = novo;
    } 
    else{
      aux->prox = novo;
    }
    aux = novo;
  }
  nivel_max = mergesort(&lista, N, 0);
  aux = lista;
  while(aux != NULL) {
    printf("%d ", aux->val);
    aux = aux->prox;
  }
  printf("\n%d", nivel_max);
  libera(lista);
  return 0;
}
