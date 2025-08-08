//8 de agosto del 2025

#include <studio.h>
#include <math.h>

int main(){
  float Numeros[5] = {1.2,3.5,5.1,7.2,9.5};
  int i;

  printf ("Números: ")
  for (i=0; i<5; i++){
    printf ("%.3f", Numeros[1]);
  }

  printf ("Resultados de las funciones /n");
  printf ("f(x) = x^2     f(x) = log(x+1)    f(x) = exp(x) + cos(x)/n");

  for (int i=0; i<5; i++){
    float x= Numeros[i];
      float x^2= x*x;
      float log(x+1)= log(x+1);
      float exponencial_cos= exp(x)+ cos(x);
    
    printf ("%.3f     %.3f      %.3f      %.3f", x, x^2, log(x+1), exponencial_cos);
  }
  return 0;
}