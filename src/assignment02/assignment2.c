#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

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


    int i,j;
    char a[COLUMNS][ROWS];

    for(i = 0;i < ROWS;i++)
        for(j = 0;j < COLUMNS;j++)
            a[i][j] = (rand() % 26) + 'A';

    for(i = 0;i < ROWS;i++){
        for(j = 0;j < COLUMNS;j++){
            printf("%c  ", a[i][j]);
            if(j == COLUMNS-1){
                printf("\n");
            }
        }
    }

// searching for left to right palindromes

    int ind_palin = 1;
    int num_palins = 0;

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

//    i = 0;
//    j = COLUMNS-1;
////    for(i = 0;i < ROWS;i++){
//    while(i<ROWS){
////        for(j = COLUMNS-1;j >= 0;j--){
//        while(j>=0){
//            if((i!=0) && (j!=0)){
//                int ibis = i;
//                int jbis = j;
//                while((ibis!=0) && (jbis!=0)){
////                    printf("ibis : %d, jbis: %d\n ", ibis, jbis);
//
//                    if(ibis<ROWS){
//                        printf("comparing : %c, %c\n", a[ibis][jbis], a[ibis-1][jbis-1]);
//                        if(a[ibis][jbis]==a[ibis-1][jbis-1]){
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

    printf("XXX\n");
    //search for top left to bottom right

    i = 1;
    j = 0;
    int e = 0;
    int n = 4;

    for(int i = 1; i<=n; i++){
        while(j<i){
            int ibis = i+e;
            int jbis = j-e;
            while(ibis>0 && jbis<n){
                if(0<=ibis<n-1 && 0<=jbis<n-1){
//                    bool test = ibis<3;
//                    printf("test : ibis<3 : %d\n", test);
//                    printf("comparing %c and %c. pos i = %d, pos j = %d\n", a[ibis][jbis], a[ibis-1][jbis+1], ibis, jbis);
                    printf("couple (i,j) = (%d,%d)\n", ibis, jbis);
                }
//                printf("couple (i,j) = (%d,%d)\n", ibis, jbis);
                ibis--;
                jbis++;
            }
//            printf("sortie de boucle\n");
            j++;
            if(i!=n)
                e++;

        }
        e=0;
//        printf("sortie de boucle 2\n");
//        j=i-1;
        if(i==4){
            j=j;
        } else {
            j=0;
        }
    }


    printf("nb palindrome linéaire : %d", num_palins);

    return(0);

}