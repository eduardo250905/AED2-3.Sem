#include <stdio.h>
#include <stdlib.h>

typedef struct elemento{
  int valor;
  char tipo;
  struct elemento *prox;
  struct elemento *ant;
}elemento;

typedef elemento* Pelemento;

Pelemento organiza(Pelemento lista, Pelemento novo){
  Pelemento aux;
  if(lista->valor >= novo->valor){
    novo->prox = lista;
    novo->ant = NULL;
    lista->ant = novo;
    lista = novo;
  }else{
    for(aux = lista; aux != NULL; aux=aux->prox){
      if(aux->valor >= novo->valor){
        novo->prox = aux;
        novo->ant = aux->ant;
        aux->ant->prox = novo;
        aux->ant = novo;
        break;
      }
      if(aux->prox == NULL){
        aux->prox = novo;
        novo->ant = aux;
        break;
      }
    }
  }
  return lista;
}

int compara(Pelemento pot, Pelemento mic, int N){
  Pelemento aux1 = pot, aux2 = mic;
  int i, j, resultado = 1;
  for(i=0; i < N; i++){
    if(aux1->valor <= aux2->valor){
        resultado = 0;
        break;
      aux1 = aux1->prox;
      aux2 = aux2->prox;
    }
  }
  return resultado;
}

void libera(Pelemento e){
  Pelemento aux;
  while(e != NULL){
    aux = e;
    e = e->prox;
    free(aux);
  }
}

int main(void) {
  int N, pot, mic, i, v, resultado;
  Pelemento lista_pot=NULL, lista_mic=NULL, novo;
  scanf("%d", &N);
  for(i=0; i<N; i++){
    scanf("%d", &v);
    novo = (Pelemento) malloc(sizeof(elemento));
    novo->valor = v;
    novo->tipo = 'm';
    if(lista_mic == NULL){
      lista_mic = novo;
      lista_mic->ant = NULL;
      lista_mic->prox = NULL;
    }else{
      lista_mic = organiza(lista_mic, novo);
    }
  }
  for(i=0; i<N; i++){
    scanf("%d", &v);
    novo = (Pelemento) malloc(sizeof(elemento));
    novo->valor = v;
    novo->tipo = 'p';
    if(lista_pot == NULL){
      lista_pot = novo;
      lista_pot->ant = NULL;
      lista_pot->prox = NULL;
    }else{
      lista_pot = organiza(lista_pot, novo);
    }
  }
  resultado = compara(lista_pot, lista_mic, N);
  if(resultado == 0) printf("nao");
  else printf("sim");
  libera(lista_mic);
  libera(lista_pot);
  return 0;
}
