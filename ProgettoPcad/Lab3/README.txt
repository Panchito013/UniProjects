L'esercizio consiste nell'implementare in Java Concorrente l'algoritmo del Crivello di Eratostene per calcolare i numeri primi nell'intervallo 1..N.

L’algoritmo del crivello di Eratostene è basato sulla seguente idea. 
Per selezionare i numeri primi compresi tra 1 ed N prima si scrivono in sequenza tutti i numeri. Poi si iniziano a togliere i numeri divisibili per 2. Poi i numeri divisibili per il primo numero che rimane subito dopo il 2. Poi per quello seguente ecc. Alla fine rimarranno soli i numeri primi (vedi simulazione).

In questo algoritmo possiamo sfruttare la concorrenza costruendo una pipeline di thread T1 T2 T3... associati ai numeri primi P1 P2 P3 ... 

A partire da  P1=2, ogni  thread Ti è associato al numero primo Pi   e ha un canale di comunicazione (coda FIFO) con il thread precedente e successivo. 

Il thread Ti riceve una sequenza di numeri dal thread Ti-1 e passa a Ti+1 solo i numeri non divisibili per Pi (cioè filtra i numeri non primi rispetto a P1 ... Pi). 
Se Ti non ha ancora un thread successore, al primo numero Pi+1 non divisibile per Pi che riceve crea il thread Ti+1 associandolo a Pi+1 e poi continua a filtrare i numeri seguenti come descritto precedentemente.

Implementare un programma Java concorrente che implementi questo algoritmo,