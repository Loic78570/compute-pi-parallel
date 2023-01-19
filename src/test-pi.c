#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_THREADS 8

static unsigned int steps = 500000000;
double step;

int main (int argc, const char *argv[]) {

    int i,j;
    double x;
    double pi, sum = 0.0;
    double start, delta, deltavar;

    printf("/************************************************************/\n");
    printf("/         CALCUL DE PI EN PROGRAMMATION PARALLÈLE            /\n");
    printf("/                                                            /\n");
    printf("/         Ce programme va calculer l'intégrale de            /\n");
    printf("/                  1/1+x² entre 0 et 1.                      /\n");
    printf("/         Le résultat vaut arctan(1)-arctan(0)=pi/4          /\n");
    printf("/                                                            /\n");
    printf("/         Ce programme calcule ce résultat avec un           /\n");
    printf("/         nombre de threads différents à chaque étape.       /\n");
    printf("/                                                            /\n");
    printf("/          Source : https://gist.github.com/bbengfort        /\n");
    printf("/                                                            /\n");
    printf("/************************************************************/\n");
    printf("\n");
    printf("Vraie valeur de PI:          %.16g\n", M_PI);

    step = 1.0/(double) steps;

    // Compute parallel compute times for 1-MAX_THREADS
    for (j=1; j<= MAX_THREADS; j++) {

        printf("Éxécution sur %d thread: ", j);

        // This is the beginning of a single PI computation
        omp_set_num_threads(j);

        sum = 0.0;
        start = omp_get_wtime();


#pragma omp parallel for reduction(+:sum) private(x)
        for (i=0; i < steps; i++) {
            x = (i+0.5)*step;
            sum += 4.0 / (1.0+x*x);
        }

        // Out of the parallel region, finialize computation
        pi = step * sum;
        delta = omp_get_wtime() - start;
        deltavar = M_PI - pi;
        printf("PI = %.16g calculé en %.4g secondes. (±%.4g)\n", pi, delta, deltavar);

    }
    system("pause");

}