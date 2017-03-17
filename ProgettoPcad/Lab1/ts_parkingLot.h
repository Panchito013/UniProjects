#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#define MAXP 100
#define TRUE 1
#define FALSE 0



typedef struct{
    unsigned int lotsRemain;
    pthread_mutex_t lock;
    pthread_cond_t p_Queue;
    pthread_cond_t s_Queue;
}t_park;


void* ingressoS(void* in);
void* ingressoP(void* in);
void* uscita(void* out);





