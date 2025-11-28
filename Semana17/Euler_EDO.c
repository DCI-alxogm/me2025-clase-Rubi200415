#include <stdio.h>

void f(double t, double x, double y, double *dxdt, double *dydt){
    *dxdt = x + y;
    *dydt = -x + y;
}

int main(){
    double t = 0.0, h = 0.1;
    double x = 1.0, y = 0.0;
    double dxdt, dydt;

    for(int i=0; i<10; i++){
        f(t, x, y, &dxdt, &dydt);

        x = x + h * dxdt;
        y = y + h * dydt;
        t = t + h;

        printf("t=%.2f  x=%.4f  y=%.4f\n", t, x, y);
    }

    return 0;
}

