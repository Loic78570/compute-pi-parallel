#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/time.h>
#include <omp.h>

#define ROWS 3
#define COLUMNS 3



//char **genmatrix(){
//
//    static char a[10][10];
//    int i, j;
//
//    for(i = 0;i < ROWS;i++)
//        for(j = 0;j < COLUMNS;j++)
//            a[i][j] = (rand() % 26) + 'A';
//
//    return a;
//}

int main(){

    omp_set_num_threads(omp_get_num_procs());

    int i,j;
    static char a[COLUMNS][ROWS] = {{'a', 'b', 'c'},
                                    {'d', 'e', 'f'},
                                    {'g', 'h', 'a'}};

    struct timeval tv1, tv2;
    struct timezone tz;
    double elapsed;

    //GENERATION
//    for(i = 0;i < ROWS;i++)
//        for(j = 0;j < COLUMNS;j++)
//            a[i][j] = (rand() % 26) + 'A';

   // PRINTING

    for(i = 0;i < ROWS;i++){
        for(j = 0;j < COLUMNS;j++){
            printf("%c  ", a[i][j]);
            if(j == COLUMNS-1){
                printf("\n");
            }
        }
    }

    gettimeofday(&tv1, &tz);

// searching for left to right palindromes

    int ind_palin = 1;
    int num_palins = 0;

#pragma omp parallel for private(i,j) shared(ind_palin,num_palins)
    for(i = 0;i < ROWS;i++){
        for(j = 0;j < COLUMNS;j++){
//            printf("%c  ", a[i][j]);
            if((i!=0) && (j!=COLUMNS-1) && a[i][j]==a[i][j-1]){
                ind_palin++;
            }
            else if(ind_palin>1){
                num_palins++;
                ind_palin = 1;
//                printf("num palin %c, %d, %d\n", a[i][j], i, j);
            }
        }
    }

    // search for top to bottom palindroms

#pragma omp parallel for private(i,j) shared(ind_palin,num_palins)
    for(i = 0;i < ROWS;i++){
        for(j = 0;j < COLUMNS;j++){
//            printf("%c  ", a[i][j]);
            if((i!=0) && (j!=COLUMNS-1) && a[i][j]==a[i-1][j]){
                ind_palin++;
            }
            else if(ind_palin>1){
                num_palins++;
                ind_palin = 1;
//                printf("num palin %c, %d, %d\n", a[i][j], i, j);
            }
        }
    }

    // search for crossed palindrom (top right to bottom left)

    i = 0;
    j = COLUMNS-1;
//    for(i = 0;i < ROWS;i++){
#pragma omp parallel while private(i,j, ibis, jbis) shared(ind_palin,num_palins)
    while(i<ROWS){
//        for(j = COLUMNS-1;j >= 0;j--){
        while(j>=0){
            if((i!=0) && (j!=0)){
                int ibis = i;
                int jbis = j;
                while((ibis!=0) && (jbis!=0)){
//                    printf("ibis : %d, jbis: %d\n ", ibis, jbis);

                    if(ibis<ROWS){
                        printf("comparing : %c, %c\n", a[ibis][jbis], a[ibis-1][jbis-1]);
                        if(a[ibis][jbis]==a[jbis][ibis] && jbis!=ibis){
                            ind_palin++;
                        }
                        else if(ind_palin>1){
                            num_palins++;
                            ind_palin = 1;
                        }
                    }

                    ibis--;
                    jbis--;
                }

            }

            i++;
            if(i==COLUMNS+1){
                break;
            }
        }
        j--;
    }

    printf("XXX\n");
    //search for top left to bottom right

    int j_scale = 0;
    ind_palin = 0;
    int n = 1;
    i = 1;
    j = 0;
    int lim = ROWS;

#pragma omp parallel while private(i,j) shared(ind_palin,num_palins, lim, n)
    while(n<lim){
        while(i>j_scale){
//            printf("Couple (i,j) = (%d,%d)\n", i, j);
            printf("comparing %c and %c. pos i = %d, pos j = %d\n", a[i][j], a[j][i], j, i);

            if(a[i][j] == a[j][i] && i!=j){
                ind_palin++;
            } else if(ind_palin>0){
                num_palins++;
                ind_palin=0;
            }

            j++;
            i--;
        }
        if(j_scale==lim-2){
            break;
        }
//        printf("n : %d\n", n);
        if(n<lim-1){

            n++;
            i=n;
            j=0;
        }
        else if(n==lim-1){
            j_scale++;
            j=j_scale;
            i=n;
//            printf("val j : %d", j);
//            printf("val i : %d", i);
//            printf("val n: %d\n", n);
        }

    }

    if(ind_palin>0){
        num_palins++;
        ind_palin=0;
    }

    gettimeofday(&tv2, &tz);

    elapsed = (double) (tv2.tv_sec-tv1.tv_sec) + (double) (tv2.tv_usec-tv1.tv_usec) * 1.e-6;



    printf("nb palindrome linéaire : %d\n", num_palins);
    printf("time elapsed : %f\n", elapsed);

    return(0);

}