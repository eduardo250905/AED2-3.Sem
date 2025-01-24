#include <stdio.h>
#include <stdlib.h>

typedef struct SNo {
  int *chaves;
  int n;
  struct SNo **filhos;
  struct SNo *pai;
} TNo;

typedef TNo *PNo;

PNo criar_no(int m) {
  PNo novo = (PNo)malloc(sizeof(TNo));
  novo->n = 0;
  novo->pai = NULL;
  novo->chaves = (int *)malloc(2 * m * sizeof(int *));
  novo->filhos = (PNo *)malloc((2 * m + 1) * sizeof(PNo));
  for (int i = 0; i < 2 * m + 1; i++) {
    novo->filhos[i] = NULL;
  }
  return novo;
}

int posicao(PNo no, int chave) {
  int pos = 0;
  while (pos < no->n && chave > no->chaves[pos]) {
    pos++;
  }
  return pos;
}

PNo busca(PNo no, int chave) {
  int pos = posicao(no, chave);
  if (no->filhos[pos] == NULL || (pos < no->n && no->chaves[pos] == chave)) {
    return no;
  }
  return busca(no->filhos[pos], chave);
}

void insere(PNo no, int m, int chave, PNo pt);

void particiona(PNo no, int m, int chave, int pos, PNo pt) {
  PNo novo = criar_no(m);
  int meio = m;
  for (int i = no->n; i > pos; i--) {
    no->chaves[i] = no->chaves[i - 1];
    no->filhos[i + 1] = no->filhos[i];
  }
  no->chaves[pos] = chave;
  no->filhos[pos + 1] = pt;
  if (pt != NULL) {
    pt->pai = no;
  }
  no->n += 1;
  for (int i = meio + 1, j = 0; i < no->n; i++, j++) {
    novo->chaves[j] = no->chaves[i];
    novo->filhos[j] = no->filhos[i];
    if (novo->filhos[j] != NULL) {
      novo->filhos[j]->pai = novo;
    }
  }
  novo->filhos[m] = no->filhos[no->n];
  if (novo->filhos[m] != NULL) {
    novo->filhos[m]->pai = novo;
  }
  novo->n = m;
  no->n = meio;
  if (no->pai == NULL) {
    PNo pai = criar_no(m);
    pai->chaves[0] = no->chaves[meio];
    pai->filhos[0] = no;
    pai->filhos[1] = novo;
    pai->n = 1;
    no->pai = pai;
    novo->pai = pai;
    } else {
      insere(no->pai, m, no->chaves[meio], novo);
  }
}

PNo insere_folha(PNo raiz, int m, int chave) {
  if (raiz != NULL) {
    PNo no = busca(raiz, chave);
    int pos = posicao(no, chave);
    if (pos == no->n || chave != no->chaves[pos]) {
      insere(no, m, chave, NULL);
      while (raiz->pai != NULL) {
        raiz = raiz->pai;
      }
    }
  } else {
    raiz = criar_no(m);
    raiz->chaves[0] = chave;
    raiz->n = 1;
  }
  return raiz;
}

void insere(PNo no, int m, int chave, PNo pt) {
  int pos = posicao(no, chave);
  if (no->n < 2 * m) {
    for (int i = no->n; i > pos; i--) {
      no->chaves[i] = no->chaves[i - 1];
      no->filhos[i + 1] = no->filhos[i];
    }
    no->chaves[pos] = chave;
    no->filhos[pos + 1] = pt;
    if (pt != NULL) {
      pt->pai = no;
    }
    no->n += 1;
  } else {
    particiona(no, m, chave, pos, pt);
  }
}

void libera(PNo *raiz, int m){
  if(raiz){
    for(int i=0; i<=(*raiz)->n; i++){
      libera(&(*raiz)->filhos[i], m);
    }
    free((*raiz)->chaves);
    free((*raiz)->filhos);
    free(*raiz);
  }
}

int main(void) {
  int m, n, pos;
  PNo raiz = NULL, aux;
  scanf("%d", &m);
  scanf("%d", &n);
  while (n >= 0) {
    raiz = insere_folha(raiz, m, n);
    scanf("%d", &n);
  }
  scanf("%d", &n);
  printf("%d\n", raiz->n);
  aux = busca(raiz, n);
  pos = posicao(aux, n);
  if ((pos < aux->n) && (aux->chaves[pos] == n)) {
    printf("%d\n", aux->n);
    for (int i = 0; i < aux->n; i++) {
      printf("%d ", aux->chaves[i]);
    }
  } else {
    printf("Valor nao encontrado");
  }
  libera(&raiz, m);
  return 0;
}
