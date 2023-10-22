#include <stdio.h>
#include <stdlib.h>
#define MAX_DEGREE (degree_p + degree_q)

// a
void poly_print(double const p[], int const m) {
    int i;
    int firstTerm = 1; // Variable, um den ersten Ausdruck zu kennzeichnen

    for (i = 0; i <= m; i++) {
        if (p[i] != 0) {
            if (!firstTerm) {
                if (p[i] > 0) {
                    printf(" + ");
                } else {
                    printf(" - ");
                }
            } else {
                firstTerm = 0;
            }

            if (i == m || (i < m && p[i + 1] == 0)) {
                printf("%g", (p[i] > 0) ? p[i] : -p[i]);
            } else {
                printf("%g*x", (p[i] > 0) ? p[i] : -p[i]);
            }

            if (i < m - 1 && p[i + 1] != 0) {
                printf("^%d", m - i);
            }
        }
    }

    printf("\n");
}

// b
double poly_evaluate(double const p[], int const m, double const x) {
    double result = 0;
    for (int i = m; i >= 0; i--) {
        result = result * x + p[i];
    }
    return result;
}

// c

int poly_add(double const p[], int const m, double const q[], int const n, double r[]) {
    
    int max_degree = (m > n) ? m : n; 

    for (int i = 0; i <= max_degree; i++) {
        double p_coefficient = (i <= m) ? p[i] : 0; 
        double q_coefficient = (i <= n) ? q[i] : 0; 
        r[i] = p_coefficient + q_coefficient;
    }

    return max_degree; 
}

// d

int poly_mult(double const p[], int const m, double const q[], int const n, double r[]) {
    // Grad des resultierenden Polynoms
    int degree_result = m + n;

    // Dynamische Speicherallokation für das Ergebnispolynom result
    double *result = malloc((size_t)(degree_result + 1) * sizeof(double));

    // Überprüfung auf Speicherzuweisungsfehler
    if (result == NULL) {
        fprintf(stderr, "Fehler: Speicher konnte nicht allokiert werden\n");
        exit(EXIT_FAILURE);
    }

    // Initialisiere das Ergebnispolynom mit Nullen
    for (int i = 0; i <= degree_result; i++) {
        result[i] = 0;
    }

    // Multipliziere die Koeffizienten und speichere die Ergebnisse im Ergebnispolynom result
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            result[i + j] += p[i] * q[j];
        }
    }

    // Kopiere das Ergebnispolynom in r
    for (int i = 0; i <= degree_result; i++) {
        r[i] = result[i];
    }

    free(result);

    return degree_result; 
}



int main() {
    double p[] = {4, 3, -2, 1};
    int degree_p = 3; // Grad des Polynoms
    double x = 1.5; // Wert von x, an dem das Polynom ausgewertet werden soll

    double q[] = {4, 5, 6, 7}; 
    int degree_q = 3; 

    // Dynamische Speicherallokation für Ergebnispolynome
    double *result_add = malloc((size_t)(MAX_DEGREE + 1) * sizeof(double));
    double *result_multi = malloc((size_t)(MAX_DEGREE + 1) * sizeof(double));

    // Überprüfung auf Speicherzuweisungsfehler
    if (result_add == NULL || result_multi == NULL) {
        fprintf(stderr, "Fehler: Speicher konnte nicht allokiert werden\n");
        exit(EXIT_FAILURE);
    }

    // Ergebnispolynome berechnen
    int result_add_degree = poly_add(p, degree_p, q, degree_q, result_add); // c
    int result_multi_degree = poly_mult(p, degree_p, q, degree_q, result_multi);  // d

    // Ausgabe des Originalpolynoms und des Ergebnisses
    poly_print(p, degree_p);
    double result = poly_evaluate(p, degree_p, x);
    printf("Ergebnis der Auswertung an x = %.2f: %.2f\n", x, result);

    // Ausgabe des Ergebnispolynoms für die Addition
    printf("Grad des resultierenden Polynoms (Addition): %d\n", result_add_degree);
    printf("R(x) = ");
    poly_print(result_add, result_add_degree);

    // Ausgabe des Ergebnispolynoms für die Multiplikation
    printf("Grad des resultierenden Polynoms (Multiplikation): %d\n", result_multi_degree);
    printf("R(x) = ");
    poly_print(result_multi, result_multi_degree);

    // Speicher freigeben
    free(result_add);
    free(result_multi);

    return 0;
}







    

   

    





