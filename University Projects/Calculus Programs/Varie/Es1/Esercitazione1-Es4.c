#include<stdio.h>
#include<math.h>


int main()
{
	double P;
	double tol = pow(10,-8);
	int k;
	double Err;
	double Pi;
	double t;
	
	
	Pi = 4*atan(1.);
	
	P=0;
	k = 0;
	
	do
	{	
		t = (int)pow(-1,k) * (1./(2*k+1));
		P = P + t;
		Err = fabs(Pi-4*P)/Pi;
		printf("N = %d\t%1.16f\t%e\n",k,4*P,Err);
		
		k++;
	}
	while(Err >= tol);
	
	printf("\nApprossimazione di pigreco dopo %d iterazioni: %1.16f\n",k,4*P);
	printf("Valore calcolato con 4*atan(1): %1.16f\n",Pi);
	printf("Errore relativo: %e\n\n",Err);

	system("PAUSE");
	return 0;
}
