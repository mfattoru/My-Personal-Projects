/*
    Creazione di un elemento di software che calcoli
    il minimo numero rappresentabile del sistema. 
*/

#include <stdio.h>

int main()
{
    double rmin;        // Minimo Numero Rappresentabile
    double r;           // Variabile locale
 
    // Inizializzazione delle variabili
    r = 1.;
 
    // Ciclo di calcolo di rmin
    do
    {
        rmin = r;
        r = r / 2.;
 	    printf("%e\n",rmin);
    }
    while(r != 0);
 
    // Output del risultato
    printf("\n\nIl minimo numero rappresentabile e': %e\n\n",rmin);
 
    system("PAUSE");
    return 0;
}




