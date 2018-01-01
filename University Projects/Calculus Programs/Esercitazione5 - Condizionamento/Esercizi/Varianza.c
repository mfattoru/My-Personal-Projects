/*
    Elemento di software per il calcolo della varianza di una successione
    finita Xi.
*/

#include <stdio.h>
#include <math.h>

int main()
{
	int n,i;
	double x[100],med;
	double sigma,sigma1;

	printf("Calcolo della varianza\n");
	printf("Formula 1: 1/(n-1)[sum{1=1,n} (x(i)-med)^2]\n");
	printf("Formula 2: 1/(n-1)[sum{1=1,n} x(i)^2- 1/n(sum{i=1,n}x(i))^2]\n");
	
	printf("Inserire la lunghezza del vettore: ");
	scanf("%d",&n);

	printf("Inserire le componenti del vettore\n");
	for(i=0;i<n;i++)
	{
		printf("X[%d]: ",i+1);
		scanf("%lf",&x[i]);
	}
	
	med = 0;
	for(i=0;i<n;i++)
	   med += x[i];
	   
	med = med/n;
	
	sigma = 0;
	sigma1 = 0;
	
	for(i=0;i<n;i++)
	{
        sigma = sigma + pow((x[i] - med),2);
        sigma1 = sigma1 + pow(x[i],2);
    }
    
    sigma = (1./(n-1))*sigma;
    sigma1 = (1./(n-1))*(sigma1 - n*(pow(med,2)));
    
    printf("\nMedia: %lf\n",med);
    printf("Varianza con la formula 1: %lf\n",sigma);
    printf("Varianza con la formula 2: %lf\n\n",sigma1);

    system("PAUSE");
    return 0;
}
