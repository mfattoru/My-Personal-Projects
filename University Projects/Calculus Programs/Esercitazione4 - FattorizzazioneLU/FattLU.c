/************************************************************************/
/*                                                                      */
/*     Creazione di un elemento di software matematico che              */
/*     implementi la Fattorizzazione LU di una matrice A fornita        */
/*     in input.                                                        */
/*     Sara' inoltre possibile risolvere il sistema definito da tale    */
/*     matrice.                                                         */
/*                                                                      */
/************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Prototipi delle function
void FattorizzazioneLU(double** A, int n, int ipiv[]);
void ForwardSubstitution_LYeqPB(double** A, double* B, double* Y, int n, int ipiv[]);
int BackSubstitution_UXeqY(double** A, double* B, double* Y, int n, int ipiv[]);
void StampaSol(double* Y, int n, int Comp);

int main()
{
    double **A;	    // Matrice da fattorizzare
    double *B;		// Vettore dei termini noti
    double *Y;		// Vettore delle soluzioni del sistema triangolare inferiore
    double *X;		// Vettore delle soluzioni del sistema triangolare superiore
    int n;		    // Dimensione della matrice quadrata
    int i,j;		// Indici dei cicli
    int* ipiv;		// Vettore delle permutazioni
    int Comp;		// Compatibilita' del sistema

    // Input del numero di righe e colonne della matrice
    printf("Inserire il numero di righe e colonne della matrice: ");
    scanf("%d",&n);

    // Allocazione della memoria per la matrice A
    A = (double**)malloc(n*sizeof(double*));
    for(i=0;i<n;i++)
        A[i] = (double*)calloc(n,sizeof(double));

    // Input della matrice A
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
        {
            printf("A[%d][%d]: ",i+1,j+1);
            scanf("%lf",&A[i][j]);
        }

    // Allocazione della memoria per il vettore dei termini noti B
    B = (double*)calloc(n,sizeof(double));

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
    Y = (double*)calloc(n,sizeof(double));

    // Allocazione della memoria per il vettore delle permutazioni ipiv
    ipiv = (int*)calloc(n,sizeof(int));

    // Fattorizzo la matrice A nelle matrici L e U
    FattorizzazioneLU(A,n,ipiv);

    // Stampo la matrice fattorizzata
    printf("\n\nMatrice L:\n");
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(i == j)
                printf("[1.000000]\t");
            else if(i > j)
                printf("[%lf]\t",A[ipiv[i]][j]);
            else
                printf("[0.000000]\t");
        }
        printf("\n");
    }
    printf("\n\nMatrice U:\n");
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(i <= j)
                printf("[%lf]\t",A[ipiv[i]][j]);
            else
                printf("[0.000000]\t");
        }
        printf("\n");
    }

    // Allocazione della memoria per il vettore delle soluzioni del sistema finale
    X = (double*)calloc(n,sizeof(double));

    // Risolvo il sistema triangolare inferiore LY = Pb
    ForwardSubstitution_LYeqPB(A,B,Y,n,ipiv);

    // Stampo il vettore dei termini noti modificato
    printf("\n\nVettore dei termini noti fattorizzato:\n");
    for(i=0;i<n;i++)
        printf("[%lf]\n",Y[i]);

    // Calcolo e stampo la soluzione del sistema
    Comp = BackSubstitution_UXeqY(A,Y,X,n,ipiv);

    StampaSol(X,n,Comp);

    // Deallocazione della memoria per tutte le strutture dati utilizzate
    for(i=0;i<n;i++)
    {
    	free(A[i]);
    }
    free(A);
    free(B);
    free(Y);
    free(X);
    free(ipiv);

    system("PAUSE");
    return 0;
}


/* Algoritmo di fattorizzazione LU; produce lo stesso risultato del  */
/* metodo di Gauss, con la differenza che separa le fasi di modifica */
/* della matrice attiva e del vettore dei termini noti.              */
void FattorizzazioneLU(double** A, int n, int ipiv[])
{
    int i,j,k,t,r,start=0;
    double mas;

    // Inizializzo il vettore ipiv
    for(i=0;i<n;i++)
        ipiv[i] = i;

    // Ciclo sui passi
    for(k=0;k<n-1;k++)
    {
        // Applico il pivoting parziale
        mas = fabs(A[ipiv[k]][k]);
        r = k;
        for(i=k+1;i<n;i++)
        {
            if(fabs(A[ipiv[i]][k]) > mas)
            {
                mas = fabs(A[ipiv[i]][k]);
                r = i;
            }
        }
        //--------------------STAMPA DEL PIVOT SELEZIONATO--------------
        printf("\nPIVOT: %lf\n",mas);
        if(r != k)
        {
            // Scambio virtuale delle righe
            t = ipiv[r];
            ipiv[r] = ipiv[k];
            ipiv[k] = t;
        }
        //----------------------STAMPA DEL VETTORE IPIV-----------------
        printf("\nipiv:{ ");
        for(start=0;start<n;start++){
            printf("%d ",ipiv[start]);
        }
        printf("}\n");
        // Calcolo degli elementi di L e U
        for(i=k+1;i<n;i++)
        {
            // Calcolo del moltiplicatore
            A[ipiv[i]][k] = A[ipiv[i]][k] / A[ipiv[k]][k];
            for(j=k+1;j<n;j++)
                // Modifica della matrice attiva
                A[ipiv[i]][j] = A[ipiv[i]][j] - (A[ipiv[i]][k] * A[ipiv[k]][j]);
        }
    }
}


/* Algoritmo di ForwardSubstitution particolarizzato al caso della fattorizzazione */
/* LU. In questo caso l'algoritmo procede nella maniera tradizionale, con          */
/* l'eccezione della mancata divisione per l'elemento diagonale, che ha sempre il  */
/* valore pari a 1.							                                       */
void ForwardSubstitution_LYeqPB(double** A, double* B, double* Y, int n, int ipiv[])
{
    int i,j;
    double r;

    // Calcolo il primo elemento
    Y[0] = B[ipiv[0]];

    i = 1;

    while(i<n)
    {
        // Calcolo del termine r
        r = B[ipiv[i]];

        for(j=0;j<i;j++)
            r = r - (A[ipiv[i]][j] * Y[j]);

        Y[i] = r;
        i++;
    }
}


/* Algoritmo di BackSubstitution particolarizzato al caso della fattorizzazione LU.  */
/* In questo caso l'algoritmo procede nella maniera tradizionale, non usando il      */
/* vettore ipiv per il vettore dei termini noti Y in quanto e' gia' stato permutato. */
/* Viene implementato anche un controllo sulla compatibilita' del sistema.	         */
int BackSubstitution_UXeqY(double** A, double* B, double* Y, int n, int ipiv[])
{
    int i,j;
    int Comp = 1;			// Per default il sistema e' determinato
    double r;

    // Calcolo della (n-1)-ma soluzione
    if(A[ipiv[n-1]][n-1] != 0)
        // Esiste la soluzione e la calcolo
        Y[n-1] = B[n-1] / A[ipiv[n-1]][n-1];
    else if(B[n-1] == 0)
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
        r = B[i];
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


/* Procedura che interpreta la compatibilita' del sistema e nel caso */
/* stampa il vettore delle soluzioni.				                 */
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


