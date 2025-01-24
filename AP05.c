#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void troca(char* str1, char* str2){
  char aux[strlen(str1) + 1];
  strcpy(aux, str1);
  strcpy(str1, str2);
  strcpy(str2, aux);
}

void MAX_HEAPIFY(char** str, int n, int i){
  int l = 2*i, r = 2*i+1, max;
  if(l <= n && strcmp(str[l], str[i]) > 0){
    max = l;
  }else max = i;
  if(r <= n && strcmp(str[r],str[max]) > 0){
    max = r;
  }
  if(max != i){
    troca(str[i], str[max]);
    MAX_HEAPIFY(str, n, max);
  }
}

void BUILD_MAX_HEAP(char** str, int n){
  for(int i=n/2; i>=1; i--){
    MAX_HEAPIFY(str, n, i);
  }
}

char* HEAP_EXTRACT_MAX(char** str, int *n){
  char *max;
  int last;
  if(*n>=1){
    max = str[1];
    last = *n;
    str[1] = str[last];
    *n-=1;
    MAX_HEAPIFY(str, *n, 1);
  }
  return max;
}

char** HEAPSORT(char** str, int n){
  char** str_org;
  int aux = n;
  str_org = (char**) malloc((n+1)*sizeof(char*));
  for(int i = 1; i <= n; i++) {
    str_org[i] = (char*) malloc((strlen(str[i]) + 1) * sizeof(char));
    strcpy(str_org[i], str[i]);
  }
  while(n > 0){
    strcpy(str_org[n], HEAP_EXTRACT_MAX(str, &aux));
    n--;
  }
  return str_org;
}

int main(void) {
  char **string, **nova_string, **string_organizada, c;
  int n, m, j, cont=0, invalido=0;
  scanf("%d", &n);
  string = (char**)malloc(n*sizeof(char*));
  for(int i=0; i<n; i++){
    string[i] = (char*) malloc(21*sizeof(char));
    scanf("%20s", string[i]);
    for(int j=0; j<strlen(string[i]); j++){
      if(string[i][j] < 'a' || string[i][j] > 'z'){
        printf("a palavra %s eh invalida", string[i]);
        return 0;
      }
    }
  }
  scanf("%d", &m);
  if(m < 0 || m >= n) return -1;
  nova_string = (char**) malloc((m+1)*sizeof(char*));
  for(int i=1; i<=m; i++){
    scanf("%d", &j);
    if(j >= n || j < 0) return -1;
    nova_string[i] = (char*) malloc((strlen(string[j]) + 1) * sizeof(char));
    strcpy(nova_string[i], string[j]);
  }
  BUILD_MAX_HEAP(nova_string, m);
  printf("build_heap:");
  for(int i=1; i<=m; i++){
    printf(" %s", nova_string[i]);
  }
  string_organizada = HEAPSORT(nova_string, m);
  printf("\npalavras:");
  for(int i=1; i<=m; i++){
    printf(" %s", string_organizada[i]);
  }
  free(string);
  free(nova_string);
  free(string_organizada);
  return 0;
}
