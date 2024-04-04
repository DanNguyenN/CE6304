/*
This program reads data from files datal and data2 and forms two
1000x1000 matrices matl and mat 2 .
Then calls function and multiplies the two matrices and stores result
in 1000x1000 matrix mat 3.
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>

double mat1[1000][1000], mat2[1000][1000], mat3[1000][1000];
    int m=1000, n=1000, p=1000;
    int s=0, e=1000;

void* matmul1 (void * arg);
void* matmul2 (void * arg);

pthread_t tid1, tid2;

int main (void){
    FILE *f;
    f = fopen("data1", "rb");
    fread(mat1, sizeof(double), sizeof(mat1)/sizeof(double), f);
    fclose(f);

    f = fopen("data2", "rb");
    fread(mat2, sizeof(double), sizeof(mat2)/sizeof(double), f);
    fclose(f);


    clock_t start, end;
    double cpu_time_used;
    start = clock();

    pthread_create(&tid1, NULL, matmul1, NULL);
    pthread_create(&tid2, NULL, matmul2, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time taken: %f\n", cpu_time_used, "ms\n");

    printf("%lf %lf %lf %lf \n", mat3[6][0], mat3[5][3], mat3[5][4],
        mat3[901][7]);
        
    return 0;
}


void* matmul1(void * arg){
    int i, j, k, l;
    double sum;
    int s = 0, e = 500;
    for (i=s; i<e; i++){
        for (j=0; j<p; j++){
            for (k=0; k<n; k++){
                sum = sum + mat1[i][k] * mat2[k][j];
            }
            mat3[i][j] = sum;
            sum = 0;
        }
    }
    pthread_exit(NULL);
}

void* matmul2(void * arg){
    int i, j, k, l;
    double sum;
    int s = 500, e = 1000;
    for (i=s; i<e; i++){
        for (j=0; j<p; j++){
            for (k=0; k<n; k++){
                sum = sum + mat1[i][k] * mat2[k][j];
            }
            mat3[i][j] = sum;
            sum = 0;
        }
    }
    pthread_exit(NULL);
}