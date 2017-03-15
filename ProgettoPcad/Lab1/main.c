#include "ts_parkingLot.h"


int main(int argc, char** argv){
    if(argc != 3){
        fprintf(stderr, "Wrong parameters: lab1 [N] [K]");
        exit(5);
    }


int n = atoi(argv[1]);
int k = atoi(argv[2]);

pthread_t macchine[MAXP];


int i = 0;
for(i = 0; i < n; i++){
    if(pthread_create(macchine[i], NULL, task) != 0){
      printf("Error in thread creation");

    }
}

exit(0);


}