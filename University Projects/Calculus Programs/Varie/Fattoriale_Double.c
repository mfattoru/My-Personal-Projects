#include <stdio.h>

// Limite massimo 171!

int main()
{
    int n;
    double fatt;
    int i;

    printf("Inserire il numero di cui si vuole calcolare il fattoriale: ");
    scanf("%d",&n);

    fatt = 1.;
    i = 1;

    do
    {
        fatt *= i;
        i++;
    }while(fatt > 0 && i < n);

    printf("Il valore di %d! e': %e\n\n",n,fatt);


    system("PAUSE");
    return 0;
}
