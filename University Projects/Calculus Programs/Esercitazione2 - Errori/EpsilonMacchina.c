/* 
    Creazione di un elemento di software che calcoli
    l'epsilon macchina del sistema.
*/

#include <stdio.h>

int main()
{
    double eps;         // Epsilon Macchina
    double u1,u2;       // Variabili Locali
    
    // Inizializzazione delle variabili
    u1 = 1.;
    
    // Ciclo di calcolo dell'epsilon macchina
    do
    {
        eps = u1;
        u1 = u1 / 2.;
        u2 = u1 + 1.;
        printf("%1.16f\t%e\n",eps,eps);
    }
    while(u2 != 1.);
    
    // Output del risultato
    printf("\n\nL'epsilon macchina e': %e\n\n",eps);
    
    system("PAUSE");
    return 0;
}
    
    


