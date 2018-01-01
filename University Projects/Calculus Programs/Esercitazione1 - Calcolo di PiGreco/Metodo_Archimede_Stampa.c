/*
La complessità computazionale del metodo di Cramer applicato ad un sistema di ordine n è:

T(n) = O((n+1)!)

La risoluzione di un sistema di equazioni lineari di ordine n mediante l’algoritmo di eliminazione di Gauss e di back-substitution ha una complessità di tempo:
T(Gauss+Back) (n) = O(n^3)


La complessità di spazio dell'algoritmo di eliminazione di Gauss per una matrice di ordine n è:
S(Gauss) (n) = n(n+1) = O(n^2)

Calcolare SOLO la fattorizzazione LU di A ha un costo computazionale di:
T = O(n^3/3)

Risolvere m coppie di sistemi triangolari (uno inferiore ed uno superiore), ha un costo computazionale di
O(m^2) per ciascuna di esse.

Di conseguenza il costo computazionale totale è ora:
O(n^3/3 + mn^2)

Inversa di una matrice:
T = O(4/3 n^3)

Calcolo del determinante CON la fattorizzazione LU:
O(n^3/3)

Calcolo del determinante SENZA la fattorizzazione LU:
O(n!)

Complessità di spazio per memorizzare una matrice:
O(n^2)

Complessità di spazio per memorizzare una matrice triangolare:
O(n^2/2)


Forward substitution per un sistema con matrice triangolare inferiore bidiagonale, derivante dalla fattorizzazione LU senza pivoting di una matrice tridiagonale.

Backward substitution per un sistema con matrice triangolare superiore bidiagonale, derivante dalla fattorizzazione LU senza pivoting di una matrice tridiagonale

La complessità di tempo e spazio dei due algoritmi è:
O(n)

Complessità di tempo rispetto la fattorizzazione LU senza pivoting di una matrice a banda memorizzata secondo lo schema band storage:
T = O(npq)Al crescere di p e q la complessità di tempo si avvicina a
O(n^3) flop
cioè a quella dell’algoritmo per una matrice di dimensione n × n, e che per p, q = n, essa è proprio O(n^3).

La complessità di spazio è quella richiesta dallo schema di memorizzazione a banda, ossia
S = (n, p, q) = (p + q + 1)n = O((p + q + 1)n)

Forward substitution per un sistema con matrice triangolare inferiore derivante dalla fattorizzazione LU senza pivoting di una matrice a banda:
T(n, p) = O(np) flop

Back substitution per un sistema con matrice triangolare superiore derivante dalla fattorizzazione LU senza pivoting di una matrice a banda:
T(n, q) = O(nq) flForward substitution per un sistema con matrice triangolare inferiore derivante dalla fattorizzazione LU senza pivoting di una matrice a banda:
T(n, p) = O(np) flop

Back substitution per un sistema con matrice triangolare superiore derivante dalla fattorizzazione LU senza pivoting di una matrice a banda:
T(n, q) = O(nq) flop

Complessità di tempo per la fattorizzazione LU con pivoting parziale di una matrice a banda:
TLUband+piv(n, p, q) = O(np(p + q + 1)) flop

Complessità di spazio per la fattorizzazione LU con pivoting parziale di una matrice a banda:
SLUband+piv(n, p, q) = O((2p + q + 1)n)

Complessità di tempo per la fattorizzazione di una matrice simmetrica:
O(n^3/6)

La complessità di spazio dell’algoritmo per la fattorizzazione di una matrice simmetrica è quella dell’algoritmo di eliminazione di Gauss, per matrici generiche, cioè O(n^2), a meno che non si utilizzi uno schema di memorizzazione packed. In quest’ultimo caso la complessità è:
O(n^2/2)

La complessità asintotica di tempo richiesta dall’algoritmo per la costruzione del polinomio interpolante espresso nella formula di Lagrange è:
T(n) = O(n^2) flop
Al variare di n occorre effettuare di nuovo tutte le valutazioni.

La complessità di tempo dell'algoritmo di Horner per la valutazione di un polinomio espresso nella formula di Newton è:
T(n) = O(n) flop

La complessità di tempo e, quindi l’efficienza, il numero di operazioni richieste dal metodo di eliminazione di Gauss per matrici tridiagonali è:
T = O(n)


*/
