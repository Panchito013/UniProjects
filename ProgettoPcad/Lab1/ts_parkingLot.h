#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MAXP 100
#define TRUE 1
#define FALSE 0


typedef struct{
    unsigned int lotsCount;
}MONITOR;


MONITOR sharedMem;
pthread_mutex_t mutex_lotsCount;
pthread_cond_t p_Queue, s_Queue;
void* ingressoS();
void* ingressoP();
void* uscita();





