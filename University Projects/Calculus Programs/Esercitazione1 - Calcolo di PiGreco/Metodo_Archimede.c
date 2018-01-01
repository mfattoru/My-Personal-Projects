/*
	Implementazione di un elemento di software che implementi
	il metodo di Archimede per il calcolo di pi greco.
*/

#include<stdio.h>
#include<math.h>

double EPS();

int main()
{
	/* Dichiarazione delle variabili */
	int n, passo, esp;
	double A=1., b, s, err_rel, Pi, tol, err_tronc;
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

	/* Inizializzazione delle variabili */
	b = 2.;
	s = 1.;
	passo = 3;
	err_rel = 1.;

	/* Calcolo di Pi con la funzione atan() del compilatore */
	Pi = 4*atan(1.);

	/* Ciclo di calcolo di Pi */
	printf("\nCalcolo dell'approssimazione di pigreco:\n\n");
	/* Ciclo fin quando non raggiungo il numero di passi scelto oppure fin quando
	   l'errore relativo tra il valore calcolato e Pi diventa piu' piccolo della
	   tolleranza inserita in input oppure quando il valore calcolato si annulla */
    if( (fp = fopen( "Archimede.txt", "w" )) != NULL ){
        fprintf(fp,"PASSO\tP-GRECO\t\t\tERR-RELAT\n\n");
        while(passo <= n /*&& err_rel > tol */ && A > 0)
        {
            b = 2*b;
            s = sqrt((1-sqrt(1-s*s))/2);
            A = b*s;

            /* Calcolo dell'errore relativo */
            err_rel = fabs(Pi-A)/Pi;
            //------------------STAMPA RISULTATI INTERMEDI A VIDEO---------------------
            printf("N = %d\t%1.16f\t%e\n",passo,A,err_rel);
            //------------------STAMPA RISULTATI INTERMEDI SU FILE-----------------------
            fprintf(fp,"N = %d\t%1.16f\t%e\n",passo,A,err_rel);
            //---------------------------------------------------------------------------
            passo++;
        }

        /* Calcolo dell'errore di troncamento analitico secondo la formula (1/4)^n */
        err_tronc = 1/pow(4,passo-1);

        //---------------------STAMPA RISULTATI FINALI A VIDEO----------------------------
        printf("\n\nValore di PiGreco calcolato mediante il metodo di Archimede: %1.16f\n",A);
        printf("Valore di PiGreco calcolato con 4*atan(1): %1.16f\n",Pi);
        printf("Errore relativo: %e\n",err_rel);
        //printf("Errore di troncamento analitico: %e\n\n",err_tronc);
        printf("Errore di troncamento analitico: %3.16f\n\n",err_tronc);
        //-------------------------------------------------------------------------------------

        //-----------------------STAMPA RISULTATI FINALI SU FILE----------------------------
        fprintf(fp,"\n\nValore di PiGreco calcolato mediante il metodo di Archimede: %1.16f\n",A);
        fprintf(fp,"Valore di PiGreco calcolato con 4*atan(1): %1.16f\n",Pi);
        fprintf(fp,"Errore relativo: %e\n",err_rel);
        fprintf(fp,"Errore di troncamento analitico: %e\n\n",err_tronc);
        //-----------------------------------------------------------------------------------
    }
    else{

        printf("\nIMPOSSIBILE APRIRE IL FILE!!\n");
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

/*----------------------------------------------------
Il metodo di Archimede è instabile, poiche al passo i-esimo si moltiplica il termine precedente
per u (mu) = 2^(i-2) che è, quindi, anche il fattore di amplificazione dell'errore di round-off.
----------------------------------------------------*/
