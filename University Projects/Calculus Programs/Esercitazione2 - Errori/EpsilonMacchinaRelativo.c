/* 
    Creazione di un elemento di software che calcoli
    l'epsilon macchina relativo ad un numero fornito
    in input.
*/

#include <stdio.h>
#include <math.h>

// Prototipi delle function utilizzate
double EPS();
double RMIN();

int main()
{
    double x;           // Numero di cui calcolare l'epsilon macchina relativo
    double m;           // Mantissa di x
    int e;              // Esponente di x
    double epsrel;      // Epsilon macchina relativo da calcolare
        
    // Input della mantissa e dell'esponente di x
    printf("Inserire la mantissa di x: ");
    scanf("%lf",&m);
    printf("Inserire l'esponente di x: ");
    scanf("%d",&e);
    
    // Calcolo di x
    x = m * (pow(10,e));

    // Calcolo dell'epsilon macchina relativo ad x
    if(fabs(x) > (RMIN()/EPS()))
        epsrel = fabs(x) * EPS();
    else
        epsrel = RMIN();

    // Output del risultato
    printf("\n\nL'epsilon macchina relativo al numero X = %lf e': %e\n\n",x,epsrel);

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

