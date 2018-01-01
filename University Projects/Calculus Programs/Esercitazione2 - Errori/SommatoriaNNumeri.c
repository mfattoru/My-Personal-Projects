/*
    Implementazione di un elemento di software che
    calcoli la sommatoria 1/2^N, che usa il criterio
    di arresto naturale.
*/

#include <stdio.h>
#include <math.h>

// Prototipi delle function utilizzate
double EPS();
double RMIN();
double EPSREL(double x);


int main()
{
    int N;                // Numero di termini da sommare
    int i;                // Indice del ciclo di calcolo
    double somma;         // Valore della sommatoria
    double y;	          // Termine da sommare

    // Input del numero di termini da sommare
    printf("Inserire il numero di termini da sommare: ");
    scanf("%d",&N);

    // Inizializzazione delle variabili    
    i = 0;
    somma = 0.;
    
    // Ciclo di calcolo
    do
    {
        // Calcolo dell'i-mo termine della sommatoria
        y = (1/(pow(2,i)));     
        somma = somma + y;
        printf("%d.%1.16f\t%e\n",i+1,somma,somma);
        i++;
    }
    while(y >= EPSREL(somma) && i<=N);      // Criterio di arresto naturale
	    
    // Output del risultato
    printf("\nValore della somma di 1/2^n dopo %d iterazioni: %e\n\n",i,somma);
    
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


double RMIN()
{
    double rmin;        // Minimo Numero Rappresentabile
    double r;           // Variabile locale
    
    // Inizializzazione delle variabili
    r = 1.;
    
    do
    {
        rmin = r;
        r = r / 2.;
    }
    while(r != 0);
    
    return rmin;
}


double EPSREL(double x)
{
    double epsrel;      // Epsilon macchina relativo da calcolare
    
    // Calcolo dell'epsilon macchina relativo ad x
    if(fabs(x) > (RMIN()/EPS()))
        epsrel = fabs(x) * EPS();
    else
        epsrel = RMIN();
        
    return epsrel;
}
