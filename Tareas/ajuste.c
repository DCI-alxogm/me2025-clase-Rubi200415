#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_multimin.h>
#include <string.h>   // Para strchr
#include <stddef.h>   // Para size_t

// Estructura para pasar datos a las funciones de chi2
typedef struct {
    double* aw;            // water activity
    double* xe;            // moisture content (% dry basis)
    size_t n;              // número de puntos válidos
} data_t;

// Modelo Peleg: Xe = b0 / (aw^b1) + b2 * (aw^b3)
double peleg_model(double aw, const double params[4]) {
    double b0 = params[0], b1 = params[1], b2 = params[2], b3 = params[3];
    if (aw <= 0 || aw >= 1) return NAN;
    return b0 / pow(aw, b1) + b2 * pow(aw, b3);
}

// Modelo DLP: Xe = b0 + b1*x + b2*x^2 + b3*x^3, con x = ln(-ln(aw))
double dlp_model(double aw, const double params[4]) {
    if (aw <= 0 || aw >= 1) return NAN;
    double x = log(-log(aw));
    double b0 = params[0], b1 = params[1], b2 = params[2], b3 = params[3];
    return b0 + b1*x + b2*pow(x,2) + b3*pow(x,3);
}

// Función chi2 para Peleg
double chi2_peleg(const gsl_vector* v, void* params) {
    data_t* data = (data_t*)params;
    double b[4] = {gsl_vector_get(v, 0),
                   gsl_vector_get(v, 1),
                   gsl_vector_get(v, 2),
                   gsl_vector_get(v, 3)};
    double sum = 0.0;
    for (size_t i = 0; i < data->n; ++i) {
        double pred = peleg_model(data->aw[i], b);
        if (!isnan(pred)) {
            double diff = data->xe[i] - pred;
            sum += diff * diff;
        }
    }
    return sum;
}

// Función chi2 para DLP
double chi2_dlp(const gsl_vector* v, void* params) {
    data_t* data = (data_t*)params;
    double b[4] = {gsl_vector_get(v, 0),
                   gsl_vector_get(v, 1),
                   gsl_vector_get(v, 2),
                   gsl_vector_get(v, 3)};
    double sum = 0.0;
    for (size_t i = 0; i < data->n; ++i) {
        double pred = dlp_model(data->aw[i], b);
        if (!isnan(pred)) {
            double diff = data->xe[i] - pred;
            sum += diff * diff;
        }
    }
    return sum;
}

// Función auxiliar para cargar datos desde CSV (mejorada)
int load_data(const char* filename, double** aw, double** xe, size_t* n) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        perror("No se pudo abrir el archivo");
        return -1;
    }

    // Contar líneas válidas (ignorar encabezado si existe)
    size_t lines = 0;
    char buffer[256];
    int first_line = 1; // Para saltar encabezado si existe

    while (fgets(buffer, sizeof(buffer), fp)) {
        // Saltar encabezado si es la primera línea y contiene texto (no números)
        if (first_line) {
            first_line = 0;
            // Si la primera línea parece tener letras, la ignoramos
            if (strchr(buffer, 'a') || strchr(buffer, 'A') || strchr(buffer, 'w')) {
                continue;
            }
        }
        // Contar solo líneas con datos numéricos
        lines++;
    }
    rewind(fp);

    // Saltar encabezado si existe
    first_line = 1;
    while (fgets(buffer, sizeof(buffer), fp)) {
        if (first_line) {
            first_line = 0;
            if (strchr(buffer, 'a') || strchr(buffer, 'A') || strchr(buffer, 'w')) {
                continue;
            }
        }
        break;
    }

    *n = lines;
    if (*n == 0) {
        fprintf(stderr, "Error: No se encontraron datos en %s\n", filename);
        fclose(fp);
        return -1;
    }

    *aw = malloc(*n * sizeof(double));
    *xe = malloc(*n * sizeof(double));

    if (*aw == NULL || *xe == NULL) {
        fprintf(stderr, "Error: No se pudo asignar memoria.\n");
        fclose(fp);
        return -1;
    }

    size_t i = 0;
    while (i < *n && fscanf(fp, "%lf,%lf", &(*aw)[i], &(*xe)[i]) == 2) {
        if ((*aw)[i] > 0 && (*aw)[i] < 1) {
            i++;
        }
    }
    *n = i; // Solo puntos válidos

    if (*n < 4) {
        fprintf(stderr, "Advertencia: Pocos puntos válidos (%zu) en %s\n", *n, filename);
        free(*aw);
        free(*xe);
        *aw = NULL;
        *xe = NULL;
        fclose(fp);
        return -1;
    }

    fclose(fp);
    return 0;
}

void fit_model(const char* model_name, double (*chi2_func)(const gsl_vector*, void*), 
               const double init_params[4], data_t* data) {
    const gsl_multimin_fminimizer_type* T = gsl_multimin_fminimizer_nmsimplex2;
    gsl_multimin_fminimizer* s = NULL;
    gsl_vector* x = gsl_vector_alloc(4);
    gsl_vector* step = gsl_vector_alloc(4);

    for (int i = 0; i < 4; ++i) {
        gsl_vector_set(x, i, init_params[i]);
        gsl_vector_set(step, i, 0.1); // tamaño inicial del simplex
    }

    gsl_multimin_function minex_func;
    minex_func.n = 4;
    minex_func.f = chi2_func;
    minex_func.params = data;

    s = gsl_multimin_fminimizer_alloc(T, 4);
    gsl_multimin_fminimizer_set(s, &minex_func, x, step);

    size_t iter = 0;
    int status;
    double size;

    do {
        iter++;
        status = gsl_multimin_fminimizer_iterate(s);
        if (status) break;
        size = gsl_multimin_fminimizer_size(s);
        status = gsl_multimin_test_size(size, 1e-4);
    } while (status == GSL_CONTINUE && iter < 1000);

    printf("\n--- Ajuste %s ---\n", model_name);
    printf("Iteraciones: %zu\n", iter);
    printf("Chi2 final: %.6f\n", s->fval);
    printf("Parámetros: [");
    for (int i = 0; i < 4; ++i) {
        printf("%.6f", gsl_vector_get(s->x, i));
        if (i < 3) printf(", ");
    }
    printf("]\n");

    gsl_vector_free(x);
    gsl_vector_free(step);
    gsl_multimin_fminimizer_free(s);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <archivo.csv>\n", argv[0]);
        fprintf(stderr, "Formato CSV: aw,xe (una línea por dato, sin encabezado necesario)\n");
        return 1;
    }

    double* aw = NULL;
    double* xe = NULL;
    size_t n;

    if (load_data(argv[1], &aw, &xe, &n) != 0) {
        return 1;
    }

    if (n < 4) {
        fprintf(stderr, "Error: se necesitan al menos 4 puntos válidos.\n");
        free(aw); free(xe);
        return 1;
    }

    data_t data = {.aw = aw, .xe = xe, .n = n};

    // Valores iniciales (deben ajustarse según el conjunto de datos)
    double p0_peleg[4] = {1.0, 0.5, 1.0, 1.0};
    double p0_dlp[4]   = {1.0, 0.1, 0.01, 0.001};

    fit_model("Peleg", chi2_peleg, p0_peleg, &data);
    fit_model("DLP",   chi2_dlp,   p0_dlp,   &data);

    free(aw);
    free(xe);
    return 0;
}