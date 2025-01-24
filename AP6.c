#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int procura(char c, char *ordem){
  for(int i=0; i<27; i++){
    if(c == ordem[i]) return i;
  }
  return -1;
}

void counting_sort(char **str, char **str_nova, char *ordem, int ind, int n){
  int C[27], classe;
  for(int i=0; i<27; i++){
    C[i] = 0;
  }
  for(int i=0; i<n; i++){
    classe = procura(str[i][ind], ordem);
    C[classe] = C[classe] + 1;
  }
  for(int i=1; i<27; i++){
    C[i] += C[i-1];
  }
  for(int i=0; i<27; i++){
      printf("%d ", C[i]);
  }
  printf("\n");
  for(int i=n-1; i>=0; i--){
    classe = procura(str[i][ind], ordem);
    str_nova[C[classe]-1] = str[i];
    C[classe] -= 1;
  }
}

void radix_sort(char **str, char **str_nova, char* ordem, int d, int n){
  for(int i=d-1; i>=0; i--){
    counting_sort(str, str_nova, ordem, i, n);
    for(int j=0; j<n; j++){
      str[j] = str_nova[j];
    }
  }
}

int main(void) {
  int n, d=0;
  scanf("%d", &n);
  char **str = malloc(n * sizeof(char*));
  char **str_organizada = malloc(n * sizeof(char*));
  char ordem[27];
  ordem[0]=' ';
  for(int i=1; i<27; i++){
    scanf(" %c", &ordem[i]);
  }
  for(int i=0; i<n; i++){
    str[i] = malloc(21 * sizeof(char));
    scanf("%s", str[i]);
    if(d < strlen(str[i])) d = strlen(str[i]);
    for(int j=0; j<strlen(str[i]); j++){
      if((int) str[i][j] < 'z') str[i][j] = tolower(str[i][j]);
    }
    printf("%s.\n", str[i]);
  }
  printf("%d\n", d);
  for(int i=0; i<n; i++){
    if(strlen(str[i]) < d){
      for(int j=strlen(str[i]); j<d; j++){
        str[i][j] = ' ';
      }
    }
  }
  for(int i=0; i<n; i++){
    str_organizada[i] = malloc(21 * sizeof(char));
  }
  radix_sort(str, str_organizada, ordem, d, n);
  for(int i=0; i<n; i++){
    printf("%s\n", str_organizada[i]);
  }
  for(int i=0; i<n; i++){
    free(str[i]);
  }
  free(str);
  free(str_organizada);
  return 0;
}
