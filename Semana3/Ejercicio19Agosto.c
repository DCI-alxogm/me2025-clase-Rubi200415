#include <stdio.h>
#include <math.h>


int main(void) {
    double x = 0;
    double Es1;
    double Es2 = 500;
    double VV;
    double VC = 1;
    int n = 10;

    printf("Ingrese los valores correspondientes para X y el error porcentual esperado:\n");
    scanf("%lf, %lf",&x, &Es1);

    VV = exp(x);

    if (Es1 < Es2){
    for (int i = 1; i <= n; i++) {
        double factorial =1;

        for (int cont=1; cont <= i; ++cont){
            factorial *= cont;
        }

        VC += (pow(x,i))/( factorial);
        Es2 = ((VC - VV) / VV) * 100;

        printf("Iteración %d: VC = %f, Error = %f%%\n", i, VC, Es2);

        if (Es2 < Es1) {
            printf("Error alcanzado en iteración %d\n", i);
            break;
        }
    }

        }

    printf("\nResultado final:\n");
    printf("Valor verdadero (exp(x)): %f\n", VV);
    printf("Valor calculado: %f\n", VC);
    printf("Error porcentual: %f%%\n", Es2);

    return 0;
}
