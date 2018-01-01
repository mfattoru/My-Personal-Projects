/* 

   Creazione di un elemento di software che implementi la fattorizzazione
   LU specializzata al caso di matrici strutturate. In questo caso la
   matrice e' una matrice a banda con ampiezza di banda superiore q e
   ampiezza di banda inferiore p. Cio' permette di ridurre la complessita'
   dell'algoritmo di fattorizzazione LU.
   La matrice fornita in input sara' memorizzata secondo lo schema di 
   memorizzazione band storage.
   
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Prototipi delle function utilizzate
void BandStorage(double**,double**,int,int,int);
int Max(int,int);
int Min(int,int);
void BandLU(double**, int, int, int);
void BandFS(double**, double*, int, int, int);
void BandBS(double**, double*, int, int, int);


int main()
{
	double** A;			// Matrice di partenza
	double** AB;		// Matrice memorizzata con band storage
	double* B;			// Vettore dei termini noti
	int n;				// Dimensione della matrice quadrata
	int i,j;			// Indici dei cicli
	int p;				// Ampiezza di banda inferiore
	int q;				// Ampiezza di banda superiore
	int w;				// Ampiezza di banda della matrice


	// Input del numero di righe e colonne della matrice
	printf("Inserire il numero di righe e di colonne della matrice: ");
	scanf("%d",&n);

	// Allocazione della memoria per la matrice A
	A = (double**)calloc(n,sizeof(double*));
	for(i=0;i<n;i++)
		A[i] = (double*)calloc(n,sizeof(double));

	// Input della matrice A
	printf("Inserire la matrice: \n");
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
		{
			printf("A[%d][%d]: ",i+1,j+1);
			scanf("%lf",&A[i][j]);
		}

	// Input delle due ampiezze di banda
	printf("Inserire la dimensione della banda superiore: ");
	scanf("%d",&q);
	printf("Inserire la dimensione della banda inferiore: ");
	scanf("%d",&p);
	
	// Calcolo dell'ampiezza di banda totale
	w = p+q+1;
	
	// Allocazione della memoria per la matrice AB, rappresentazione in band storage della matrice A
	AB = (double**)calloc(w,sizeof(double*));
	for(i=0;i<w;i++)
		AB[i] = (double*)calloc(n,sizeof(double));

	// Allocazione della memoria per il vettore dei termini noti
	B = (double*)calloc(n,sizeof(double));

	// Input del vettore dei termini noti
	printf("Inserire il vettore dei termini noti: \n");
    for(i=0;i<n;i++)
    {
       	printf("B[%d]: ",i+1);
       	scanf("%lf",&B[i]);
   	}

	// Rappresento la matrice con il metodo di Band Storage
	BandStorage(A,AB,n,p,q);
	
	// Fattorizzazione LU della matrice AB
	BandLU(AB,n,p,q);
	
	// Calcolo il vettore dei termini noti
	BandFS(AB,B,n,p,q);

	// Risolvo il sistema
	BandBS(AB,B,n,p,q);	
   	
   	// Output del risultato
   	printf("La soluzione e':\n");
   	for(i=0;i<n;i++)
   	    printf("[%lf]\n",B[i]);
   	    
   	
	system("PAUSE");
	return 0;
}


/* Procedura che data una matrice A a banda, con banda inferiore p e banda */
/* superiore q, la rappresenta in una matrice di dimensioni (p+q+1)*n 	   */
/* secondo il metodo di Band Storage.	                  				   */
void BandStorage(double** A, double** AB, int n, int p, int q)
{
	int i,j;
	
	for(j=0;j<n;j++)
		for(i=Max(0,j-q);i<=Min(n-1,j+p);i++)
			AB[q+i-j][j] = A[i][j];
}	


/* Funzione che ritorna il massimo tra X e Y */
int Max(int X,int Y)
{
	if(X > Y)
		return  X;
	else
		return Y;
}


/* Funzione che ritorna il minimo tra X e Y */
int Min(int X,int Y)
{
	if(X < Y)
		return  X;
	else
		return Y;
}


/* Algoritmo che implementa la fattorizzazione LU particolarizzata per le    */
/* matrici a banda. Cio' permette di evitare inutili calcoli su elementi il  */
/* cui valore e' gia' noto per la struttura della matrice, con vantaggio     */
/* sul costo computazionale.				                    		     */
void BandLU(double** AB,int n, int p, int q)
{
    int i,j,k;
    
	int t,z;

    // Ciclo sui passi
    for(k=0;k<n-1;k++)
    {
        // Calcolo dei moltiplicatori
        for(i=k+1;i<=Min(k+p,n-1);i++)
            AB[q+i-k][k] = AB[q+i-k][k] / AB[q][k];
        	    
        // Modifica della matrice
        for(j=k+1;j<=Min(k+q,n-1);j++)
        {
            for(i=k+1;i<=Min(k+p,n-1);i++)
                AB[q+i-j][j] = AB[q+i-j][j] - (AB[q+i-k][k]*AB[q+k-j][j]);
        }
 
    }
}


/* Algoritmo di ForwardSubstitution particolarizzato al caso di matrici a banda.   */
/* In questo caso l'algoritmo procede nella maniera tradizionale, ma evitando di   */
/* eseguire operazioni su gli elementi nulli noti a priori per la struttura della  */
/* matrice.				                                     					   */
void BandFS(double** AB, double* B, int n, int p, int q)
{
    int i,j;
    
    for(j=0;j<n-1;j++)
        for(i=j+1;i<=Min(j+p,n-1);i++)
            B[i] = B[i] - (AB[q+i-j][j] * B[j]);
}


/* Algoritmo di BackSubstitution particolarizzato al caso di matrici a banda.      */
/* In questo caso l'algoritmo procede nella maniera tradizionale, ma evitando di   */
/* eseguire operazioni su gli elementi nulli noti a priori per la struttura della  */
/* matrice.			                                      						   */
void BandBS(double** AB, double* B, int n, int p, int q)
{
    int i,j;
    
    for(j=n-1;j>=1;j--)
    {
        B[j] = B[j] / AB[q][j];
        for(i=Max(j-q,0);i<=j-1;i++)
            B[i] = B[i] - (AB[q+i-j][j] * B[j]);
    }
    B[0] = B[0] / AB[q][0];
}
    
    
