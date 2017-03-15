void* foo (votd* vargp){
        int myid;
        myid = *((int*)vargp);
        printf("%d",myid);
}


int main(){

        pthread_t tid[2];
        int i,*ptr;
        ptr = malloc(sizeof(int));
        for(i = 0; i < 2 ; i++){
                *ptr = i;
                pthread_create(&tid[i],NULL,foo,ptr);
         }

}

//problema di Race condition tra main e thread creati. La race condition è sulla cella di memoria. il puntatore della cella di memoria nel "for" potrebbe andare avanti mentre un thread
//concorrentemente potrebbe stampare.

========================================================================
ESERCIZIO:

mutex m = 1 //in memoria condivisa

//pattern

loop1 :
	mlock(); //down() se si tratta di semafori e non mutex
	...//sezione critica
	munlock(); //up() se si tratta di semafori e non mutex
	... 

loop2 :
        mlock();
        ...//sezione critica
        munlock();
        ...

1) supponiamo di avere k posti da allocare k risorse:

Sem risorse = k;

//pattern del thread-iesimo

loop: 
	down(risorse); //acquisizione 
	//controllo sulle risorse : con mutex poiché il semaforo soltanto non garantisce la mutua esclusione
	{
	down(m);
	//controllo
	up(m);
	}
	//sezione critica
	up(risorse);
2) Comunicazione asincrona con i semafori

//Ho un thread0 che coordina altri thread

//Memoria condivisa:

Sem S[n];
S[i] = 0 per ogni thread;

//T0:
up(S[i]);

//T-ieasimo
down(S[i]);


// Comunicazione Sincrona

//memoria condivisa:
Sem S = 0;
Sem T = 1;
msg //buffer

//Thread0 Loop:
var x;
down(T);
msg = x;
up(S);

//Thread1 Loop:
var y;
down(S);
y = msg;
up(T);

//LETTORI SCRITTORI:

//Memoria condivisa:
mutex m = 1;
DB;
int NR = 0;
mutex c = 1;

//Reader:
down(c);
NR++;
if(NR==1)
    down(m);
up(c);

//sezione critica
read(DB);

down(c);
NR--
if(NR == 0)
    up(m);
up(c);

//Writer:
down(m);
//sezione critica
{
write(DB);
}
up(m);


