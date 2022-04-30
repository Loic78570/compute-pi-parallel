#include <stdio.h>
#include <omp.h>
#include <sys/time.h>
#include <stdlib.h>


#define matrix_size 1000

int A[matrix_size][matrix_size];
int B[matrix_size][matrix_size];
int C[matrix_size][matrix_size];

int main(int argc, char** argv)
{
    int i,j,k;
    struct timeval tv1, tv2;
    struct timezone tz;
    double elapsed;
    omp_set_num_threads(omp_get_num_procs());
    for (i= 0; i< matrix_size; i++)
        for (j= 0; j< matrix_size; j++)
        {
            A[i][j] = rand()%10;
            B[i][j] = rand()%10;
        }
    gettimeofday(&tv1, &tz);


#pragma omp parallel for private(i,j,k) shared(A,B,C)
    for (i = 0; i < matrix_size; ++i) {
        for (j = 0; j < matrix_size; ++j) {
            for (k = 0; k < matrix_size; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    
    gettimeofday(&tv2, &tz);
    elapsed = (double) (tv2.tv_sec-tv1.tv_sec) + (double) (tv2.tv_usec-tv1.tv_usec) * 1.e-6;
    printf("elapsed time = %f seconds.\n", elapsed);

    for (i= 0; i< matrix_size; i++)
    {
        for (j= 0; j< matrix_size; j++)
        {
            printf("%d\t",C[i][j]);
        }
        printf("\n");
    }
}
 