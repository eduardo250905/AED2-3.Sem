#include <stdio.h>
#include <stdlib.h>

typedef struct SNo{
  int chave;
  int fb;
  struct SNo *esq, *dir;
}TNo;

typedef TNo *PNo;

PNo CriarNovoNo(int chave){
  PNo novo = (PNo) malloc(sizeof(TNo));
  novo->chave = chave;
  novo->esq = NULL;
  novo->dir = NULL;
  novo->fb = 0;
  return novo;
}

int max(int a, int b){
  if(a>b) return a;
  return b;
}

int altura(PNo no){
  if(!no) return -1;
  return 1+max(altura(no->esq), altura(no->dir));
}

int FatorBalanceamento(PNo no){
  int fb = altura(no->esq) - altura(no->dir);
  return fb;
}

PNo busca(int valor, PNo raiz){
  PNo aux = raiz;
  while(aux != NULL){
    if(valor == aux->chave){
      return aux;
    }else if(valor > aux->chave){
      aux = aux->dir;
    }else if(valor < aux->chave){
      aux = aux->esq;
    }
  }
  return aux;
}

PNo MenorADireita(PNo p){
  PNo aux = p->dir;
  while(aux->esq != NULL){
    aux = aux->esq;
  }
  return aux;
}

void rotacaoLL(PNo *a){
  PNo b;
  b = (*a)->esq;
  (*a)->esq = b->dir;
  b->dir = *a;
  (*a)->fb = FatorBalanceamento(*a);
  b->fb = FatorBalanceamento(b);
  *a = b;
}

void rotacaoRR(PNo *a){
  PNo b;
  b = (*a)->dir;
  (*a)->dir = b->esq;
  b->esq = *a;
  (*a)->fb = FatorBalanceamento(*a);
  b->fb = FatorBalanceamento(b);
  *a = b;
}

void rotacaoLR(PNo *a){
  rotacaoRR(&(*a)->esq);
  rotacaoLL(a);
}

void rotacaoRL(PNo *a){
  rotacaoLL(&(*a)->dir);
  rotacaoRR(a);
}

int insere(PNo *raiz, int valor){
  if(*raiz == NULL){
    PNo novo = CriarNovoNo(valor);
    *raiz = novo;
    return 1;
  }
  PNo atual = *raiz;
  int res;
  if(valor < atual->chave){
    res = insere(&(atual->esq), valor);
    if(res == 1){
      atual->fb = FatorBalanceamento(atual);
      if(atual->fb >= 2){
        if(valor < atual->esq->chave){
          rotacaoLL(raiz);
        }else{
          rotacaoLR(raiz);
        }
      }
    }
  }else if(valor > atual->chave){
    res = insere(&(atual->dir), valor);
    if(res == 1){
      atual->fb = FatorBalanceamento(atual);
      if(atual->fb <= -2){
        if(atual->dir->chave < valor){
          rotacaoRR(raiz);
        }else{
          rotacaoRL(raiz);
        }
      }
    }
  }else{
    return 0;
  }
  return res;
}

int remover(PNo *raiz, int valor){
  if(raiz == NULL) return 0;
  int res;
  if(valor < (*raiz)->chave){
    res = remover(&((*raiz)->esq), valor);
    if(res == 1){
      (*raiz)->fb = FatorBalanceamento(*raiz);
      if((*raiz)->fb <= -2){
        if(altura((*raiz)->dir->esq) <= altura((*raiz)->dir->dir)){
          rotacaoRR(raiz);
        }else{
          rotacaoRL(raiz);
        }
      }
    }
  }else if(valor > (*raiz)->chave){
    res = remover(&((*raiz)->dir), valor);
    if(res == 1){
      (*raiz)->fb = FatorBalanceamento(*raiz);
      if((*raiz)->fb >= 2){
        if(altura((*raiz)->esq->dir) <= altura((*raiz)->esq->esq)){
          rotacaoLL(raiz);
        }else{
          rotacaoLR(raiz);
        }
      }
    }
  }
  if((*raiz)->chave == valor){
    if((*raiz)->esq == NULL || (*raiz)->dir == NULL){
      PNo lixo = *raiz;
      if((*raiz)->esq != NULL){
        *raiz= (*raiz)->esq;
      }else{
        *raiz = (*raiz)->dir;
      }
      free(lixo);
    }else{
      PNo sub = MenorADireita(*raiz);
      (*raiz)->chave = sub->chave;
      remover(&((*raiz)->dir), (*raiz)->chave);
      (*raiz)->fb = FatorBalanceamento(*raiz);
      if((*raiz)->fb >= 2){
        if(altura((*raiz)->esq->dir) <= altura((*raiz)->esq->esq)){
          rotacaoLL(raiz);
        }else{
          rotacaoLR(raiz);
        }
      }
    }
    return 1;
  }
  return res;
}

void libera(PNo raiz){
  if(raiz == NULL) return;
  libera(raiz->esq);
  libera(raiz->dir);
  free(raiz);
}

void inicializa(PNo *raiz){
  *raiz = NULL;
}

int main(void) {
  int n = 0;
  PNo raiz, aux;
  inicializa(&raiz);
  while (n >= 0) {
    scanf("%d", &n);
    if (n >= 0) {
      insere(&raiz, n);
    }
  }
  printf("%d, %d, %d\n", altura(raiz), altura(raiz->esq) + 1, altura(raiz->dir) + 1);
  n = 0;
  while (n >= 0) {
    scanf("%d", &n);
    if (n >= 0) {
      aux = busca(n, raiz);
      if (aux == NULL) {
        insere(&raiz, n);
      } else {
        remover(&raiz, n);
      }
    }
  }
  scanf("%d", &n);
  aux = busca(n, raiz);
  if (aux == NULL) {
    printf("Valor nao encontrado");
  } else {
    printf("%d, %d, %d", altura(aux), altura(aux->esq) + 1, altura(aux->dir) + 1);
  }
  libera(raiz);
  return 0;
}
