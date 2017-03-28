#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define MAXTHREADS 50
#define MAXLOTS 5
#define MAXATMPT 5

typedef struct ParkingLot{
    int maxLots;
    pthread_cond_t queueA;
    pthread_cond_t queueB;
}parkLot_t;

typedef struct threadCar{
    pthread_t car;
    int carId;
    int attempts;
}Car;


void* ptr;
parkLot_t parkingLot;

Car carPark[MAXTHREADS];
pthread_mutex_t barrier = PTHREAD_MUTEX_INITIALIZER;


void* entranceA(int* id){
    int atmpt = 0; //number of actual attempts through the barrier

    while(atmpt < carPark[*id].attempts){
        /////////////////Entrance////////////////////////
        pthread_mutex_lock(&barrier);
        while(parkingLot.maxLots == 0){
            fprintf(stderr,"\nCar %d in queue A; Number of Attempt \n: %d", carPark[*id].carId, carPark[*id].attempts);
            pthread_cond_wait(&parkingLot.queueA, &barrier);
        }
        fprintf(stderr,"\nCar %d is entering the parkingLot\n", carPark[*id].carId);
        parkingLot.maxLots--;
        printf("\nLots remaining in parkingLot: %d\n", parkingLot.maxLots);
        pthread_mutex_unlock(&barrier);

        sleep(2);
        /////////////////////Exit///////////////////////
        pthread_mutex_lock(&barrier);
        fprintf(stderr,"\nCar %d is exiting the parkingLot\n", carPark[*id].carId);
        parkingLot.maxLots++;
        pthread_cond_signal(&parkingLot.queueA);
        pthread_cond_signal(&parkingLot.queueB);
        pthread_mutex_unlock(&barrier);
        atmpt++;
    }
    pthread_exit(ptr);
}

void* entranceB(int* id){

    int atmpt = 0; //number of actual attempts through the barrier

    while(atmpt < carPark[*id].attempts){
        /////////////////Entrance////////////////////////
        pthread_mutex_lock(&barrier);
        while(parkingLot.maxLots == 0){
            fprintf(stderr,"\nCar %d in queue B; Number of Attempt \n: %d\n", carPark[*id].carId, carPark[*id].attempts);
            pthread_cond_wait(&parkingLot.queueB, &barrier);
        }
        fprintf(stderr,"\nCar %d is entering the parkingLot\n", carPark[*id].carId);
        parkingLot.maxLots--;
        printf("\nLots remaining in parkingLot: %d\n", parkingLot.maxLots);
        pthread_mutex_unlock(&barrier);

        sleep(1);
        /////////////////////Exit///////////////////////
        pthread_mutex_lock(&barrier);
        fprintf(stderr,"\nCar %d is exiting the parkingLot\n", carPark[*id].carId);
        parkingLot.maxLots++;
        pthread_cond_signal(&parkingLot.queueA);
        pthread_cond_signal(&parkingLot.queueB);
        pthread_mutex_unlock(&barrier);
        atmpt++;
    }
    pthread_exit(ptr);
    

}
