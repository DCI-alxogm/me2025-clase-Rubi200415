#include <stdio.h>
#include <math.h>

/* Parámetros del problema */
#define C 12.5
#define M 68.1
#define A 8.3
#define B 2.2
#define VMAX 46.0
#define G 9.81

/* Función dv/dt = f(v) */
double f(double v)
{
    double term = v + A * pow(v / VMAX, B);
    return G - (C / M) * term;
}

int main()
{
    double h = 0.1;
    double v_euler = 0.0;
    double v_rk2 = 0.0;
    double v_rk4 = 0.0;

    double k1, k2, k3, k4;
    int i;

    printf("Iter\tEuler\t\tRK2\t\tRK4\n");

    for(i = 0; i < 2; i++)
    {
        /* --------- EULER --------- */
        v_euler = v_euler + h * f(v_euler);

        /* --------- RK2 (midpoint) --------- */
        k1 = f(v_rk2);
        k2 = f(v_rk2 + 0.5 * h * k1);
        v_rk2 = v_rk2 + h * k2;

        /* --------- RK4 --------- */
        k1 = f(v_rk4);
        k2 = f(v_rk4 + 0.5 * h * k1);
        k3 = f(v_rk4 + 0.5 * h * k2);
        k4 = f(v_rk4 + h * k3);
        v_rk4 = v_rk4 + (h/6.0) * (k1 + 2*k2 + 2*k3 + k4);

        printf("%d\t%.10f\t%.10f\t%.10f\n",
               i+1, v_euler, v_rk2, v_rk4);
    }

    return 0;
}
