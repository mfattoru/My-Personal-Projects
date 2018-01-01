#include <stdio.h>
#include <math.h>

// Prototipi delle funzioni
double F(double x);
int Trapez1(double a, double b, double Tol, int MaxVal, double* Int, double* Err, int* Nval);
double EPS();

int main()
{
    double a,b;                 // Estremi dell'intervallo
    double Tol;                 // Estremo inferiore dell'erroer
    int MaxVal;                 // Numero massimo di iterazioni
    double Int;                 // Stima dell'integrale
    double Err;                 // Stima dell'errore
    int Nval;                   // Numero di valutazioni
    int Iflag;                  // Indicatore di errore


    // Input dei parametri da passare a Trapez1
    printf("Inserire il primo estremo dell'intervallo: ");
    scanf("%lf",&a);
    printf("Inserire il secondo estremo dell'intervallo: ");
    scanf("%lf",&b);
    printf("Inserire la tolleranza desiderata: ");
    scanf("%lf",&Tol);
    printf("Inserire il numero massimo di valutazioni di funzione: ");
    scanf("%d",&MaxVal);

    if(Tol < EPS())
        Tol = EPS();

    // Chiamo la funzione Trapez1
    Iflag = Trapez1(a,b,Tol,MaxVal,&Int,&Err,&Nval);

    // Se Iflag = 0 stampo il risultato del calcolo
    if(!Iflag)
    {
        printf("\n\nStima dell'integrale: %1.16f\n",Int);
        printf("Stima dell'errore: %e\n",Err);
        printf("Numero di valutazioni: %d\n",Nval);
        printf("Iflag: %d\n",Iflag);
    }
    // Altrimenti c'e stato un errore
    else
        printf("\n\nTolleranza non raggiunta.\n");

    system("PAUSE");
    return 0;
}


/* Questa e' la funzione di cui si calcola l'integrale. Tale funzione va modificata 	*/
/* al variare della funzione integranda. Nel caso specifico e' la funzione e^x.		*/
double F(double x)
{
    return pow(x,3);
    //return exp(x);
}


/* Funzione che calcola l'integrale definito di F(X) nell'intervallo [a,b] attraverso 	*/
/* formula trapezoidale composita con strategia non adattativa. La funzione restituisce */
/* la stima dell'integrale e dell'errore ed il numero di valutazioni di funzione 	*/
/* effettuati.										*/
int Trapez1(double a, double b, double Tol, int MaxVal, double* Int, double* Err, int* Nval)
{
    double h;                   // Distanza tra i nodi
    double x;                   // Nodo attuale
    double oldint;              // Stima dell'integrale al passo precedente
    double sum;                 // Somma parziale
    int m;                      // Numero dei nodi per la formula trapezoidale composita
    int k;                      // Indice del ciclo for

    m = 2;
    h =(b-a)/m;
    x = (a+b)/m;

    oldint = h*(F(a)+F(b));

    *Int = oldint/2 + h*F(x);
    *Nval = 3;
    /*
    l'errore di discretizzazione viene calcolato come la differenza in valore assoluto
    della stima dell'integrale al passo precedente meno la stima dell'integrale al passo corrente,
    il tutto fratto 3
    */
    *Err = fabs(*Int - oldint)/3;

    // Ciclo principale con test sull'errore
    while(*Err > Tol && *Nval < MaxVal)
    {
    	// Incremento del numero di nodi
        m = m * 2;
        // Dimezzamento della distanza
        h = h/2;
        // Somma parziale
        sum = 0.;

        // Calcolo della formula trapezoidale composita su m punti mei
        for(k=1;k<=m;k=k+2)
        {
            x = a + k*h;
            sum = sum + F(x);
            (*Nval)++;
        }

        oldint = *Int;
        *Int = oldint/2 + h*sum;
	// Stima dell'errore
        *Err = fabs(*Int - oldint)/3;
    }

    // Se non e' stato raggiunto il numero massimo di iterazioni ritorno 0
    if(*Nval < MaxVal)
        return 0;
    // Altrimenti, se si e' usciti per la tolleranza, ritorno 1
    else
        return 1;
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

/* formule semplici non composite,x le composite bosogna suddividere i'intervallo di valutazione in + parti
in questo modo si ha una stima migliore dell'integrale.
raddoppiando il numero di intervalli si riduce di 4 volte l'errore di disctretizzazione
f(x) = equazione dell'integrale sostituedo il valore di x all'incognita
----------------------formula rettangolase semplice
a partenza integrale,b fine integrale (si chiamano NODI)


I[f]=(3 linee) A(R)=(ondato sopra)A(U)= f(a)(b-a)

----------------------formula del punto medio
I[f]=(3 linee) A(R)=(ondato sopra)A(V)= f(c)(b-a)
dove c=(a+b)/2

--------------------formula trapezoidale
I[f]=(3 linee) A(R)=(ondato sopra)A(T)= ((b-a)/2) * [f(a)+ f(b)]

---------------formula trapezoidale composita
la formula trapeziodale composita di tipo innestato migliora l'efficienza del software
perchè ad ogni passo è possibile riutilizzare tutti o quasi i valori ottenuti nei
passi precedenti


Entrambe le strategie (Adattiva globale e locale) presentano vantaggi e svantaggi,
anche se le routine pi`u efficienti attualmente esistenti sono basate sulla strategia globale.
Quest’ultima, infatti, a parit`a di tolleranza richiesta, utilizza generalmente un numero
minore di valutazioni della funzione integranda rispetto alla strategia locale. Inoltre, se
l’algoritmo termina per aver raggiunto il massimo numero di valutazioni della funzione
integranda, `e sempre disponibile una stima di I[f]. Diversamente, la strategia locale
produce una stima dell’integrale della funzione solo fino all’intervallo che ha esaminato
per ultimo procedendo dall’estremo inferiore dell’intervallo [a, b] verso quello superiore.
Tuttavia la strategia locale richiede un’occupazione minore di memoria per la pila,
in quanto, se essa contiene ad esempio 50 sottointervalli, l’intervallo in testa alla pila ha
ampiezza al pi`u 2−50(b−a) ≃ 10−15(b−a) che, per usuali valori di (b−a), `e un numero
minore della precisione relativa dei sistemi floating point utilizzati dalla maggior parte
dei calcolatori. In tal caso si ha che la pila non conterr`a mai pi`u di 50 intervalli. Per tale
motivo la strategia locale ha avuto un maggior successo rispetto alla strategia globale
negli anni ’70, quando la capacit`a limitata della memoria dei calcolatori costituiva un
serio vincolo alla dimensione dei programmi eseguibili. Con la tecnologia odierna tale
problema `e superato e la maggior parte degli algoritmi adattativi sono basati sulla
strategia globale.

*/

