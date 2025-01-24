#include <stdio.h>
#include <stdlib.h>

int escolha_pivo(int *v, int ini, int mei, int fim){
  if((v[ini] <= v[mei] && v[mei] < v[fim]) || (v[fim] < v[mei] && v[mei] <= v[ini]))
    return mei;
  if((v[mei] < v[ini] && v[ini] < v[fim]) || (v[fim] < v[ini] && v[ini] < v[mei]))
    return ini;
  return fim;
}

void troca(int *v1, int *v2){
  if(*v1 == *v2) return;
  int aux = *v2;
  *v2 = *v1;
  *v1 = aux;
}

int particao(int *v, int p, int r){
  int x, i;
  x = v[r];
  i = p-1;
  for(int j=p; j<r; j++){
    if(v[j] < x){
      i++;
      troca(&v[i], &v[j]);
    }
  }
  troca(&v[i+1], &v[r]);
  return i+1;
}

void quicksort_m1(int *v, int p, int r, int *altura_min, int *altura_max, int profundidade){
  int q;
  if(p < r){
    q = particao(v, p, r);
    quicksort_m1(v, p, q-1, altura_min, altura_max, profundidade + 1);
    quicksort_m1(v, q+1, r, altura_min, altura_max, profundidade + 1);
  } else {
    if (profundidade < *altura_min || *altura_min == -1) *altura_min = profundidade;
    if (profundidade > *altura_max) *altura_max = profundidade;
  }
}

void quicksort_m2(int *v, int p, int r, int *altura_min, int *altura_max, int profundidade){
  int q, pivo, m;
  m = (p+r)/2;
  if(p < r){
    pivo = escolha_pivo(v, p, m, r);
    troca(&v[pivo], &v[r]);
    q = particao(v, p, r);
    quicksort_m2(v, p, q-1, altura_min, altura_max, profundidade + 1);
    quicksort_m2(v, q+1, r, altura_min, altura_max, profundidade + 1);
  } else {
    if (profundidade < *altura_min || *altura_min == -1) *altura_min = profundidade;
    if (profundidade > *altura_max) *altura_max = profundidade;
  }
}

int main(void) {
  int n, x, *v1, *v2, altura_min_m1 = -1, altura_max_m1 = -1, altura_min_m2 = -1, altura_max_m2 = -1;
  scanf("%d", &n);
  v1 = (int*) malloc(n * sizeof(int));
  v2 = (int*) malloc(n * sizeof(int));
  if(v1 == NULL) return 1;
  for(int i=0; i<n; i++){
    scanf("%d", &x);
    v1[i] = x;
    v2[i] = x;
  }
  quicksort_m1(v1, 0, n-1, &altura_min_m1, &altura_max_m1, 0);
  quicksort_m2(v2, 0, n-1, &altura_min_m2, &altura_max_m2, 0);
  free(v1);
  free(v2);
  printf("%d\n%d", altura_max_m1 - altura_min_m1, altura_max_m2 - altura_min_m2);
  return 0;
}
