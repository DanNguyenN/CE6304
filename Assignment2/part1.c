/*
Main thread creates two child threads and join them.
Thread 1 fills file "datafile" with all 1s. Thread 2
fills file "datafile" with all 2s.
Both executes concurrently.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>

//Function prototypes
void* f1();
void* f2();

//Global file pointers
FILE *fp, *fp1, *fp2;
int d=25;

int main(){
    int third[d][d];
    //open "datafile"
    //make two file pointers for "datafile", fp1 and fp2.
    fp1 = fopen("datafile", "wb");
    fp2 = fp1;
    //create thread1
    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, f1, NULL);
    //create thread2
    pthread_create(&tid2, NULL, f2, NULL);
    //join both threads
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    //close "datafile"
    fclose(fp1);
    //read "datafile" into array test[25][25]
    fp = fopen("datafile", "rb");
    fread(third, sizeof(int), sizeof(third)/sizeof(int), fp);
    //print test[25][25]
    for (int i=0; i<d; i++){
        printf("\n");
        for (int j=0; j<d; j++){
            printf("%d ", third[i][j]);
        }
    }
    //exit from main
    printf("\nExit from main thread\n");
    return 0;
}

//THREAD1
void* f1(){
    int temp = 1;
    //write 25x25 1s digit by digit into "datafile". Call fwrite 25x25 times.
    for (int i=0; i<d; i++){
        for (int j=0; j<d; j++){
            fwrite(&temp, sizeof(int), sizeof(temp)/sizeof(int), fp1);

        }
    }    
    //exit thread 1
    pthread_exit(NULL);
}
//THREAD2
void* f2(){
    int temp = 2;
    //write 25x25 2s digit by digit into "datafile". Call fwrite 25x25 times.
    for (int i=0; i<d; i++){
        for (int j=0; j<d; j++){
            fwrite(&temp, sizeof(int), sizeof(temp)/sizeof(int), fp2);

        }
    }    
    //exit thread 2
    pthread_exit(NULL);
}