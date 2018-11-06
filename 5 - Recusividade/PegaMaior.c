#include <stdio.h>
#include <stdlib.h>

int maior(int *v, int tam, int pos){
  if (pos == tam-1){
    return v[pos];
  }
  int a = v[pos];
  int b = maior(v, tam, pos+1);
  if (a > b){
    return a;
  }else{
    return b;
  } 
}

int main(){
  int tam=14;
  int v[tam];
  int a;
  
  for (a=0;a<tam;a++){
    v[a]=a;
  }
  printf("Maior e %d", maior(v, tam, 0));
  return 0;
}
