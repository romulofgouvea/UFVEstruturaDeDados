#include <stdio.h>
#include <stdlib.h>

int fib(int num){
  if (num == 0 || num == 1){
    return num;
  }
  return fib(num-1) + fib(num-2);
}

int main(){
  int a, tam = 15;
  for (a=0;a<tam; a++){
    printf("%d ", fib(a));
  }
  return 0;
}
