#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Definizione del tipo di dato stack
typedef struct nodo {
    double a;
    double b;
    double val;
    struct nodo* next;
}NODO;

// Funzioni per la gestione dello stack
int IsStackEmpty(NODO* Head);
NODO* Push(NODO* Head, double a, double b, double val);
NODO* Pop(NODO* Head, double* a, double* b, double* val);

// Funzioni per il calcolo dell'integrale
int StrategiaAdattativaLocale(double a, double b, double Tol, int MaxVal, double* Int, double* Err, int* Nval);
void Quadra(double c, double d, double* Q);
double F(double x);
double EPS();


int main()
{
    int Iflag;				// Indicatore di errore
    double a;				// Estremo superiore dell'intervallo
    double b;				// Estremo inferiore dell'intervallo
    double Tol;			// Tolleranza sull'errore
    double Int;			// Stima dell'integrale
    double Err;			// Stima dell'errore
    int MaxVal;			// Numero massimo di valutazioni
    int Nval;

    // Input dei valori a passare a StrategiaAdattativaLocale
    printf("Inserire il primo estremo dell'intervallo: ");
    scanf("%lf",&a);
    printf("Inserire il secondo estremo dell'intervallo: ");
    scanf("%lf",&b);
    printf("Inserire la tolleranza desiderata: ");
    scanf("%lf",&Tol);
    printf("Inserire il numero massimo di valutazioni di funzione: ");
    scanf("%d",&MaxVal);

    // Se Tol e' negativa oppure il numero di valutazioni e' minore di 3, setto Iflag a 2
    if(Tol < 0 || MaxVal < 3)
        Iflag = 2;
    else
    {
        if(Tol < EPS())
            Tol = EPS();
        // Altrimenti richiamo la funzione
        Iflag = StrategiaAdattativaLocale(a,b,Tol,MaxVal,&Int,&Err,&Nval);
    }
    // Se Iflag vale 0, stampo l'output
    if(Iflag == 0)
    {
        printf("\n\nStima dell'integrale: %1.16f\n",Int);
        printf("Stima dell'errore: %e\n",Err);
        printf("Numero di valutazioni: %d\n",Nval);
        printf("Iflag: %d\n",Iflag);
    }
    else if(Iflag == 1)
    // Se Iflag vale 1 restituisco errore sul numero di valutazioni
        printf("Errore. Non e' stato raggiunto il numero di valutazioni richiesto\n\n");
    else
    // Altrimenti restituisco errore sull'input
        printf("Errore di input. La tolleranza immessa e' negativa oppure il numero di valutazioni e' minore di 3.\n\n");

    system("PAUSE");
    return 0;
}


/* Funzione che calcola l'integrale definito di F(X) nell'intervallo [a,b] usando una	*/
/* strategia adattativa locale. La funzione restituisce un intero indicante il successo	*/
/* dell'operazione di calcolo e una stima dell'integrale e dell'errore.			*/
int StrategiaAdattativaLocale(double a, double b, double Tol, int MaxVal, double* Int, double* Err, int* nval)
{
    int Iflag;				// Indicatore di errore
    double Q1;				// stima dell'integrale secondo la formula trapezoidale
    double Q2;				// stima dell'integrale secondo la formula trapezoidale
    double Locerr;			// errore di discretizzazione locale
    double inf;			// estremo inferiore dell'intervallo corrente
    double sup;			// estremo superiore dell'intervallo corrente
    double res;			// stima corrente dell'integrale definito
    double newres;			// stima dell'integrale
    NODO* Stack;			// Struttura dati per memorizzare gli intervalli

    // Alloco e inizializzo la struttura dati stack
    Stack = (NODO*)malloc(sizeof(NODO));
    Stack = NULL;

    // Inizializzo l'integrale e l'errore
    *Int = 0;
    *Err = 0;

    // Chiamo la formula trapezoidale sull'intervallo [a,b]
    Quadra(a,b,&Q1);

    // Setto il numero di valutazioni e inserisco i valori nello stack
    *nval = 3;
    Stack = Push(Stack,a,b,Q1);

    do
    {
    	// Estraggo un intervallo
        Stack = Pop(Stack,&inf,&sup,&res);

     	// Calcolo la formula trapezoidale nei due sottointervalli
        Quadra(inf,(inf + sup)/2,&Q1);
        Quadra((inf + sup)/2,sup,&Q2);

	// Calcolo il valore attuale dell'integrale
        newres = Q1 + Q2;

        // Calcolo il valore dell'errore locale
        Locerr = fabs(res - newres)/3;

        // Se l'errore locale e' minore della tolleranza locale, aggiorno Int e Err
        if(Locerr < Tol*(sup - inf)/(b-a))
        {
            *Int = *Int + newres;
            *Err = *Err + Locerr;
        }
        // Altrimenti inserisco gli intervalli nello stack e continuo a suddividere
        else
        {
            Stack = Push(Stack,(inf + sup)/2,sup,Q2);
            Stack = Push(Stack,inf,(inf + sup)/2,Q1);
        }

        // Aggiorno il numero di valutazioni di funzione
        *nval = *nval + 6;

    }while(!IsStackEmpty(Stack) && *nval < MaxVal);
    // Ciclo fino all'esaurimento degli intervalli o al raggiungimento di MaxVal

    // Se non e' stato raggiunto il numero massimo di iterazioni restituisco 0
    if(*nval < MaxVal)
        Iflag = 0;
    else
    // Altrimenti restituisco 1
        Iflag = 1;

    return Iflag;
}

/* Funzione che calcola la formula trapezoidale composita sull'intervallo [c,d].	*/
/* Restituisce in output una stima Q dell'integrale.					*/
void Quadra(double c, double d, double* Q)
{
    double h,fc,fd,fm,t1,t2;

    h = d - c;
    fc = F(c);
    fd = F(d);
    fm = F((c + d)/2);
    t1 = h * (fc + fd) / 2;
    t2 = h * (fc + 2*fm + fd) / 4;
    *Q = t2;
}


/* Questa e' la funzione di cui si calcola l'integrale. Tale funzione va modificata 	*/
/* al variare della funzione integranda. Nel caso specifico e' la funzione e^x.		*/
double F(double x)
{
    return exp(x);
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


/* Funzione che controlla se lo stack e' vuoto.						*/
int IsStackEmpty(NODO* Head)
{
    if(Head == NULL)
        return 1;
    else
        return 0;
}


/* Funzione che inserisce un nuovo nodo nello stack. Uno stack e' composto da tre	*/
/* campi info, rappresentanti gli estremi dell'intervallo e il valore dell'integrale.	*/
NODO* Push(NODO* Head, double a, double b, double val)
{
	NODO* Nodo = (NODO*)malloc(sizeof(NODO));
	Nodo->a = a;
	Nodo->b = b;
	Nodo->val = val;
	Nodo->next = Head;
    Head = Nodo;

    return Head;
}


/* Funzione che permette l'estrazione dei campi info dallo stack.			*/
NODO* Pop(NODO* Head, double* a, double* b, double* val)
{
    NODO* Temp;

    if(!IsStackEmpty(Head))
    {
        *a = Head->a;
        *b = Head->b;
        *val = Head->val;
        Temp = Head;
        free(Head);
        Head = Temp->next;
    }
        return Head;
}
