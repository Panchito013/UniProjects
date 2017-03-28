#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<time.h>
#include <unistd.h>//per la sleep
//typedef enum bool_e{TRUE,FALSE}bool;
typedef struct Park
{
	int MaxPost;
	pthread_cond_t codaA;
	pthread_cond_t codaB;

}park_t;
void *asd;
park_t park;

int app=0;
typedef struct macchina
{
	pthread_t macchina;
	int id;
	int Ntentativi;

}Car;
Car ntid[100];
pthread_mutex_t accept_car = PTHREAD_MUTEX_INITIALIZER;


void *ParkA(int *id)
{
	int tent=0;
	
	while(tent<ntid[(*id)].Ntentativi)
	{
		//fprintf(stderr,"MAcchina %d entra nel posteggio; Numero tentativo \n: %d\n",ntid[*id].id,ntid[*id].Ntentativi);
		pthread_mutex_lock(&accept_car);
		while (park.MaxPost==0)
		{
			fprintf(stderr,"MAcchina %d in coda; Numero tentativo \n: %d\n",ntid[*id].id,ntid[*id].Ntentativi);
			pthread_cond_wait(&park.codaA,&accept_car);
			//fprintf(stderr,"MAcchina %d esce coda; Numero tentativo \n: %d\n",ntid[*id].id,ntid[*id].Ntentativi);
		}
		park.MaxPost--;
		printf("%d\n",park.MaxPost);
		pthread_mutex_unlock(&accept_car);
	
		sleep(2);

		pthread_mutex_lock(&accept_car);
		park.MaxPost++;	
		pthread_cond_signal(&park.codaA);
		pthread_cond_signal(&park.codaB);
		pthread_mutex_unlock(&accept_car);
		//fprintf(stderr,"MAcchina %d è uscita dal posteggio; Numero tentativo \n: %d\n",ntid[*id].id,ntid[*id].Ntentativi);
		tent++;	
	}
	pthread_exit(asd);
}

void *ParkB(int *id)
{
	int tent=0;
	while (tent<ntid[*id].Ntentativi)
	{
		pthread_mutex_lock(&accept_car);
		while (park.MaxPost==0)
		{
			//fprintf(stderr,"MAcchina %d in coda; Numero tentativo \n: %d\n",ntid[*id].id,ntid[*id].Ntentativi);
			pthread_cond_wait(&park.codaB,&accept_car);
			//fprintf(stderr,"MAcchina %d in coda; Numero tentativo \n: %d\n",ntid[*id].id,ntid[*id].Ntentativi);
		}	
		park.MaxPost--;
		printf("%d\n",park.MaxPost);
		pthread_mutex_unlock(&accept_car);
	
		sleep(1);

		pthread_mutex_lock(&accept_car);
		park.MaxPost++;
		pthread_cond_signal(&park.codaA);
		pthread_cond_signal(&park.codaB);
		pthread_mutex_unlock(&accept_car);
		//fprintf(stderr,"MAcchina %d è uscita dal posteggio; Numero tentativo \n: %d\n",ntid[*id].id,ntid[*id].Ntentativi);
		tent++;
	}
	pthread_exit(asd);
}

int main()
{
	fprintf(stderr,"/****Parcheggio Aperto*****/\n");
	//**
	//inzializzo struttura.
	park.MaxPost=10;
	park.codaA=(pthread_cond_t)PTHREAD_COND_INITIALIZER;
	park.codaB=(pthread_cond_t)PTHREAD_COND_INITIALIZER;
	//**
	
	int ingresso; //[1]->princilape [2]->secondario
	
	
	srand(time(NULL));
	int index=0;
	
	while (index<100)
	{
		//fprintf(stderr,"++++++%d\n",index);
		ingresso= rand()%2+1;
		ntid[index].id=index+1;
		ntid[index].Ntentativi=5;
		if(ingresso==1)		
		{
			pthread_create(&(ntid[index].macchina),NULL,(void*)ParkA,&ntid[index].id);//creo il thread loopA	
		}		
		if(ingresso==2)		
		{
			pthread_create(&(ntid[index].macchina),NULL,(void*)ParkB,&ntid[index].id);//creo il thread loopB
		}		
		index++;
	}
	for (index=0; index < 100; index++)
		pthread_join((ntid[index].macchina),asd);

	if(park.MaxPost!=10)
		fprintf(stderr,"Errore, posteggio non vuoto....!!! Impossibile chiudere il parcheggio!!Auto nel posteggio : %d\n",30-park.MaxPost);
	else
		fprintf(stderr,"/****Parcheggio Chiuso Con Successo*****/\n");
	
	return 0;
}
