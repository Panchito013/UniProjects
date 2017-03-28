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
            fprintf(stderr,"\nCar %d in queue; Number of Attempt \n: %d\n", carPark[*id].carId, carPark[*id].attempts);
            pthread_cond_wait(&parkingLot.queueA, &barrier);
        }
        parkingLot.maxLots--;
        printf("%d/n", parkingLot.maxLots);
        pthread_mutex_unlock(&barrier);

        sleep(3);
        /////////////////////Exit///////////////////////
        pthread_mutex_lock(&barrier);
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
            fprintf(stderr,"\nCar %d in queue; Number of Attempt \n: %d\n", carPark[*id].carId, carPark[*id].attempts);
            pthread_cond_wait(&parkingLot.queueB, &barrier);
        }
        parkingLot.maxLots--;
        printf("%d/n", parkingLot.maxLots);
        pthread_mutex_unlock(&barrier);

        sleep(1);
        /////////////////////Exit///////////////////////
        pthread_mutex_lock(&barrier);
        parkingLot.maxLots++;
        pthread_cond_signal(&parkingLot.queueA);
        pthread_cond_signal(&parkingLot.queueB);
        pthread_mutex_unlock(&barrier);
        atmpt++;
    }
    pthread_exit(ptr);
    

}

int main(){
    fprintf(stderr, "\n===== ParkingLot is OPEN =====\n");

    parkingLot.maxLots = MAXLOTS;
    parkingLot.queueA = (pthread_cond_t)PTHREAD_COND_INITIALIZER;
    parkingLot.queueB = (pthread_cond_t)PTHREAD_COND_INITIALIZER;

    int entrance; // 1 -> FirstEntrance || 2 -> SecondEntrance

    srand(time(NULL));
    int i = 0;

    while(i < MAXTHREADS){
        entrance = rand() % 2 + 1;
        carPark[i].carId = i + 1;
        carPark[i].attempts = MAXATMPT;

        if(entrance == 1)
            pthread_create(&(carPark[i].car), NULL, (void*) entranceA, &carPark[i].carId);
        
        if(entrance == 2)
            pthread_create(&(carPark[i].car), NULL, (void*) entranceB, &carPark[i].carId);
        
        i++;
    }

    for(i = 0; i < MAXTHREADS; i++)
        pthread_join((carPark[i].car), ptr);

    if(parkingLot.maxLots != MAXLOTS)
        fprintf(stderr,"ParkingLot is not Empty!!! Closure not possible! Cars in lots : %d\n",30-parkingLot.maxLots);
    else 
        fprintf(stderr,"\n===== ParkingLot is CLOSE =====\n");

 return 0;

}
