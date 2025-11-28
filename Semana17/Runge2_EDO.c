#include <stdio.h>

void f(double t, double x, double y, double *dxdt, double *dydt){
    *dxdt = x + y;
    *dydt = -x + y;
}

int main(){
    double t = 0.0, h = 0.1;
    double x = 1.0, y = 0.0;
    double k1x, k1y, k2x, k2y;

    for(int i=0; i<10; i++){
        f(t, x, y, &k1x, &k1y);

        f(t+h, x + h*k1x, y + h*k1y, &k2x, &k2y);

        x = x + h * 0.5 * (k1x + k2x);
        y = y + h * 0.5 * (k1y + k2y);

        t = t + h;

        printf("t=%.2f  x=%.4f  y=%.4f\n", t, x, y);
    }

    return 0;
}
