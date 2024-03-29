#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/time.h>
#include <omp.h>

#define ROWS 40
#define COLUMNS 40



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
//    static char a[COLUMNS][ROWS] = {{'a', 'b', 'c', 'd'},
//                                    {'e', 'a', 'g', 'h'},
//                                    {'i', 'j', 'b', 'l'},
//                                    {'m', 'n', 'o', 'p'}};
    static char a[COLUMNS][COLUMNS];

    struct timeval tv1, tv2;
    struct timezone tz;
    double elapsed;

    //GENERATION
    for(i = 0;i < ROWS;i++)
        for(j = 0;j < COLUMNS;j++)
            a[i][j] = (rand() % 26) + 'A';

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
//#pragma omp parallel while private(i,j, ibis, jbis) shared(ind_palin,num_palins)
//    while(i<ROWS){
////        for(j = COLUMNS-1;j >= 0;j--){
//        while(j>=0){
//            if((i!=0) && (j!=0)){
//                int ibis = i;
//                int jbis = j;
//                int x = 0;
//                while((ibis!=0) && (jbis!=0)){
////                    printf("ibis : %d, jbis: %d\n ", ibis, jbis);
//
//                    if(ibis<ROWS){
//                        if(i-j>=0){
//                            x = -i;
//                        } else {
//                            x = i-j;
//                        }
//                        printf("comparing : %c, %c (%d, %d) with (%d, %d)\n", a[ibis][jbis], a[ibis-1][jbis+x]
//                        , ibis, jbis, ibis-1, jbis+x);
//
//                        printf("val i: %d, val j: %d", i, j);
//                        if(a[ibis][jbis]==a[ROWS-ibis][ROWS-jbis] && jbis!=ibis){
//                            ind_palin++;
//                        }
//                        else if(ind_palin>1){
//                            num_palins++;
//                            ind_palin = 1;
//                        }
//                    }
//
//                    ibis--;
//                    jbis--;
//                }
//
//            }
//
//            i++;
//            if(i==COLUMNS+1){
//                break;
//            }
//        }
//        j--;
//    }

    int lim = ROWS-1;
    i =1, j=lim;
    int n=1, k = 0, h = 0;
    ind_palin = 0;
    int delta;


#pragma omp parallel while private(i,j) shared(ind_palin,num_palins)
    while(n<=lim && j>0){
        while(i>0 && j>0){
            delta = (k-n)+h*2;
//            printf("val n : %d, val k : %d -- ", n, k);
//            printf("(i,j) = (%d,%d) (k-n=%d)\n", i, j, delta);

            if(delta == 0){
                // même lettre
//                printf("même lettre -> singleton (i,j) = (%d, %d)\n", i, j);
            }
            else if(i+delta>=0 && j+delta>=0) {
//                printf("Comparing :  = (%c,%c) (%d,%d) et (%d,%d)\n", a[i][j], a[i + delta][j + delta],
//                       i, j, i + delta, j + delta);
//                printf("ind palin : %d\n", ind_palin);
                if(a[i][j] == a[i+delta][j+delta] && delta!=0){
//                    printf("palin!");
                    ind_palin++;
                }
                else if(ind_palin>0)
                    ind_palin = 0;
            }

//            else if(ind_palin>0 && a[i][j] != a[i+delta][j+delta]){
//                ind_palin=0;
//            }

            else if(ind_palin>1){
                printf("incr...");
                num_palins++;
                ind_palin=0;
            }
            i--;j--;h++;
        }
//        printf("ind palin : %d (l174)", ind_palin);
//        printf("delta : %d", delta);
        if(ind_palin>1){
//            printf("\nincr 175 \n\n");
//            printf("For :  = (%c,%c) (%d,%d) et (%d,%d)\n", a[i][j], a[i + delta][j + delta],
//                   i, j, i + delta, j + delta);
            num_palins++;
            ind_palin=0;
        }

        if(n<lim){
            n++; i=n; j=lim; h=0;
        } else if (n==lim){
            i=n; k++; j=lim-k; h=0;
        }

    }

    if(ind_palin>0){
        printf("incr 189 ");
        num_palins++;
        ind_palin=0;
    }

    printf("XXX\n");
    //search for top left to bottom right

    int j_scale = 0;
    ind_palin = 0;
    n = 1;
    i = 1;
    j = 0;
    lim = ROWS;

//#pragma omp parallel while private(i,j) shared(ind_palin,num_palins, lim, n)
//    while(n<lim){
//        while(i>j_scale){
////            printf("Couple (i,j) = (%d,%d)\n", i, j);
//            printf("comparing %c and %c. pos i = %d, pos j = %d\n", a[i][j], a[j][i], j, i);
//
//            if(a[i][j] == a[j][i] && i!=j){
//                ind_palin++;
//            } else if(ind_palin>0){
//                num_palins++;
//                ind_palin=0;
//            }
//
//            j++;
//            i--;
//        }
//        if(j_scale==lim-2){
//            break;
//        }
////        printf("n : %d\n", n);
//        if(n<lim-1){
//
//            n++;
//            i=n;
//            j=0;
//        }
//        else if(n==lim-1){
//            j_scale++;
//            j=j_scale;
//            i=n;
////            printf("val j : %d", j);
////            printf("val i : %d", i);
////            printf("val n: %d\n", n);
//        }
//
//    }
//
//    if(ind_palin>0){
//        num_palins++;
//        ind_palin=0;
//    }

    gettimeofday(&tv2, &tz);

    elapsed = (double) (tv2.tv_sec-tv1.tv_sec) + (double) (tv2.tv_usec-tv1.tv_usec) * 1.e-6;



    printf("nb palindrome linéaire : %d\n", num_palins);
    printf("time elapsed : %f\n", elapsed);

    return(0);

}