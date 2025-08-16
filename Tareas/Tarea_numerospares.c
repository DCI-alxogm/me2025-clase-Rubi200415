#include <stdio.h>

int main(void) {
    int d;
    int continuar;

    do {
        printf("Ingrese un numero");
        scanf ("%d", &d);

        if ( d%2 ==0){
            printf("%d es un número par\n",d);
            printf("¿Desea ingresar otro número? (verdadero = 1, falso = 0)");
            scanf("%d", &continuar);
        } else {
            printf("%d es un número impar\n",d);
            printf("¿Desea ingresar otro número? (verdadero = 1, falso = 0)");
            scanf("%d", &continuar);
        }
    } while (continuar == 1);

    return 0;

}