/*
    Elemento di software che dati gli estremi di un intervallo ed un 
    numero N di punti, genera N punti tra di loro equidistanziati, 
    usando due diverse formule.
*/

#include <stdio.h>
#include <math.h>

int main()
{
	int k,n;
	double a,b,h,X[1000],Y[1000];

	printf("\nFormula 1: x0 = a  x(k) = x(k-1) + h    k=0..n\n");
	printf("Formula 2: X(k) = a + h*k   k=0...n\n\n\n");

	printf("Inserire gli estremi a e b\n");
	printf("A: ");
	scanf("%lf",&a);
	printf("B: ");
	scanf("%lf",&b);

	printf("Inserire il numero dei punti desiderati: ");
	scanf("%d",&n);
	
	X[0] = a;
	Y[0] = a;
	h = (b-a)/n;

	printf("Punto %d\tFormula 1: %1.16f\tFormula 2: %1.16f\n",1,X[0],Y[0]);	

	for(k=1;k<n;k++)
	{
		X[k] = X[k-1] + h;
		Y[k] = Y[0] + h*k;
		printf("Punto %d\tFormula 1: %1.16f\tFormula 2: %1.16f\n",k+1,X[k],Y[k]);		
	}




	system("PAUSE");
	return 0;
}

