#include "ts_parkingLot.h"


int main(int argc, char** argv){
    if(argc != 3){
        fprintf(stderr, "Wrong parameters: lab1 [N] [K]");
        exit(5);
    }


int N = atoi(argv[1]);
int K = atoi(argv[2]);
void* retPoint;

pthread_t macchine[MAXP];
t_park plot;
plot.p_Queue = (pthread_cond_t)PTHREAD_COND_INITIALIZER;
plot.s_Queue = (pthread_cond_t)PTHREAD_COND_INITIALIZER;

srand(time(NULL));
int exitC = rand()%N + 1;
int i = 0;
int k = 0;
while(k < K){
    printf("\nTentativo %d ", k);
    int entranceC = rand()%3 + 1;
    for(i = 0; i < N; i++){
        if(entranceC == 1){
            printf("\nIngresso di %d ", entranceC);
            pthread_create(&macchine[i], NULL, (void*) ingressoP, &plot);
        }
        if(entranceC == 2){
            printf("\nIngresso di %d ", entranceC);
            pthread_create(&macchine[i], NULL, (void*) ingressoS, &plot);
        }
    }

    sleep(2);

    if(entranceC == 3){
        printf("\nUscita");
        pthread_create(&macchine[exitC], NULL, (void*) uscita, &plot);
    }
    k++;
}

for(i = 0; i < N; i++)
    pthread_join(macchine[i],&retPoint);

exit(0);


}