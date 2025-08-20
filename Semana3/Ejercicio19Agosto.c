#include <stdio.h>
#include <math.h>

int main(void) {
    double x = 0;
    double Es1;
    double Es2 = 500;
    double VV;
    
    printf("Ingrese los valores correspondientes para X y el error porcentual esperado:\n");
    printf("Formato: x, error (ejemplo: 2, 0.1): ");
    scanf("%lf, %lf", &x, &Es1);

    VV = exp(x);
    double VC = 1;
    double factorial = 1;

    if (Es1 < Es2) {
        for (int i = 0; i <= 100; i++) {
            
            if (i > 0) {
                factorial *= i;
            }
            
            
            VC += pow(x, i) / factorial;
            Es2 = fabs((VC - VV) / VV) * 100;
            printf("Iteración %d: VC = %f, Error = %f%%\n", i, VC, Es2);
            
            if (Es2 < Es1) {
                printf("Error alcanzado en iteración %d\n", i);
                break;
            }
        }
    }

    printf("\nResultado final:\n");
    printf("Valor verdadero (exp(%f)): %f\n", x, VV);
    printf("Valor calculado: %f\n", VC);
    printf("Error porcentual: %f%%\n", Es2);

    return 0;
}
