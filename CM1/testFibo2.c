#include <math.h>
#include <omp.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int fibser(int n){

    if(n<=1) return 1;
    return fibser(n-1)+fibser(n-2);
}

int fib(int n){
    int x, y;
    if(n<=1) return 1;
    if(n<=30) return fibser(n);
#pragma omp task shared(x)
    x=fib(n-1);
#pragma omp task shared(y)
    y=fib(n-2);
#pragma omp taskwait
    return x+y;
}

int main(){
    double s=omp_get_wtime();
    int z;
#pragma omp parallel
    {
#pragma omp single
        z=fib(50);
    }
    double sec=omp_get_wtime()-s;

    printf("the result = %d in time = %3f", z, sec);
}