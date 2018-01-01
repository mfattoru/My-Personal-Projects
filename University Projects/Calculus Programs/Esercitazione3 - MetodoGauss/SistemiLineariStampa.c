/*

DOMANDE E RISPOSTE
RISOLUZIONE DI SISTEMI LINEARI
E
CALCOLO MATRICIALE



1) CHE COSA SI INTENDE PER MATRICE SINGOLARE?
Una matrice singolare è una matrice quadrata con determinante pari a zero.


2) QUAL E' LA COMPLESSITA' DI TEMPO E DI SPAZIO DELL'ALGORITMO DI BACK-SUBSTITUTION?
Tbs (n) = n^2  →  O ( n^2 )
Sbs (n) = n^2 + 2n  →  O ( n^2 )


3) QUAL E' LA COMPLESSITA' DI TEMPO E DI SPAZIO ASINTOTICA DEL METODO DI ELIMINAZIONE DI GAUSS?
Tgauss (n) = 2(n^3 – n)/3  flop + (n^2 – n)/2 flop = O(n^3)
(sostituire ad n la dimanesione della matrice per ricavare il numero di Flop necessari).
Sgauss (n) = n(n+1) = O(n^2)


4) DESCRIVERE IN COSA CONSISTE LA TECNICA DEL PIVOTING PARZIALE:
La strategia di pivoting parziale, seleziona l'elemento pivot al passo k, l' elemento di massimo modulo tra quelli della k-ma colonna a partire da quello diagonale e lo scambia.


5) DESCRIVERE COME INCIDE IL PIVOTING PARZIALE SULLA STABILITA' DELL'ALGORITMO DI GAUSS:
Il pivoting parziale rende l'algoritmo di Gauss praticamente stabile.



6) QUAL E' LA COMPLESSITA' DI TEMPO ASINTOTICA DEL METODO DI ELIMINAZIONE DI GAUSS CON PIVOTING PARZIALE?
TgaussPv (n) = O (n^2/2)


7) DIRE QUAL E' L'ALGORITMO PIU' EFFICIENTE PER FATTORIZZARE LA MATRICE NEL PRODOTTO DI DUE MATRICI  TRIANGOLARI E COME SI ESPRIME TALE FATTORIZZAZIONE:
E' l'algoritmo di fattorizzazione LU, dove L è la matrice triangolare inferiore composta dai moltiplicatori e con tutti 1 sulla diagonale principale, ed U è la matrice triangolare superiore ottenuta all'ultimo passo dell'algoritmo di eliminazione di Gauss.
Si ha quindi che LU=PA.


8) QUAL E' LA COMPLESSITA' DI TEMPO  ASINTOTICA DEL METODO DI FATTORIZZAZIONE LU?
TLU(n) = (n^3/3 + mn^2)




9) SCRIVERE LA COMPLESSITA' DI TEMPO ASINTOTICA DELL'ALGORITMO UTILIZZATO PER IL CALCOLO DELLA MATRICE INVERSA E PER IL CALCOLO DEL DETERMINANTE:
T^-1(n) = O(n^3/3) + 2nO(n^2/2) = O(4/3n^3)
T (n) determinante = O(n!) ed utilizzando la fattorizzazione LU il costo totale diventa = O(n^3/3)


10) DESCRIVERE BREVEMENTE L'ALGORITMO IMPLEMENTATO PER IL CALCOLO DELL'INVERSA DI UNA MATRICE QUADRATA, DI DIMENSIONE N TRIANGOLARE SUPERIORE:
Per calcolare l'inversa di una assegnata matrice A di dimensione n, triangolare superiore occorre effettuare n volte l'algoritmo di back-substitution.
(L'algoritmo implementato sfrutta la fattorizzazione LU per il calcolo della matrice inversa, ma siccome nel nostro caso la matrice è già triangolare superiore l'algoritmo esegue solo n volte la back-substitution).


11) ENUNCIARE IL TEOREMA DEL CONDIZIONAMENTO:
Sia || . || una norma matriciale submoltiplicativa (cioè ||AB|| <= ||A|| ||B||) e compatibile con una norma vettoriale (cioè ||Ax|| <= ||A|| ||x|| per ogni x diverso da 0 ). Sia inoltre il sistema Ax = b (con A non singolare) e si consideri il sistema perturbato:


(A + ∆A) (x + ∆x) = (b+∆b)

Se
||∆A|| < 1 / ||A^-1||

posto μ(A) = ||A|| ||A^-1|| si ha:

||∆x|| / ||x|| <= μ(A) / (1 – μ(A) ||∆A|| / ||A|| )  (||∆A|| / ||A|| + ||∆b|| / ||b|| )




12) ENUNCIARE IL CRITERIO DI SYLVESTER:
Sia A una matrice simmetrica  reale n x n (i cui valori sono numeri reali). Per i=1....n, sia Di il determinante del minore ottenuto cancellando da A le ultime n-i righe e le ultime n-i colonne. La matrice A è definita positiva se e solo se Di > 0 per ogni i.


13) QUANDO UNA MATRICE SI DEFINISCE POSITIVA?
Una matrice A simmetrica si definisce positiva se per ogni x, con x diverso da zero, risulta che:
x^TAx > 0


14) SPIEGARE IN COSA CONSISTE LA FATTORIZZAZIONE DI CHOLESKY:
Sia A appartenente ad R^nxn un matrice simmetrica definita positiva.
Allora esiste una ed una sola matrice triangolare inferiore L appartenente ad R^nxn,
con lk,k > 0 per k = 1..n, tale che:

A = LL^T







15) DIRE QUAL E' L'ALGORITMO PIU' EFFICIENTE PER LA FATTORIZZARE LA MATRICE SIMMETRICA S (NON POSITIVA), NEL PRODOTTO DI DUE MATRICI TRIANGOLARI, E COME SI ESPRIME TALE FATTORIZZAZIONE?
Sia A ∈ ℜ^n×n una matrice simmetrica tale che tutte le sue sottomatrici principali sono non singolari. Esistono allora una ed una sola matrice L ∈ ℜ^n×n triangolare unitaria inferiore ed una ed una sola matrice D ∈ ℜ^n×n diagonale tali che
A = LDL^T

Inoltre, L coincide con la matrice triangolare inferiore della fattorizzazione LU di A
e gli elementi diagonali di D coincidono con i corrispondenti elementi diagonali della matrice triangolare superiore della fattorizzazione LU di A, ovvero L^T = D^−1U.
I risultati precedenti suggeriscono che il calcolo della fattorizzazione LDL^T si può eseguire modificando opportunamente l’algoritmo di eliminazione di Gauss, utilizzato per ottenere la fattorizzazione LU. Inoltre, grazie alla simmetria della matrice A e delle sottomatrici attive, ad ogni passo, dopo avere calcolato i moltiplicatori, si può operare solo sul triangolo superiore della sottomatrice attiva corrente.
L’algoritmo si può eseguire in place, memorizzando gli elementi del triangolo superiore di A al posto
dei corrispondenti elementi di L^T e gli elementi diagonali di D al posto di quelli di A;
gli elementi diagonali di L, essendo tutti uguali ad 1, non sono memorizzati. Una descrizione di tale algoritmo `e fornita di seguito.


16) SI DESCRIVA LA COMPLESSITA' DI TEMPO E DI SPAZIO ASINTOTICA DELL'ALGORITMO DI FATTORIZZAZIONE LU SENZA PIVOTING SPECIFICO PER UNA MATRICE A BANDA.
TLUband (n,p,q) = O(npq) flop
SLUband (n,p,q) = (p + q + 1)n = O((p + q + 1)n)


17) DESCRIVERE UNO SCHEMA DI MEMORIZZAZIONE DI UNA MATRICE A BANDA CHE CONSENTA UN RISPARMIO IN TERMINI DI COMPLESSITA' DI SPAZIO RISPETTO ALLA MEMORIZZAZIONE DI TUTTI GLI ELEMENTI DELLA MATRICE:
In generale, per memorizzare una generica matrice a banda A, di dimensione nxn, con ampiezza di banda  p e q, si utilizza un array bidimensionale di dimensione(p+q+1)xn, nel modo seguente:
AB(q + 1 + i – j,j) = aij, max(1,j - q) <= i<=min(n,j + p),
Tale schema di memorizzazione è detto a banda ed ha una complessità di spazio pari a (p + q + 1)n.
E' chiaro che la memorizzazione a banda è significativamente vantaggiosa, rispetto alla usuale memorizzazione mediante un array bidimensionale di dimensione nxn, se p,q << n/2.


18) DESCRIVERE UNO SCHEMA DI MEMORIZZAZIONE DI UNA MATRICE TRIDIAGONALE CHE CONSENTA UN RISPARMIO IN TERMINI DI COMPLESSITA' DI SPAZIO RISPETTO ALLA MEMORIZZAZIONE DI TUTTI GLI ELEMENTI DELLA MATRICE:
In generale, data una matrice tridiagonale A di dimensioni nxn si utilizza un array monodimensionale di lunghezza n per memorizzare la diagonale principale e due array monodimensionali di lunghrzza n-1 per memorizzare la diagonale inferiore e quella superiore. Tale schema di memorizzazione ha una complessita' di spazio pari a 3n-2, cioè O(n), di un ordine di grandezza inferiore rispetto alla usuale memorizzazione mediante un array bidimensionale.


19) SI DESCRIVA LA COMPLESSITA' DI TEMPO E DI SPAZIO ASINTOTICA DELL'ALGORITMO DI FATTORIZZAZIONE LU SENZA PIVOTING SPECIFICO PER UNA MATRICE TRIDIAGONALE.
TLUtrid(n) = 3n – 3 = O( n) flop
SLUtrid(n) = 3n – 2 = O( n)
20) SPIEGARE BREVEMENTE I VANTAGGI COMPUTAZIONALI CHE SI OTTENGONO SCAMBIANDO VIRTUALMENTE INVECE CHE EFFETTIVAMENTE LE RIGHE DELLA MATRICE:
Utilizzando il vettore Ipiv per non scambiare fisicamente le righe della matrice e quindi evitare di costruire la matrice per gli scambi, e nella forward-substitution tramite Ipiv già si conoscono gli scambi da effettuare. Tutto a favore di minore memoria occupata e di vantaggi computazionali sui calcoli.


21) SI DESCRIVA UN ALTRO MODO IN CUI L'UTLIZZO DELLA FATTORIZZAZIONE LU CONSENTE UN RISPARMIO, IN TERMINI DI COSTO COMPUTAIZONALE, RISPETTO ALL'UTILIZZO DELL'ALGORITMO DI GAUSS.
La fattorizzazione LU oltre a calcolare l'inversa puo' risolvere il problema del calcolo del determinante.


15) DIRE QUAL E' L'ALGORITMO PIU' EFFICIENTE PER RISOLVERE UN SISTEMA LINEARE CON MATRICE SIMMETRICA DEFINITA POSITIVA? QUAL E' LA SUA COMPLESSITA' DI TEMPO E DI SPAZIO?
E' la fattorizzazione di Cholesky, ossia:
sia A appartenente ad R^nxn un matrice simmetrica definita positiva.
Allora esiste una ed una sola matrice triangolare inferiore L appartenente ad R^nxn,
con lk,k > 0 per k = 1..n, tale che:

A = LL^T

TChol(n) = O ( n^3/6) fllp.
SChol(n) = O ( n^2 ) mentre se si utilizza uno schema di memorizzazione packed risulta essere O ( n^2/2) e quindi risulta dimezzata.

*/
