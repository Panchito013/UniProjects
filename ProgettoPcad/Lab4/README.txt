Labo 4: ConnectionPool
Tutorial Java 
https://docs.oracle.com/javase/tutorial/essential/

Tutorial Java Concorrente
http://docs.oracle.com/javase/tutorial/essential/concurrency/

ConcurrentHashmap:
https://docs.oracle.com/javase/7/docs/api/java/util/concurrent/ConcurrentHashMap.html

Metodologie di programmazione:
https://dibris.aulaweb.unige.it/mod/resource/view.php?id=23326

Implementare una classe Java, ConnectionPool, per gestire richieste di connessioni HTTP attraverso un thread pool.

La classe deve fornire un metodo "request" che prende come parametro una stringa che rappresenta l'URI di una chiamata ad un servizio REST e sottomette al thread pool una richiesta di connessione, implementata attraverso un callable, all'indirizzo specificato. 

ConnectionPool deve quindi fornire un metodo 
- request (che al suo interno metterà in coda un task sul pool)
- stop (che serve a gestire la terminazione del pool)

I metodi request e stop potrebbero essere chiamati da diversi thread contemporaneamente.

Il metodo request deve sollevare eccezioni in caso di errori di connessione e restituire attraverso un Future i primi 10 caratteri dei dati disponibii all'indirizzo specificato nella connessione (oppure un booleano che rappresenta l'esito della conessione).

Per le connessioni usare URLconnection e metodi come openConnection
(vedi ad es. http://www.simplesoft.it/connessioni-http-in-java.html per gestire Proxy). In caso di problemi di connessione dal laboratorio simulate una connessione.

Implementare quindi un programma Java multithreaded che usa un'istanza comune del ConnectionPool per effettuare attraverso dei thread richieste multiple di connessione.

Gestire la terminazione del ConnectionPool usando il pattern visto a lezione (assumendo di lasciare il tempo al server di terminare le richieste).

Estensione con caching locale

Estendere quindi la classe in maniera tale da implementare un meccanismo di caching locale con apposita struttura dati  (NON su  file) per evitare di effettuare nuovamente connessioni già effettuate. 
Ad esempio usare una hashmap e per la cache (interna alla striuttura dati del pool) in modo da associare ad un URL la risposta calcolata (prima stringa del sito o un booleano che rappresenta esito della connessione).

Fare attenzione alla sincronizzazione tra le richieste multiple quando si legge/scrive nella cache in particolare per l'inserimento di nuove coppie.

Per assicurare thread-safeness usate la sincronizzazione Java oppure strutture dati concorrenti come le ConcurrentHashMap. 
Nel secondo caso seguite con attenzione i design pattern visti a lezione.

In particolare ricordate che contains e put singolarmente sono operazioni atomiche ma le due operazioni in cascata non rappresentano un blocco atomico. Provate ad usare per questo scopo putIfAbsent.


ConcurrentHashmap:
https://docs.oracle.com/javase/7/docs/api/java/util/concurrent/ConcurrentHashMap.html
