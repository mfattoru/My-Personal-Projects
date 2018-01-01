/*
	Implementazione di un elemento di software che implementi
	il metodo di Leibniz per il calcolo di pi greco.
    A differenza del metodo di Viete, converge molto lentamente
    quindi per una buona approssimazione inserire n grande (+ di 1000)
*/

#include <stdio.h>
#include <math.h>

double EPS();

int main()
{
	/* Dichiarazione delle variabili */
	int n, passo, esp;
	double q, i, Pi, err_rel, tol, err_tronc;
    FILE *fp;

	/* Inserimento dell'ordine di sviluppo in serie di Taylor di arctg(x) */
	printf("\nInserire l'ordine di sviluppo della serie di Taylor di arctg(x): ");
	scanf("%d",&n);

	/* Richiesta del valore esp tale che 10^esp sia la tolleranza */
	printf("\nInserire un valore X tale che 10^X sia la tolleranza: ");
	scanf("%d",&esp);

	/* Calcolo della tolleranza */
	tol = pow(10,esp);

   /* Se la tolleranza e' minore dell'epsilon m,acchina, la tolleranza verra' impostata ad eps */
	if(tol < EPS())
		tol = EPS();


	/* Calcolo di Pi con la funzione atan() del compilatore */
	Pi = 4*atan(1.);

	/* Inizializzazione delle variabili */
	q = 1.;
	passo = 2;
	err_rel = 1.;

	/* Ciclo per il calcolo di Pi. Il ciclo si arresta quando si arriva al numero di
	   passi scelto oppure quando l'errore relativo tra il valore calcolato e il valore
	   di Pi diventa piu' piccolo della tolleranza scelta. */
    if( (fp = fopen( "Leibniz.txt", "w" )) != NULL ){
        fprintf(fp,"PASSO\tP-GRECO\t\t\tERR-RELAT\n\n");
        while(passo <= n && err_rel > tol){
            i = pow(-1,passo-1)/(2*passo-1);
            q =  q + i;

            /* Calcolo dell'errore relativo */
            err_rel = fabs(Pi-4*q)/Pi;
            //------------------STAMPA RISULTATI INTERMEDI A VIDEO---------------------
            printf("N = %d\t%1.16f\t%e\n",passo,4*q,err_rel);
            //------------------STAMPA RISULTATI INTERMEDI SU FILE-----------------------
            fprintf(fp,"N = %d\t%1.16f\t%e\n",passo,4*q,err_rel);
            //---------------------------------------------------------------------------
            passo++;
        }

        /* Valore calcolato di pi greco */
        q = 4*q;

        /* Calcolo dell'errore di troncamento analitico secondo la formula 1/2n */
        err_tronc = pow(2*n,-1);

        //---------------------STAMPA RISULTATI FINALI A VIDEO----------------------------
        printf("\n\nValore di PiGreco calcolato mediante il metodo di Leibniz: %1.16f\n",q);
        printf("Valore di PiGreco calcolato con 4*atan(1): %1.16f\n",Pi);
        printf("Errore relativo: %e\n",err_rel);
        //printf("Errore di troncamento analitico: %e\n\n",err_tronc);
        printf("Errore di troncamento analitico: %3.16f\n\n",err_tronc);
        //-----------------------------------------------------------------------------------


        //-----------------------STAMPA RISULTATI FINALI SU FILE----------------------------
        fprintf(fp,"\n\nValore di PiGreco calcolato mediante il metodo di Leibniz: %1.16f\n",q);
        fprintf(fp,"Valore di PiGreco calcolato con 4*atan(1): %1.16f\n",Pi);
        fprintf(fp,"Errore relativo: %e\n",err_rel);
        fprintf(fp,"Errore di troncamento analitico: %e\n\n",err_tronc);
        //-----------------------------------------------------------------------------------

    }
	system("PAUSE");
	return 0;
}


double EPS()
{
    double eps;         // Epsilon Macchina
    double u1,u2;       // Variabili Locali

    // Inizializzazione delle variabili
    u1 = 1.;

    do
    {
        eps = u1;
        u1 = u1 / 2.;
        u2 = u1 + 1.;
    }
    while(u2 != 1.);

    return eps;
}

/*--------------------------------------------------------------------------------------------------
il valore di pgreco è ottenuto dallo sviluppo in serie di mc laurin della funzione arctg(x)

Nel metodo di Leibniz, che utilizza uno sviluppo in serie, l'errore round-off cresce linearmente
con il numero degli addendi della serie; questo metodo è quindi stabile. Tuttavia, a causa
della lenta velocità di convergenza della sua formula, si ottengono risultati accurati solo per
n molto grande.

l'errore di troncamento analitico è |e_n| = O((2n)^-1)

il metodo converge ad O(n)
----------------------------------------------------------------------------------------------------*/
