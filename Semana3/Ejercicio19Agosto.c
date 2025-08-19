#include <stdio.h>
#include <math.h>

int main(void) {
    float x, Es, VV;
    int n;
    printf("Ingrese los valores correspondientes para X y el error porcentual esperado");
    scanf ("%f, %f", &x,&Es);
    float Es2 = 10 + Es;
    
  
    VV = exp(x);
    printf(" Imprime el valor verdadero %f", VV);

    //Calculamos el Euler
    if (Es<Es2){
      for ();
    }
    
    return 0;

}