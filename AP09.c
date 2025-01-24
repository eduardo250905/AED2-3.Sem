#include <stdio.h>
#include <stdlib.h>

typedef struct sNo{
  int chave;
  struct sNo *prox, *ant;
}TNo;

typedef TNo *PNo;

typedef struct Slista{
  PNo inicio;
  PNo ultimo;
}Tlista;

typedef Tlista *Plista;

void inicializa_hash(Plista *hash, int tam_hash){
  for (int i=0; i<tam_hash; i++){
    hash[i] = NULL;
  }
}

void inserir_hash(Plista *hash, int tam_hash, int n){
  int pos = n % tam_hash;
  PNo novo = (PNo) malloc(sizeof(TNo));
  novo->chave = n;
  novo->prox = NULL;
  if(hash[pos] == NULL){
    hash[pos] = (Plista) malloc(sizeof(Tlista));
    hash[pos]->inicio = novo;
    hash[pos]->ultimo = novo;
    novo->ant = NULL;
  }else{
    hash[pos]->ultimo->prox = novo;
    novo->ant = hash[pos]->ultimo;
    hash[pos]->ultimo = novo;
  }
}

PNo pesquisa_hash(Plista *hash, PNo *ant, int tam_hash, int n){
  int pos = n % tam_hash;
  if(hash[pos] == NULL) return NULL;
  for(PNo aux=hash[pos]->inicio; aux != NULL; aux=aux->prox){
    if(aux->chave == n) return aux;
    *ant = aux;
  }
  return NULL;
}

int remover_hash(Plista *hash, int tam_hash, int n){
  int pos = n % tam_hash;
  PNo aux, ant=NULL;
  aux = pesquisa_hash(hash, &ant, tam_hash, n);
  if(aux == NULL) return 0;
  if(aux == hash[pos]->inicio){
    if(aux == hash[pos]->ultimo){
      free(aux);
      hash[pos] = NULL;
      free(hash[pos]);
      return 1;
    }
    hash[pos]->inicio = aux->prox;
  }
  if(aux == hash[pos]->ultimo){ 
    hash[pos]->ultimo = ant;
  }
  if(ant != NULL) ant->prox = aux->prox;
  if(aux->prox != NULL) aux->prox->ant = ant;
  free(aux);
  return 1;
}

void imprime_linha(Plista *hash, int tam_hash, int l){
  printf("[%d] ", l);
  if(l >= tam_hash || hash[l] == NULL) return;
  for(PNo aux = hash[l]->inicio; aux != NULL; aux=aux->prox){
    printf("%d ", aux->chave);
  }
}

void libera_hash(Plista *hash, int tam_hash){
  PNo aux, lixo;
  for(int i=0; i<tam_hash; i++){
    if(hash[i] != NULL){
      aux = hash[i]->inicio;
      while(aux != NULL){
        lixo = aux;
        aux = aux->prox;
        free(lixo);
      }
      free(hash[i]);
    }
  }
}

int main(void) {
  int tam_hash, n;
  scanf("%d", &tam_hash);
  Plista hash[tam_hash];
  inicializa_hash(hash, tam_hash);
  scanf("%d", &n);
  while(n != -1){
    inserir_hash(hash, tam_hash, n);
    scanf("%d", &n);
  }
  scanf("%d", &n);
  if(remover_hash(hash, tam_hash, n) != 1){
    printf("Valor nao encontrado\n");
  }
  scanf("%d", &n);
  imprime_linha(hash, tam_hash, n);
  libera_hash(hash, tam_hash);
  return 0;
}
