/*
	Implementazione di un elemento di software che implementi
	il metodo di Viete per il calcolo di pi greco.
*/

#include <stdio.h>
#include <math.h>

double EPS();

int main()
{
	/* Dichiarazione delle variabili */
	int n, passo, esp;
	double p, c, Pi, err_rel, tol, err_tronc;
    FILE *fp;

	/* Richiesta del valore N tale che 2^N sia il numero dei lati del poligono */
	printf("\nInserire un valore N tale che 2^N sia il numero dei lati del poligono: ");
	scanf("%d",&n);

	/* Richiesta del valore esp tale che 10^esp sia la tolleranza */
	//printf("\nInserire un valore X tale che 10^X sia la tolleranza: ");
	//scanf("%d",&esp);

	/* Calcolo della tolleranza */
	//tol = pow(10,esp);

	/* Se la tolleranza e' minore dell'epsilon macchina, la tolleranza verra' impostata ad eps */
	//if(tol < EPS())
		//tol = EPS();

	/* Calcolo di Pi con la funzione atan() del compilatore */
	Pi = 4*atan(1.);

	/* Inizializzazione delle variabili */
	p = 2*sqrt(2);;   //2 radical 2
	c = sqrt(2)/2;    //radice di 1/2
	passo = 3;
	err_rel = 1.;

    /* Ciclo per il calcolo di Pi. Il ciclo si arresta quando si arriva al numero di
	   passi scelto oppure quando l'errore relativo tra il valore calcolato e il valore
	   di Pi diventa piu' piccolo della tolleranza scelta. */
    if( (fp = fopen( "Viete.txt", "w" )) != NULL ){
        fprintf(fp,"PASSO\tP-GRECO\t\t\tERR-RELAT\n\n");
        while(passo <= n /*&& err_rel > tol*/){
            c = sqrt((1+c)/2);
            p = p / c;
            //il risultato è uguale a 2 radical 2 diviso c
            /* Calcolo dell'errore relativo */
            err_rel = fabs(Pi-p)/Pi;
            //------------------STAMPA RISULTATI INTERMEDI A VIDEO---------------------
            printf("N = %d\t%1.16f\t%e\n",passo,p,err_rel);
            //------------------STAMPA RISULTATI INTERMEDI SU FILE---------------------
            fprintf(fp,"N = %d\t%1.16f\t%e\n",passo,p,err_rel);
            //-------------------------------------------------------------------------
            passo++;
        }

        /* Calcolo dell'errore di troncamento analitico secondo la formula (1/4)^n */
        err_tronc = 1/pow(4,passo-1);

        //---------------------STAMPA RISULTATI FINALI A VIDEO----------------------------
        printf("\n\nValore di PiGreco calcolato mediante il metodo di Viete: %1.16f\n",p);
        printf("Valore di PiGreco calcolato con 4*atan(1): %1.16f\n",Pi);
        printf("Errore relativo: %e\n",err_rel);
        //printf("Errore di troncamento analitico: %e\n\n",err_tronc);
        printf("Errore di troncamento analitico: %3.16f\n\n",err_tronc);
        //--------------------------------------------------------------------------------

        //---------------------STAMPA RISULTATI FINALI SU FILE----------------------------
        fprintf(fp,"\n\nValore di PiGreco calcolato mediante il metodo di Viete: %1.16f\n",p);
        fprintf(fp,"Valore di PiGreco calcolato con 4*atan(1): %1.16f\n",Pi);
        fprintf(fp,"Errore relativo: %e\n",err_rel);
        fprintf(fp,"Errore di troncamento analitico: %e\n\n",err_tronc);
        //--------------------------------------------------------------------------------
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

/*-------------------------------------------------------------------------------------------------
Il metodo di Viete è stabile, in quanto il fattore di ampliificazione dell'errore di round-off nella
formula di ricorrenza del passo i-esimo è limitato. Questo metodo è computazionalmente più
vantaggioso di quello di Leibniz, a causa della lenta convergenza della formula di Leibniz.

fattore di amplificazione: p_i+1= p_i / (c_i+1)

utilizzando lo sviluppo in serie della funzione seno di taylor calcolato in pgreco/2^n si ha che
l'errore analitico commesso ad ogni passo n è uguale a O(1/4^n)
---------------------------------------------------------------------------------------------------*/

