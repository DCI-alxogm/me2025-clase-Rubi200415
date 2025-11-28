#include <stdio.h>

void f(double t, double x, double y, double *dxdt, double *dydt){
    *dxdt = x + y;
    *dydt = -x + y;
}

int main(){
    double t = 0.0, h = 0.1;
    double x = 1.0, y = 0.0;
    double k1x, k1y, k2x, k2y, k3x, k3y, k4x, k4y;

    for(int i=0; i<10; i++){
        f(t, x, y, &k1x, &k1y);

        f(t + h/2, x + h*k1x/2, y + h*k1y/2, &k2x, &k2y);

        f(t + h/2, x + h*k2x/2, y + h*k2y/2, &k3x, &k3y);

        f(t + h, x + h*k3x, y + h*k3y, &k4x, &k4y);

        x = x + (h/6.0)*(k1x + 2*k2x + 2*k3x + k4x);
        y = y + (h/6.0)*(k1y + 2*k2y + 2*k3y + k4y);

        t = t + h;

        printf("t=%.2f  x=%.4f  y=%.4f\n", t, x, y);
    }

    return 0;
}
