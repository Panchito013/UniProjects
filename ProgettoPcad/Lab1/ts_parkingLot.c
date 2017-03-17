#include "ts_parkingLot.h"


void* ingressoP(void* in){
   
    t_park* temp;
    temp = (t_park*) in;
    
    while(TRUE){
        sleep(3);
        pthread_mutex_lock(&temp->lock);
        while(temp->lotsRemain == 0)
            pthread_cond_wait(&temp->p_Queue, &temp->lock);
        temp->lotsRemain--;
        pthread_cond_signal(&temp->s_Queue);
        pthread_mutex_unlock(&temp->lock);
    }
    return ((void*)NULL);
}




void* ingressoS(void* in){

    t_park* temp;
    temp = (t_park*) in;
    
    while(TRUE){
        pthread_mutex_lock(&temp->lock);
        while(temp->lotsRemain == 0)
            pthread_cond_wait(&temp->p_Queue, &temp->lock);
        temp->lotsRemain--;
        pthread_cond_signal(&temp->p_Queue);
        pthread_mutex_unlock(&temp->lock);

    }
    return ((void*)NULL);
}
 

void* uscita(void* out){    

    t_park* temp;
    temp = (t_park*) out;

    for(;;){
        pthread_mutex_lock(&temp->lock);

        while(temp->lotsRemain == MAXP)
            pthread_cond_wait(&temp->p_Queue,&temp->lock);

        temp->lotsRemain++;

        pthread_cond_signal(&temp->s_Queue);
        pthread_mutex_unlock(&temp->lock);
    }
    return ((void*)NULL);
}