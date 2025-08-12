#include <math.h>
#include <stdio.h>

int main(){
  int Numero[5];
  Numero[0]=1;
  Numero[1]=2;
  Numero[2]=3;
  Numero[3]=4;
  Numero[4]=5;
  float Resultados [5];

  int indx;

printf ("x\t x^2 \t log(x+1) \t exp (x)+ cos(x)\n");
  for (indx=0; indx<5; indx++){
      if (Numero[indx]%2 ==0){
        Resultados[indx]= log10(Numero[indx]+1);
        printf ("%d %f\n", Numero[indx], log10(Numero[indx]+1));
      } else {
        Resultados[indx] = exp(Numero[indx])+ cos(Numero[indx]);
        printf ("x=%d \n exp(x)+cos(x)= %f\n", Numero[indx], Resultados[indx]);
      }

  }

       printf("\n\nResultados\n\n");
    for (indx=0; indx<5; indx++){
    printf("%f\n", Resultados [indx]);
    }
    
    printf ("Pi + Pi= %f", 3.1415926534 + 3.1415926534);
    return 0;
}
