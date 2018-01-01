/*
    Elemento di software che implementa il calcolo del valore approssimato
    del numero di nepero secondo la definizione:
                            e = lim (1+1/n)^n
    Sara' calcolato il valore di e per n = 10^k con k=1..20
*/

#include <stdio.h>
#include <math.h>

double EPS();


int main()
{
	int n;
	double E;
	int i;
	double N1,nep;
	double Err;

    // Valore reale del numero di nepero
	E = exp(1);

	n=1;
	i=0;
	
	do
	{
		i++;
		n=pow(10,i);
		N1 = 1./n;

		if(N1 >= EPS())
		{
			N1 = 1. + N1;		
			nep = pow(N1,n);
			Err = fabs(E-nep)/E;
			printf("Passo %d:\tNumero calcolato:%1.16f\tErrore Relativo:%e\n",i,nep,Err);
		}
		else
		{
			printf("1/n e' minore dell'epsilon macchina.\n");
			printf("Il numero di nepero e': %1.16f\n",nep);
		}
	}while(i < 21 && N1 >= EPS());

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


