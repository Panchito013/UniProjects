Scrivere una libreria thread-safe  con monitor Java per simulare la gestione di un parcheggio a pagamento con un solo ingresso P.

Il parcheggio va implementato attraverso un monitor con un contatore dei posti disponibili (fino ad un numero massimo MAXP) e le funzioni per entrare ed uscire.
Ogni auto corrisponde ad un thread che utilizza le procedure del monitor per entrare ed uscire dal parcheggio un certo numero di volte fissato a priori. Quando il parcheggio è pieno le auto in arrivo devono rimanere in attesa alla sbarra. Quando si libera un posto nel parcheggio l'auto che esce deve segnalare il posto  libero ai processi in coda.
