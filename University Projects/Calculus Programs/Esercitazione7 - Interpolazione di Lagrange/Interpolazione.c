/*
	Costruzione di un elemento di softwate matematico che costruisca e valuti
	il polinomio interpolante di Lagrange espresso nella formula di Newton.
	Il software prevede anche la possibilita' di aggiungere punti di valutazione
	e nuovi nodi.
*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Prototipi delle function utilizzate
int NodiDistinti(double*, int);
void DifferenzeDivise(double*, double*, int);
double HornerNewton(double*, double, double*, int);
int AggiungiNodi(double*, double*, int, int);
double* AggiungiAVettore(double*, int, int);

int main()
{
    double* X;                 // Ascisse dei nodi di interpolazione
    double* Y;                 // Ordinate dei nodi di interpolazione
    int n;                     // Numero di punti
    int i;                     // Indice del ciclo
    double P;                  // Punto di valutazione
    double Val;                // Valutazione del polinomio in P
    int Scelta;                // Variabile di scelta del menu
    int num;                   // Numero di nodi da aggiungere
    int Esito=0;               // Esito dell'inserimento dei nodi
    FILE *fp;
    fp=fopen("interpolare.txt","w");

    // Input del numero di nodi
    printf("Inserire il numero di nodi: ");
    scanf("%d",&n);

    // Allocazione della memoria per i vettori X e Y
    X = (double*)calloc(n,sizeof(double));
    Y = (double*)calloc(n,sizeof(double));

    // Input degli n nodi
    for(i=0;i<n;i++)
    {
	printf("Inserire X[%d]: ",i+1);
	scanf("%lf",&X[i]);
	printf("Inserire Y[%d]: ",i+1);
	scanf("%lf",&Y[i]);
    }

    // Se i nodi non sono distinti, restituisco errore
    if(!NodiDistinti(X,n))
	printf("Impossibile calcolare il polinomio interpolante.\n\n");
    else
    {
        // Calcolo i coefficienti del polinomio interpolante di Lagrange, restituiti nel vettore Y
	DifferenzeDivise(X,Y,n);

	do
	{
		if(Esito != -1)
		{
			printf("1. Inserimento punto di valutazione\n");
			printf("2. Aggiunta di nodi\n");
			printf("0. Uscita\n");
			scanf("%d",&Scelta);

			switch(Scelta)
			{
				case 1:
					/*printf("Inserire il punto di valutazione: ");
					scanf("%lf",&P);
					*/
					for(P=1;P<=43;P++){
                        Val = HornerNewton(X,P,Y,n);
                        printf("La valutazione del polinomio in %lf e' : %lf \n",P,Val);
                        fprintf(fp,"La valutazione del polinomio in %lf e' : %lf \n",P,Val);
                    }
                    fclose(fp);
					break;
				case 2:
					printf("Inserire il numero di nodi da aggiungere: ");
					scanf("%d",&num);
					X = AggiungiAVettore(X,n,num);
					Y = AggiungiAVettore(Y,n,num);
					Esito = AggiungiNodi(X,Y,n,num);
					n = n+num;
					break;

			}
		}
		else
		{
			Scelta = 0;
			printf("\nErrore. I nodi inseriti non sono distinti.\n\n");
		}
	}
	while(Scelta != 0);
    }

    // Deallocazione dei vettori utilizzati
    free(X);
    free(Y);

    system("PAUSE");
    return 0;
}


/* Funzione che restituisce 1 se le ascisse degli n nodi di interpolazione    */
/* sono tra di loro distinti, in modo da evitare divisioni per 0. Restituisce */
/* 0 altrimenti.                                                              */
int NodiDistinti(double* X, int n)
{
	int Ritorno=1;
	int i=0;
	int j;

	while(i<n && Ritorno == 1)
	{
		j=i+1;
		while(j<n && Ritorno == 1)
		{
			if(X[i] == X[j])
				Ritorno = 0;
			j++;
		}
		i++;
	}

	return Ritorno;
}


/* Calcolo dei coefficienti del polinomio interpolante di Lagrange, espresso  */
/* nella formula di Newton. I coefficienti del polinomio saranno memorizzati  */
/* nel vettore delle ordinate y secondo lo schema di memorizzazione di Neville*/
void DifferenzeDivise(double* x, double* y, int n)
{
     int i, j;

    // Ciclo sull'ordine delle differenze divise
     for (j=1;j<n;j++)
     {
         // Calcolo delle differenze divise
         for (i=n-1;i>=j;i--)
             y[i]=(y[i]-y[i-1])/(x[i]-x[i-j]);
     }
}


/* Algoritmo di Horner per la valutazione del polinomio interpolante di       */
/* Lagrange, espresso nella formula di Newton avente vettore dei coefficienti */
/* A e vettore delle ascisse X nel punto P.                                   */
double HornerNewton(double* X, double P, double* A, int n)
{
	double val;
	int i;

	val = A[n-1];

	for(i=n-2;i>=0;i--)
		val = (val*(P-X[i])) + A[i];

	return val;
}


/* Funzione che riceve in input un vettore V di dimensione n e restituisce un */
/* vettore di dimensione n+num avente ai primi n posti gli stessi elementi che*/
/* erano presenti nel vettore V.                                              */
double* AggiungiAVettore(double* V, int n, int num)
{
	double* T;
	int i;

        // Alloco il vettore della nuova dimensione
	T = (double*)calloc((n+num),sizeof(double));

        // Copio gli elementi di V nei primi n posti di T
	for(i=0;i<n;i++)
		T[i] = V[i];

        // Dealloco il vecchio vettore
	free(V);

	return T;
}


/* Funzione che prende in input i vettori delle ascisse e delle ordinate,     */
/* gia' ampliati alla dimensione n+num, e aggiunge a tali vettori num nodi.   */
/* Dopo aver controllato che i nodi sono distinti, calcola differenze divise  */
/* necessarie a creare il polinomio interpolante di grado n+num-1 a partire da*/
/* quello calcolato in precedenza. In caso di nodi coincidenti, restituisce un*/
/* indicatore di errore.                                                      */
int AggiungiNodi(double* X, double* Y, int n, int num)
{
	int i,j;
	int Esito=0;

    // Input dei nodi
	for(i=n;i<(n+num);i++)
	{
		printf("Inserire X[%d]: ",i+1);
		scanf("%lf",&X[i]);
		printf("Inserire Y[%d]: ",i+1);
		scanf("%lf",&Y[i]);
	}

    // Se i nodi sono distinti, calcolo le differenze divise
	if(NodiDistinti(X,n+num))
	{
		for(j=0;j<num;j++)
			for(i=0;i<(n+j);i++)
				Y[n+j] = (Y[n+j] - Y[i] ) / (X[n+j] - X[i]);
	}
	else
		Esito = -1;

	return Esito;
}

/*
Tn=O(n^2)
*/
