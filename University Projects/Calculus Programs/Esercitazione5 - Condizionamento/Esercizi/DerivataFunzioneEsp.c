/*
    Elemento di software che calcola l'approssimazione della funzione:
            f(x) = (e^x - 1)/x
    Applicando il teorema de L'Hospital si dimostra che lim f(x) = 1 (x->0)
    Il programma dimostra tale valore per x = 10^(-k) con k=1..16
*/

#include <stdio.h>
#include <math.h>

int main()
{
	int i,n;
	double N1,nep,nep1,aus,e,err1,err2;

	printf("Limite 1: x->0 (EXP(x)-1)/X\n");
	printf("Limite 2: x->0 (EXP(x)-1)/log(EXP(X))\n\n\n");

	i=0;
	do
	{
		i++;
		n=pow(10,i);
		N1 = 1./n;
		aus = exp(N1);
		nep1 = aus -1;

		if(nep1 != 0.)
		{
			e = nep1/log(aus);
			aus = nep1/N1;
			err1 = fabs(1-aus);
			err2 = fabs(1-e);
			printf("Passo %d\nLimite 1: %1.16f\tErrore:%e\nLimite 2: %1.16f\tErrore:%e\n\n",i,aus,err1,e,err2);	
		}
		else
			printf("Passo %d\nLimite 1 = Limite 2 = 0\n\n",i);
	
	} while(i < 16 && nep1 != 0);

	system("PAUSE");
	return 0;
}
