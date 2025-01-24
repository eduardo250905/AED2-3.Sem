#include <stdio.h>
#include <stdlib.h>

typedef struct sAVL{
  int chave;
  int fb;
  struct sAVL *esq, *dir;
}tAVL;

typedef tAVL *pAVL;

typedef struct sAVP{
  int chave;
  int cor; // 0: negro; 1: vermelho
  struct sAVP *esq, *dir, *pai;
}tAVP;

typedef tAVP *pAVP;
// #########-CODIGO AVL-#########
pAVL CriarNovoNoAVL(int chave){
  pAVL novo = (pAVL) malloc(sizeof(tAVL));
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

int alturaAVL(pAVL no){
  if(!no) return -1;
  return 1+max(alturaAVL(no->esq), alturaAVL(no->dir));
}

int FatorBalanceamento(pAVL no){
  int fb = alturaAVL(no->esq) - alturaAVL(no->dir);
  return fb;
}

pAVL buscaAVL(int valor, pAVL raiz){
  pAVL aux = raiz;
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

pAVL MenorADireita(pAVL p){
  pAVL aux = p->dir;
  while(aux->esq != NULL){
    aux = aux->esq;
  }
  return aux;
}

void AVLrotacaoLL(pAVL *a){
  pAVL b;
  b = (*a)->esq;
  (*a)->esq = b->dir;
  b->dir = *a;
  (*a)->fb = FatorBalanceamento(*a);
  b->fb = FatorBalanceamento(b);
  *a = b;
}

void AVLrotacaoRR(pAVL *a){
  pAVL b;
  b = (*a)->dir;
  (*a)->dir = b->esq;
  b->esq = *a;
  (*a)->fb = FatorBalanceamento(*a);
  b->fb = FatorBalanceamento(b);
  *a = b;
}

void AVLrotacaoLR(pAVL *a){
  AVLrotacaoRR(&(*a)->esq);
  AVLrotacaoLL(a);
}

void AVLrotacaoRL(pAVL *a){
  AVLrotacaoLL(&(*a)->dir);
  AVLrotacaoRR(a);
}

int insereAVL(pAVL *raiz, int valor, int *rotacoes){
  if(*raiz == NULL){
    pAVL novo = CriarNovoNoAVL(valor);
    *raiz = novo;
    return 1;
  }
  pAVL atual = *raiz;
  int res;
  if(valor < atual->chave){
    res = insereAVL(&(atual->esq), valor, rotacoes);
    if(res == 1){
      atual->fb = FatorBalanceamento(atual);
      if(atual->fb >= 2){
        if(valor < atual->esq->chave){
          AVLrotacaoLL(raiz);
          *rotacoes += 1;
        }else{
          AVLrotacaoLR(raiz);
          *rotacoes += 1;
        }
      }
    }
  }else if(valor > atual->chave){
    res = insereAVL(&(atual->dir), valor, rotacoes);
    if(res == 1){
      atual->fb = FatorBalanceamento(atual);
      if(atual->fb <= -2){
        if(atual->dir->chave < valor){
          AVLrotacaoRR(raiz);
          *rotacoes += 1;
        }else{
          AVLrotacaoRL(raiz);
          *rotacoes += 1;
        }
      }
    }
  }else{
    return 0;
  }
  return res;
}

void imprimeAVL(pAVL raiz){
  if(raiz == NULL) return;
  printf("%d ", raiz->chave);
  imprimeAVL(raiz->esq);
  imprimeAVL(raiz->dir);
}

void inicializaAVL(pAVL *raiz){
  *raiz = NULL;
}

void liberaAVL(pAVL raiz){
  if(raiz == NULL) return;
  liberaAVL(raiz->esq);
  liberaAVL(raiz->dir);
  free(raiz);
}
// #########-CODIGO AVP-#########
pAVP CriarNovoNoAVP(int chave){
  pAVP novo = (pAVP) malloc(sizeof(tAVP));
  novo->chave = chave;
  novo->esq = NULL;
  novo->dir = NULL;
  novo->pai = NULL;
  novo->cor = 1; // Inicializa vermelho
  return novo;
}

int alturaAVP(pAVP no){
  if(!no) return -1;
  return 1 + max(alturaAVP(no->dir), alturaAVP(no->esq));
}

int alturapretaAVP(pAVP no){
  if(!no) return 0;
  if(no->cor == 1) return 0+max(alturapretaAVP(no->esq), alturapretaAVP(no->dir));
  else return 1+max(alturapretaAVP(no->esq), alturapretaAVP(no->dir));
}

pAVP buscaAVP(int valor, pAVP raiz){
  pAVP aux = raiz;
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

void AVProtacaoL(pAVP *raiz, pAVP a){
  pAVP b = a->dir;
  a->dir = b->esq;
  if(b->esq != NULL){
    b->esq->pai = a;
  }
  b->pai = a->pai;
  if(a->pai == NULL){
    *raiz = b;
  }else if(a == a->pai->esq){
    a->pai->esq = b;
  }else{
    a->pai->dir = b;
  }
  b->esq = a;
  a->pai = b;
}

void AVProtacaoR(pAVP *raiz, pAVP a){
  pAVP b = a->esq;
  a->esq = b->dir;
  if(b->dir != NULL){
    b->dir->pai = a;
  }
  b->pai = a->pai;
  if(a->pai == NULL){
    *raiz = b;
  }else if(a == a->pai->esq){
    a->pai->esq = b;
  }else{
    a->pai->dir = b;
  }
  b->dir = a;
  a->pai = b;
}

void balancear(pAVP *raiz, pAVP novo, int *mud_cores, int *rotacoes) {
  while (novo->pai != NULL && novo->pai->cor == 1) {
    if (novo->pai == novo->pai->pai->esq) {
      pAVP tio = novo->pai->pai->dir;
      if (tio != NULL && tio->cor == 1) {
        // Caso 1: tio é vermelho
        novo->pai->cor = 0;
        tio->cor = 0;
        novo->pai->pai->cor = 1;
        *mud_cores += 3;
        novo = novo->pai->pai;
      } 
      else {
        if (novo == novo->pai->dir) {
          // Caso 2a: pai é filho esquerdo e novo é filho direito
          novo = novo->pai;
          AVProtacaoL(raiz, novo);
          *rotacoes += 1;
        }
        // Caso 3a: pai é filho esquerdo e novo é filho esquerdo
        novo->pai->cor = 0;
        novo->pai->pai->cor = 1;
        *mud_cores += 2;
        AVProtacaoR(raiz, novo->pai->pai);
        *rotacoes += 1;
      }
    } 
    else {
      pAVP tio = novo->pai->pai->esq;
      if (tio != NULL && tio->cor == 1) {
        // Caso 1: tio é vermelho
        novo->pai->cor = 0;
        tio->cor = 0;
        novo->pai->pai->cor = 1;
        *mud_cores += 3;
        novo = novo->pai->pai;
      } 
      else {
        if (novo == novo->pai->esq) {
          // Caso 2b: pai é filho direito e novo é filho esquerdo
          novo = novo->pai;
          AVProtacaoR(raiz, novo);
          *rotacoes += 1;
        }
        // Caso 3b: pai é filho direito e novo é filho direito
        novo->pai->cor = 0;
        novo->pai->pai->cor = 1;
        *mud_cores += 2;
        AVProtacaoL(raiz, novo->pai->pai);
        *rotacoes += 1;
      }
    }
  }
  if((*raiz)->cor == 1) mud_cores += 1;
  (*raiz)->cor = 0; // Ajusta cor da raiz para preto
}

void insereAVP(pAVP *raiz, int valor, int *mud_cores, int *rotacoes) {
  pAVP novo = CriarNovoNoAVP(valor);
  pAVP pai = NULL;
  pAVP aux = *raiz;
  while (aux != NULL) {
    pai = aux;
    if (novo->chave < aux->chave)
      aux = aux->esq;
    else
      aux = aux->dir;
  }
  novo->pai = pai;
  if (pai == NULL){
    *raiz = novo;
  }
  else if(novo->chave < pai->chave){
    pai->esq = novo;
  }
  else{
    pai->dir = novo;
  }
  balancear(raiz, novo, mud_cores, rotacoes);
}

void liberaAVP(pAVP raiz){
  if(raiz == NULL) return;
  liberaAVP(raiz->esq);
  liberaAVP(raiz->dir);
  free(raiz);
}

void inicializaAVP(pAVP *raiz){
  *raiz = NULL;
}

int main(void) {
  int n = 0, mud_cores=0, rotAVP=0, rotAVL=0;
  pAVL raizAVL;
  pAVP raizAVP;
  inicializaAVL(&raizAVL);
  inicializaAVP(&raizAVP);
  while (n >= 0) {
    scanf("%d", &n);
    if (n >= 0) {
      insereAVL(&raizAVL, n, &rotAVL);
      insereAVP(&raizAVP, n, &mud_cores, &rotAVP);
    }
  }
  printf("%d, %d, %d", alturaAVL(raizAVL), alturaAVL(raizAVL->esq)+1, alturaAVL(raizAVL->dir)+1);
  printf("\n");
  printf("%d, %d, %d", alturaAVP(raizAVP), alturaAVP(raizAVP->esq)+1, alturaAVP(raizAVP->dir)+1);
  printf("\n");
  printf("%d", alturapretaAVP(raizAVP));
  printf("\n");
  printf("%d, %d, %d", mud_cores, rotAVP, rotAVL);
  liberaAVL(raizAVL);
  liberaAVP(raizAVP);
  return 0;
}
