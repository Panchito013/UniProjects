#include "carThreads.h"

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
