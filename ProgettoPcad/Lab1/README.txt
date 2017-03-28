Scrivere una libreria thread-safe per simulare la gestione di un parcheggio con le seguenti caratteristiche:
un numero massimo di posti MAXP
un ingresso principale P
un ingresso secondario S.
Inoltre l'accesso al parcheggio è regolato nella seguente maniera:

se il parcheggio ha posti disponibili le auto entrano dai due ingressi
quando il parcheggio è pieno le auto in arrivo in uno dei due ingressi devono rimanere in attesa al corrispondente ingresso.
quando si libera un posto l'auto che esce deve segnalare il posto libero ai due ingressi dando priorità all'ingresso principale

Implementare una struttura dati condivisa per controllare i parametri necessari alla gestione del parcheggio (ad esempio il contatore dei posti disponibili)  attraverso procedure per l'operazione di ingresso per ogni parcheggio (ingressoP, ingressoS) 
ed una procedura per l'uscita (uscita). 

Per proteggere i dati condivisi:
usare mutex della libreria pthread
Per gestire le code di attesa sui due ingressi 

usare le variabili condizione della libreria pthread
Definire due costanti N e K.
Costruire un programma che, usando la libreria definita sopra, 
crea  N thread che simulano il comportamento delle auto.
Ogni thread  deve avere il seguente comportamento: 
per K volte prova ad entrare da una delle due entrate (usando la procedura ingressoP/ingressoS), aspetta  un  tempo casuale e poi esce dal parcheggio (usando la procedura uscita).
