/*
    Elemento di software che calcola l'approssimazione di una funzione
    utilizzando la seguente approssimazione:
        f'(x) = [f(x + h) - f(x)]/h
        
    In questo contesto verrà calcolata l'approssimazione della funzione
    ln(x).
*/

#include <stdio.h>
#include <math.h>

void Derivata(double, double, double*, double*);

int main()
{
	int n;
	double x,h,d1,d2,k;
	
	printf("\nCalcolo della derivata della funzione logaritmo: Formula 1: (f(x+h)-f(x))\\h\n");
	printf("Calcolo della derivata della funzione logaritmo: Formula 2: (f(x+h)-f(x-h))\\2h\n\n");

	printf("Inserire il numero di passi: ");
	scanf("%d",&n);
	printf("Inserire il punto di valutazione: ");
	scanf("%lf",&x);
	
	k=2;
	do
	{
		h = 1./k;
		Derivata(x,h,&d1,&d2);
		printf("Incremento h=%lf\tFormula 1: %lf\tFormula 2: %lf\n",h,d1,d2);
		k=2*k;	
		
	}while(k<=n);

	system("PAUSE");
	return 0;
}

void Derivata(double x, double h, double* d1, double* d2)
{
	*d1=(log(x+h)-log(x))/h;
	*d2=(log(x+h)-log(x-h))/(2*h);
}

