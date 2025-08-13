//Paola Rubí Hernández Floreano
//13 de agosto del 2025


#include <math.h>
#include <stdio.h>

int main(){
  printf("\nResultados con numeros enteros\n");


  int a=3;
  int b=4;
  int c=5;
  int d=7;
  int e=0;

    e = (a + b)*c/d;
    printf ("Primera operación: %d\n", e);

    e= ((a+b)*c)/d;
    printf("Segunda operación: %d\n", e);

    e= a+b*c/d;
    printf("Tercera operación: %d\n", e);

    e = a +(b*c)/d;
    printf("Cuarta operación: %d\n", e);



  printf("\nResultados con numeros flotantes\n");

  float a2=3;
  float b2=4;
  float c2=5;
  float d2=7;
  float e2=0;

    e2 = (a2 + b2)*c2/d2;
    printf ("Primera operación: %f\n", e2);

    e2=((a2+b2)*c2)/d2;
    printf("Segunda operación: %f\n", e2);

    e2= a2+b2*c2/d2;
    printf("Tercera operación: %f\n", e2);

    e2 = a2 +(b2*c2)/d2;
    printf("Cuarta operación: %f\n", e2);

    return 0;
}