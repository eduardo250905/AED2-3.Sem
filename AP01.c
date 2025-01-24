#include <stdio.h>

int quant_livros(int quant_vales, int v){
  int l=0;
  if(quant_vales >= v){
    l = quant_vales / v;
    l+=quant_livros(l+(quant_vales % v), v);
  }
  return l;
}

int main(void) {
  int N, d, p, v, i, l;
  scanf("%d", &N);
  if(N > 10 || N < 1){
    return -1;
  }
  for(i=0; i<N; i++){
    scanf("%d", &d);
    scanf("%d", &p);
    scanf("%d", &v);
    if(d<0 || p < 1 || v <= 1){
      return -1;
    }
    l = d / p;
    l+=quant_livros(l, v);
    printf("%d\n", l);
  }
  return 0;
}
