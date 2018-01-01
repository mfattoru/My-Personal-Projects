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


int main()
{
    double **A;	    	// Matrice da fattorizzare
    double **B;		// Matrice dei termini noti
    double **Y;		// Matrice delle soluzioni del sistema triangolare inferiore
    double **X;		// Matrice delle soluzioni del sistema triangolare superiore
    int n;			// Dimensione della matrice quadrata
    int i,j;			// Indici dei cicli
    int* ipiv;			// Vettore delle permutazioni
    int Comp;			// Compatibilita' del sistema		
    int NumSist;		// Numero di sistemi da risolvere
    
    // Input del numero di righe e colonne della matrice
    printf("Inserire il numero di righe e colonne della matrice: ");
    scanf("%d",&n);
    
    // Input del numero di sistemi da risolvere
    printf("Inserire il numero di sistemi da risolvere: ");
    scanf("%d",&NumSist);
    
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
    
    // Allocazione della memoria per i vettori dei termini noti B[i]
    B = (double**)calloc(NumSist,sizeof(double*));
    for(i=0;i<NumSist;i++)
    	B[i] = (double*)calloc(n,sizeof(double));

    // Input dei vettori dei termini noti B
    for(i=0;i<NumSist;i++)
    {
    	printf("Inserire i termini noti del sistema %d\n",i+1);
    	for(j=0;j<n;j++)
    	{
    		printf("b[%d]: ",j+1);
        	scanf("%lf",&B[i][j]);
        }
    }


    // Allocazione della memoria per i vettori delle soluzioni Y[i]
    Y = (double**)calloc(NumSist,sizeof(double*));
    for(i=0;i<NumSist;i++)
    	Y[i] = (double*)calloc(n,sizeof(double));

    // Allocazione della memoria per il vettore delle permutazioni ipiv
    ipiv = (int*)calloc(n,sizeof(int));
    
    // Fattorizzo la matrice A nelle matrici L e U    
    FattorizzazioneLU(A,n,ipiv);

    // Allocazione della memoria per i vettori delle soluzioni del sistema finale
    X = (double**)calloc(NumSist,sizeof(double*));
    for(i=0;i<NumSist;i++)
    	X[i] = (double*)calloc(n,sizeof(double));
    
    
    for(i=0;i<NumSist;i++)
    {    
    	// Risolvo il sistema triangolare inferiore LY = Pb
    	ForwardSubstitution_LYeqPB(A,B[i],Y[i],n,ipiv);
    
    	// Calcolo e stampo la soluzione del sistema
	Comp = BackSubstitution_UXeqY(A,Y[i],X[i],n,ipiv);
    }
    
    
    printf("La matrice delle soluzioni e':\n");
    for(i=0;i<NumSist;i++)
    {
    	for(j=0;j<n;j++)
    		printf("[%lf]\t",X[j][i]);
    	printf("\n");
    }

    system("PAUSE");
    return 0;
}


/* Algoritmo di fattorizzazione LU; produce lo stesso risultato del  */
/* metodo di Gauss, con la differenza che separa le fasi di modifica */
/* della matrice attiva e del vettore dei termini noti.              */
void FattorizzazioneLU(double** A, int n, int ipiv[])
{
    int i,j,k,t,r;
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
        if(r != k)
        {
            // Scambio virtuale delle righe
            t = ipiv[r];
            ipiv[r] = ipiv[k];
            ipiv[k] = t;
        }
        
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



