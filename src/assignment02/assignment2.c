#include <stdlib.h>
#include <stdio.h>
#define ROWS 4
#define COLUMNS 4

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

    i = 0;
    j = 0;
//    for(i = 0;i < ROWS;i++){
    while(i<ROWS){
//        for(j = COLUMNS-1;j >= 0;j--){
        while(j>=0){
            printf("test i: %d, j: %d, val: %c\n", i, j, a[i][j]);
            if((i!=COLUMNS) && (j!=COLUMNS)){
//                printf("bonjour");
                int ibis = i;
                int jbis = j;
                while((ibis!=0) && (jbis!=COLUMNS)){

//                    printf("ibis : %d, jbis: %d\n ", ibis, jbis);

                    if(ibis<ROWS){
                        printf("comparing : %c, %c\n", a[ibis][jbis], a[ibis-1][jbis+1]);
                        printf("with i : %d, j: %d\n", ibis, jbis);
                        if(a[ibis][jbis]==a[ibis-1][jbis+1]){
                            ind_palin++;
                        }
                        else if(ind_palin>1){
                            num_palins++;
                            ind_palin = 1;
                        }
                    }

                    ibis--;
                    jbis++;
                }

            }

            j++;
            if(i==COLUMNS+1){
                break;
            }
        }
        i++;
    }

    printf("nb palindrome linéaire : %d", num_palins);

    return(0);

}