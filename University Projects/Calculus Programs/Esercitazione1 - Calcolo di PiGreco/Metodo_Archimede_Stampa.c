/*
La complessit� computazionale del metodo di Cramer applicato ad un sistema di ordine n �:

T(n) = O((n+1)!)

La risoluzione di un sistema di equazioni lineari di ordine n mediante l�algoritmo di eliminazione di Gauss e di back-substitution ha una complessit� di tempo:
T(Gauss+Back) (n) = O(n^3)


La complessit� di spazio dell'algoritmo di eliminazione di Gauss per una matrice di ordine n �:
S(Gauss) (n) = n(n+1) = O(n^2)

Calcolare SOLO la fattorizzazione LU di A ha un costo computazionale di:
T = O(n^3/3)

Risolvere m coppie di sistemi triangolari (uno inferiore ed uno superiore), ha un costo computazionale di
O(m^2) per ciascuna di esse.

Di conseguenza il costo computazionale totale � ora:
O(n^3/3 + mn^2)

Inversa di una matrice:
T = O(4/3 n^3)

Calcolo del determinante CON la fattorizzazione LU:
O(n^3/3)

Calcolo del determinante SENZA la fattorizzazione LU:
O(n!)

Complessit� di spazio per memorizzare una matrice:
O(n^2)

Complessit� di spazio per memorizzare una matrice triangolare:
O(n^2/2)


Forward substitution per un sistema con matrice triangolare inferiore bidiagonale, derivante dalla fattorizzazione LU senza pivoting di una matrice tridiagonale.

Backward substitution per un sistema con matrice triangolare superiore bidiagonale, derivante dalla fattorizzazione LU senza pivoting di una matrice tridiagonale

La complessit� di tempo e spazio dei due algoritmi �:
O(n)

Complessit� di tempo rispetto la fattorizzazione LU senza pivoting di una matrice a banda memorizzata secondo lo schema band storage:
T = O(npq)Al crescere di p e q la complessit� di tempo si avvicina a
O(n^3) flop
cio� a quella dell�algoritmo per una matrice di dimensione n � n, e che per p, q = n, essa � proprio O(n^3).

La complessit� di spazio � quella richiesta dallo schema di memorizzazione a banda, ossia
S = (n, p, q) = (p + q + 1)n = O((p + q + 1)n)

Forward substitution per un sistema con matrice triangolare inferiore derivante dalla fattorizzazione LU senza pivoting di una matrice a banda:
T(n, p) = O(np) flop

Back substitution per un sistema con matrice triangolare superiore derivante dalla fattorizzazione LU senza pivoting di una matrice a banda:
T(n, q) = O(nq) flForward substitution per un sistema con matrice triangolare inferiore derivante dalla fattorizzazione LU senza pivoting di una matrice a banda:
T(n, p) = O(np) flop

Back substitution per un sistema con matrice triangolare superiore derivante dalla fattorizzazione LU senza pivoting di una matrice a banda:
T(n, q) = O(nq) flop

Complessit� di tempo per la fattorizzazione LU con pivoting parziale di una matrice a banda:
TLUband+piv(n, p, q) = O(np(p + q + 1)) flop

Complessit� di spazio per la fattorizzazione LU con pivoting parziale di una matrice a banda:
SLUband+piv(n, p, q) = O((2p + q + 1)n)

Complessit� di tempo per la fattorizzazione di una matrice simmetrica:
O(n^3/6)

La complessit� di spazio dell�algoritmo per la fattorizzazione di una matrice simmetrica � quella dell�algoritmo di eliminazione di Gauss, per matrici generiche, cio� O(n^2), a meno che non si utilizzi uno schema di memorizzazione packed. In quest�ultimo caso la complessit� �:
O(n^2/2)

La complessit� asintotica di tempo richiesta dall�algoritmo per la costruzione del polinomio interpolante espresso nella formula di Lagrange �:
T(n) = O(n^2) flop
Al variare di n occorre effettuare di nuovo tutte le valutazioni.

La complessit� di tempo dell'algoritmo di Horner per la valutazione di un polinomio espresso nella formula di Newton �:
T(n) = O(n) flop

La complessit� di tempo e, quindi l�efficienza, il numero di operazioni richieste dal metodo di eliminazione di Gauss per matrici tridiagonali �:
T = O(n)


*/
