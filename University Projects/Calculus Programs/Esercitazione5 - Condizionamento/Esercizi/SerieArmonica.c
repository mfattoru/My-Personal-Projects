/*
    Elemento di software che esegue il calcolo della serie armonica (1/n).
*/

#include <stdio.h>

double EPS();

int main()
{
	int nmax,i,flag;
	double add,n,sum,epsilon,sumold;
	
	printf("Calcolo della serie armonica: n->inf S(1/n)\n");

	printf("Inserire il numero massimo di iterazioni: ");
	scanf("%d",&nmax);

	n=1.;
	add = n;
	i=0;
	flag=0;
	
	sum=1.0;
	
	epsilon = EPS();
	
	do
	{
		i++;
		n=n+1.0;
		add=1.0/n;
		
		if(add >= (sum*epsilon))
		{
			sumold = sum;
			sum = sum + add;
			
			printf("Iterazione: %d\tApprossimazione: %lf\n",i,sum);
		}
		else
		{
			printf("1/n e' minore dell'epsilon macchina relativo di %lf\n",sumold);
			printf("Approssimazione della serie: %lf\n",sum);
			flag=1;
		}
	}while(i < nmax && !flag);

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
