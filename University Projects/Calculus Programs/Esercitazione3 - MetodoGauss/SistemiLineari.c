/************************************************************************/
/*                                                                      */
/*     Creazione di un elemento di software matematico per la           */
/*     risoluzione di sistemi diagonali, triangolari superiori e        */
/*     inferiori. Tali algoritmi utilizzano anche una flag sulla        */
/*     compatibilità del sistema. E' implementata inoltre una           */
/*     funzione per il riconoscimento del tipo di sistema.              */
/*     E' implementata inoltre una funzione per la risoluzione di       */
/*     sistemi mediante l'algoritmo di Gauss con e senza pivoting.      */
/*                                                                      */
/************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>


// Prototipi delle funzioni utilizzate
int ControlloMatrice(double** A, int n);
int SistemaDiagonale(double** A, double* B, double* Y, int n);
int ForwardSubstitution(double** A, double* B, double* Y, int n);
int BackSubstitution(double** A, double* B, double* Y, int n, int ipiv[]);
void Gauss(double** A, double* B, int n);
void GaussPiv(double** A, double* B, int n, int ipiv[]);
void Pivoting(double** A, double* B, int n, int k, int ipiv[]);
void StampaSol(double* Y, int n, int Comp);


int main()
{
    double **A;         // Matrice
    double *B;          // Vettore dei termini noti
    double *Y;          // Vettore delle soluzioni
    int n;              // Dimensione della matrice quadrata
    int i,j;            // Indici dei cicli
    int Scelta;         // Variabile di scelta
    int Comp;		    // Compatibilità del sistema
    int* ipiv;          // Vettore delle permutazioni
    int Tipo;           // Tipologia di sistema

    // Input del numero di righe e colonne della matrice
    printf("Inserire il numero di righe e colonne della matrice: ");
    scanf("%d",&n);

    // Allocazione della memoria per la matrice A
    A = (double**)malloc(n*sizeof(double*));
    for(i=0;i<n;i++)
        A[i] = (double*)malloc(n*sizeof(double));

    // Input della matrice A
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
        {
            printf("A[%d][%d]: ",i+1,j+1);
            scanf("%lf",&A[i][j]);
        }

    // Allocazione della memoria per il vettore dei termini noti B
    B = (double*)malloc(n*sizeof(double));

    // Input del vettore dei termini noti B
    for(i=0;i<n;i++)
    {
        printf("b[%d]: ",i+1);
        scanf("%lf",&B[i]);
    }

    // Visualizzazione della matrice completa del sistema
    printf("La matrice inserita e':\n");
    for(i=0;i<n;i++)
    {
    	for(j=0;j<n;j++)
	    {
            printf("[%lf]\t",A[i][j]);
	    }
	    printf(" = [%lf]\n",B[i]);
    }

    // Allocazione della memoria per il vettore delle soluzioni Y
    Y = (double*)malloc(n*sizeof(double));

    // Allocazione della memoria e inizializzazione del vettore delle permutazioni ipiv
    ipiv = (int*)malloc(n*sizeof(int));
    for(i=0;i<n;i++)
    	ipiv[i] = i;

    // Controllo della tipologia del sistema
    Tipo = ControlloMatrice(A,n);

    // Utilizzo il metodo adatto alla tipologia del sistema
    switch(Tipo)
    {
        case 1:
            printf("\n\nIl sistema e' diagonale.\n\n");
            Comp = SistemaDiagonale(A,B,Y,n);
            StampaSol(Y,n,Comp);
            break;
        case 2:
            printf("\n\nIl sistema e' triangolare superiore.\n\n");
            Comp = BackSubstitution(A,B,Y,n,ipiv);
            StampaSol(Y,n,Comp);
             break;
        case 3:
            printf("\n\nIl sistema e' triangolare inferiore.\n\n");
            Comp = ForwardSubstitution(A,B,Y,n);
            StampaSol(Y,n,Comp);
            break;
        case 0:
            printf("\n\nIl sistema non e' ne' triangolare ne' diagonale.\n\n");
            do
            {
                printf("\nRisoluzione con il metodo di Gauss:\n1. Senza Pivoting\n2. Con Pivoting\n");
                scanf("%d",&Scelta);
            }while(Scelta != 1 && Scelta != 2);
            if(Scelta == 1)
            {
                    Gauss(A,B,n);
            	    Comp = BackSubstitution(A,B,Y,n,ipiv);
                    StampaSol(Y,n,Comp);
            }
            else
            {
                    GaussPiv(A,B,n,ipiv);
                    Comp = BackSubstitution(A,B,Y,n,ipiv);
                    StampaSol(Y,n,Comp);
            }
            break;
    }

    // Deallocazione della memoria per tutte le strutture dati utilizzate
    for(i=0;i<n;i++)
    {
    	free(A[i]);
    }
    free(A);
    free(B);
    free(Y);
    free(ipiv);

    system("PAUSE");
    return 0;
}


/************************************************************/
/* Questa funzione risolve un sistema diagonale.            */
/* Restituisce un intero indicante la compatibilità del     */
/* sistema (1=Compatibile, 2=Indeterminato, 3=Impossibile)  */
/************************************************************/
int SistemaDiagonale(double** A, double* B, double* Y, int n)
{
    int i;
    int Comp = 1;
    i = 0;
    while(i<n && Comp != 3)
    {
        if(A[i][i] != 0)
            // Esiste la soluzione e la calcolo
            Y[i] = B[i] / A[i][i];
        else if (B[i] == 0)
        {
            // Il sistema è indeterminato, dò un valore a caso a Y[i] e continuo
            Y[i] = 0;
            Comp = 2;
        }
        else
            // Il sistema è impossibile
            Comp = 3;
        i++;
    }
    return Comp;
}


/************************************************************/
/* Questa funzione risolve un sistema triangolare inferiore.*/
/* Restituisce un intero indicante la compatibilità del     */
/* sistema (1=Compatibile, 2=Indeterminato, 3=Impossibile)  */
/************************************************************/
int ForwardSubstitution(double** A, double* B, double* Y, int n)
{
    int i,j;
    int Comp = 1;
    double r;

    // Calcolo della prima soluzione
    if(A[0][0] != 0)
        // Esiste la soluzione e la calcolo
        Y[0] = B[0] / A[0][0];
    else if(B[0] == 0)
    {
        // Il sistema è indeterminato, dò un valore a caso a Y[0] e continuo
    	Y[0] = 0;
        Comp = 2;
    }
    else
        // Il sistema è impossibile
        Comp = 3;

    i = 1;
    while(i<n && Comp !=3)
    {
        // Calcolo del termine r
        r = B[i];
        for(j=0;j<i;j++)
            r = r - (A[i][j] * Y[j]);
      	if(A[i][i] != 0)
        	// Esiste la soluzione e la calcolo
            Y[i] = r / A[i][i];
        else if(r == 0)
	    {
            // Il sistema è indeterminato, dò un valore a caso a Y[i] e continuo
	        Comp = 2;
	        Y[i] = 0;
	    }
	    else
	        // Il sistema è impossibile
	        Comp = 3;
	    i++;
    }
    return Comp;
}


/************************************************************/
/* Questa funzione risolve un sistema triangolare superiore.*/
/* Questa funzione utilizza lo scambio virtuale delle righe */
/* realizzato attraverso l'uso del vettore ipiv.            */
/* Restituisce un intero indicante la compatibilità del     */
/* sistema (1=Compatibile, 2=Indeterminato, 3=Impossibile)  */
/************************************************************/
int BackSubstitution(double** A, double* B, double* Y, int n, int ipiv[])
{
    int i,j;
    int Comp = 1;
    double r;

    // Calcolo della (n-1)-ma soluzione
    if(A[ipiv[n-1]][n-1] != 0)
        // Esiste la soluzione e la calcolo
        Y[n-1] = B[ipiv[n-1]] / A[ipiv[n-1]][n-1];
    else if(B[ipiv[n-1]] == 0)
    {
        // Il sistema è indeterminato, dò un valore a caso a Y[n-1] e continuo
	    Y[n-1] = 0;
        Comp = 2;
    }
    else
        // Il sistema è impossibile
        Comp = 3;

    i = n-2;
    while(i>=0 && Comp !=3)
    {
        // Calcolo del termine r
        r = B[ipiv[i]];
        for(j=i+1;j<n;j++)
            r = r - (A[ipiv[i]][j] * Y[j]);
    	if(A[ipiv[i]][i] != 0)
            // Esiste la soluzione e la calcolo
    	    Y[i] = r / A[ipiv[i]][i];
        else if(r == 0)
	    {
            // Il sistema è indeterminato, dò un valore a caso a Y[i] e continuo
	        Comp = 2;
	        Y[i] = 0;
	    }
    	else
	        // Il sistema è impossibile
            Comp = 3;
	    i--;
    }
    return Comp;
}


/************************************************************/
/* Questa funzione riorganizza il sistema applicando le     */
/* operazioni ammesse dal metodo di eliminazione di Gauss.  */
/* La matrice in output avrà nel triangolo superiore la     */
/* matrice modificata, mentre nel triangolo inferiore ci    */
/* saranno i moltiplicatori utilizzati.                     */
/************************************************************/
void Gauss(double** A, double* B, int n)
{
    int i,j,k;
    for(k=0;k<=(n-2);k++)                                   // Ciclo sui passi
    {
        for(i=k+1;i<n;i++)
        {
            A[i][k] = A[i][k] / A[k][k];                    // Calcolo dei moltiplicatori
            for(j=k+1;j<n;j++)
                A[i][j] = A[i][j] - (A[i][k] * A[k][j]);    // Trasformazione matrice attiva
            B[i] = B[i] - (A[i][k] * B[k]);                 // Trasformazione termini noti
        }
    }
}


/************************************************************/
/* Questa funzione riorganizza il sistema applicando le     */
/* operazioni ammesse dal metodo di eliminazione di Gauss.  */
/* Per evitare la propagazione degli errori di round-off    */
/* viene utilizzata la strategia di pivoting parziale.      */
/* La matrice in output avrà nel triangolo superiore la     */
/* matrice modificata, mentre nel triangolo inferiore ci    */
/* saranno i moltiplicatori utilizzati.                     */
/************************************************************/
void GaussPiv(double** A, double* B, int n, int ipiv[])
{
    int i,j,k;

    // Ciclo sui passi
    for(k=0;k<n-1;k++)
    {
        // Applico il pivoting parziale
        Pivoting(A,B,n,k,ipiv);
        for(i=k+1;i<n;i++)
        {
            // Calcolo dei moltiplicatori
            A[ipiv[i]][k] = A[ipiv[i]][k] / A[ipiv[k]][k];
            for(j=k+1;j<n;j++)
            {
                // Trasformazione matrice attiva
                A[ipiv[i]][j] = A[ipiv[i]][j] - (A[ipiv[i]][k] * A[ipiv[k]][j]);
            }
            // Trasformazione vettore dei termini noti
            B[ipiv[i]] = B[ipiv[i]] - (A[ipiv[i]][k] * B[ipiv[k]]);
        }
    }
}


/************************************************************/
/* Questa funzione applica il pivoting parziale alla matrice*/
/* fornita in input, che consiste nello spostamento (solo   */
/* virtuale, realizzato con il vettore ipiv) dell'elemento  */
/* massimo in valore assoluto alla posizione                */
/* diagonale A(k,k).                                        */
/************************************************************/
void Pivoting(double** A, double* B, int n, int k, int ipiv[])
{
    int start=0;
    int i,j,r,t;
    double mas;

    // Inizializzo il massimo e l'indice al valore dell'elemento diagonale
    mas = fabs(A[ipiv[k]][k]);
    r = k;

    // Ciclo per la ricerca del massimo
    for(i=k+1;i<n;i++)
    {
        if(fabs(A[ipiv[i]][k]) > mas)
        {
            mas = fabs(A[ipiv[i]][k]);
            r = i;
        }
    }
    printf("\nPIVOT: %lf\n",mas);
    // Scambio degli indici di riga se il massimo è diverso dall'elemento diagonale
    if(r != k)
    {
        // Scambio l'indice ipiv[r] con ipiv[k]
        t = ipiv[r];
	    ipiv[r] = ipiv[k];
	    ipiv[k] = t;
    }
     //---------------------------------------------------------stampa di ipiv per controllare le righe scambiate ad ogni iterazione-----------------
    printf("\nipiv:{ ");
    for(start=0;start<n;start++){
        printf("%d ",ipiv[start]);
    }
    printf("}\n");
}


/************************************************************/
/* Questa funzione stampa a video la compatibilità del      */
/* del sistema e l'eventuale soluzione.                     */
/************************************************************/
void StampaSol(double* Y, int n, int Comp)
{
    int i;

    if(Comp == 2)                           // Sistema indeterminato
    {
    	printf("\nIl sistema e' indeterminato; una possibile soluzione e':\n\n");
    	for(i=0;i<n;i++)
	       	printf("[%lf]\n",Y[i]);
    }
    else if(Comp == 3)                      // Sistema impossibile
    	printf("\nIl sistema e'impossibile.\n\n");
    else                                    // Sistema compatibile
    {
	    printf("\nIl sistema e' determinato e la soluzione e':\n\n");
	    for(i=0;i<n;i++)
		    printf("[%lf]\n",Y[i]);
    }
}


/************************************************************/
/* Questa funzione verifica la tipologia di matrice         */
/* (diagonale,triangolare superiore, triangolare inferiore) */
/* restituendo un intero indicante tale informazione        */
/* (rispettivamente 1,2,3). Restituisce il valore 0 se la   */
/* matrice non appartiene a nessuna delle categorie citate. */
/************************************************************/
int ControlloMatrice(double** A, int n)
{
    int i,j;
    int Tipo;

    // Controllo se la matrice è diagonale
    i = 0;
    Tipo = 1;
    while(i<n && Tipo == 1)
    {
        j = 0;
        while(j<n && Tipo == 1)
        {
            if(j != i && A[i][j] != 0)
                Tipo = 0;
            j++;
        }
        i++;
    }
    // Se la matrice non è diagonale
    if(Tipo == 0)
    {
        // Controllo se la matrice è triangolare superiore
        i = n-1;
        Tipo = 2;
        while(i>=0 && Tipo == 2)
        {
            j = i - 1;
            while(A[i][j] == 0 && j >= 0)
                j--;
            if(j != -1)
                Tipo = 0;
            i--;
        }
    }
    // Se la matrice non è triangolare superiore
    if(Tipo == 0)
    {
        // Controllo se la matrice è triangolare inferiore
        i = 0;
        Tipo = 3;
        while(i<n && Tipo == 3)
        {
            j = i+1;
            while(A[i][j] == 0 && j < n)
                j++;
            if(j != n)
                Tipo = 0;
            i++;
        }
    }
    return Tipo;
}

/*
Un problema da affrontare nell’algoritmo di eliminazione di Gauss riguarda la possibilit`a
che ad un certo passo k, per k = 1, . . . , n − 1, l’elemento a(k−1)
k,k sia nullo. Se una tale
eventualit`a si verifica non risulta possibile definire i moltiplicatori mi,k in quanto ci si
troverebbe ad effettuare una divisione per zero.
*/
