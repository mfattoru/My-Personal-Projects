#include <stdio.h>

// Limite massimo 17!

int main()
{
    int n;
    int fatt;
    int i;
    
    printf("Inserire il numero di cui si vuole calcolare il fattoriale: ");
    scanf("%d",&n);
    
    fatt = 1;
    i = 1;
    
    do
    {
        fatt *= i;
        i++;
        if(fatt < 0)
            printf("Il valore del fattoriale ha causato un overflow.\n");
    }while(fatt > 0 && i < n);
       
    printf("Il valore di %d! e': %d\n\n",n,fatt);
    
    
    system("PAUSE");
    return 0;
}
