//8 de agosto del 2025

#include <stdio.h>
#include <math.h>

int main(){
  float Numeros[5] = {1.2,3.5,5.1,7.2,9.5};
  int i;

  printf ("Números: ");
  for (i=0; i<5; i++){
    printf ("%.3f", Numeros[i]);
  }

  printf("\n\nResultados de las funciones\n");
    printf("x        x^2       log(x+1)    exp(x)+cos(x)\n");

    for (i = 0; i < 5; i++) {
        float x = Numeros[i];
        float cuadrado = x * x;
        float logaritmo = log(x + 1);
        float exp_cos = exp(x) + cos(x);

        printf("%.3f   %.3f     %.3f      %.3f\n", x, cuadrado, logaritmo, exp_cos);
    }

    return 0;
}

