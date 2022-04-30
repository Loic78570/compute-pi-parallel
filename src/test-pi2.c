#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define MAX_THREADS 8

static unsigned int steps = 100000000;

void red() {
    printf("\033[1;31m");
}
void yellow() {
        printf("\033[1;33m");
}
void green() {
    printf("\033[1;32m");
}
void reset() {
    printf("\033[0m");
}

int main(){

    printf("/************************************************************/\n");
    printf("/         CALCUL DE PI EN PROGRAMMATION PARALLÈLE            /\n");
    printf("/                                                            /\n");
    printf("/         Ce programme calcule pi selon la méthode           /\n");
    printf("/         de Monte-Carlo. Le programme génère plusieurs      /\n");
    printf("/         points et estime tour par tour si le point se      /\n"
           "/         trouve dans un cercle de rayon 1.                  /\n");
    printf("/                                                            /\n");
    printf("/         Ce programme calcule ce résultat avec un           /\n");
    printf("/         nombre de threads différents à chaque étape.       /\n"
           "/         Attention, ce programme demande beaucoup de        /\n"
           "/         ressources à l'ordinateur.                         /\n");
    printf("/                                                            /\n");
    printf("/         Source : https://github.com/loic78570              /\n");
    printf("/                                                            /\n");
    printf("/************************************************************/\n");
    printf("\n");
    printf("Vraie valeur de PI:          %.16g\n", M_PI);

    double Xrand, Yrand, time, delta, estimPI;

    for (int j=1; j<= MAX_THREADS; j++) {

        printf("Éxécution sur %d thread: ", j);

        // This is the beginning of a single PI computation
        omp_set_num_threads(j);

        double sum = 0.0;
        double start = omp_get_wtime();

        double step = 1.0/(double) steps;
        double Ntotal = 0, Ncercle = 0;

#pragma omp parallel for reduction(+:Ncercle)
        for (int i = 0; i < steps; i++) {
            Xrand = (double) rand() / RAND_MAX;
            Yrand = (double) rand() / RAND_MAX;
            if (sqrt(pow(Xrand, 2) + pow(Yrand, 2)) < 1) {
                Ncercle++;
            }
        }

        estimPI = 4 * Ncercle / steps;

        time = omp_get_wtime() - start;
        delta = fabs(M_PI_4 - Ncercle/steps);
        yellow();
        printf("PI = %.12g ", estimPI);
        reset();
        printf("calculé en ");
        green();
        printf("%.2g secondes", time);
        reset();
        printf(" (±%.4g)\n", delta);
        reset();
    }


}

