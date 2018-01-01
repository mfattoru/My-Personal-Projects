/*Programma per la costruzione della spline cubica su n nodi assegnati
dall'utente e per la valutazione di questa in un punto assegnato*/

#include <stdio.h>
#include <math.h>

#define max_punti 25   /*Massimo numero di punti*/


void carica_punti(float *X ,float *Y,int *n)
/*funzione per la determinazione del numero di punti da inserire
  e per il caricamento di tali punti.
  La funzione prevede anche l'ordinamento dei punti in base alle ascisse*/
{   
    int i,j,trovato,trova,k;
    float appoggio;
    
    printf("* Questo programma permette di calcolare la spline cubica naturale\n");
    printf("  interpolante n punti da te assegnati e di valutarla in uno o piu' punti.\n");
   
    do
       {
        printf("\n\n\nDefinisci il numero di punti che vuoi inserire (min 2,max %i): ",max_punti);
        scanf("%i",n); 
        if (*n>(max_punti))
        printf("\n   Attenzione, puoi inserire al massimo %i punti !!!\n",max_punti);
        if (*n<2)
        printf("\n   Attenzione, devi inserire almeno 2 punti !!!\n");
       }       
    while((*n>max_punti)|(*n<2)); /*condizione di superamento del numero 
                                massimo di punti oppure di non raggiungimento 
                                del numero minimo*/
    
    printf("\n   Inserisci l'ascissa del punto 1 : x1=");
    scanf("%f",&X[0]);   
    printf("\n   Inserisci l'ordinata corrispondente : y1=");
    scanf("%f",&Y[0]);
    
    
    for(i=1;i<=*n-1;i++)
    {
        
        trova=1;
        
        while (trova==1)
        {
            printf("\n   Inserisci l'ascissa del punto %i : x%i=",i+1,i+1);
            scanf("%f",&X[i]);
            
            k=i-1;
            trovato=0;
            while ((k>=0)&(trovato==0)) /*questo ciclo controlla se la x
                                           appena inserita è già stata
                                           inserita precedentemente*/
            {
                if (X[i]==X[k])
                {
                    trovato=1;
                    printf("\n ===> Il valore x = %f e' gia' stato inserito <===\n",X[i]);
                }    
                k--;
                if ((k<0)&(trovato==0))
                trova=0;
            }
        }                        
                                 
        printf("\n   Inserisci l'ordinata corrispondente  : y%i=",i+1,i+1);
        scanf("%f",&Y[i]);
        
        j=i;
        while(X[j]<X[j-1]) /*tale ciclo effettua l'ordinamento dei punti
                                in base alle ascisse*/
        {
            appoggio=X[j];
            X[j]=X[j-1];
            X[j-1]=appoggio;
            
            appoggio=Y[j];
            Y[j]=Y[j-1];
            Y[j-1]=appoggio;
            
            if (j>1)
            j=j-1;       
        }    
    }           
}

void A_B_dF(float *ds,float *di,float *dF,float *X,float*Y,int n)
/*Funzione per la costruzione della matrice A,della matrice B e del vettore 
delle differenze divise di primo ordine delta-effe.
Da notare che per quanto riguarda A,essendo una matrice tridiagonale con gli 
elementi della diagonale principale tutti uguali a 2,basta costruire
soltanto la diagonale superiore(ds) e quella inferiore(di).
La matrice B non è necessario calcolarla perchè bastano la diagonale superiore
e inferiore di A*/

{
    int i;
    float delta,h,hpiu;
    
    ds[0]=1; /*pone il primo elementro delle diagonale superiore uguale a 1*/
    di[n-1]=1; /*pone l'ultimo elemento delle diagonale inferiore uguale a 1.
                Da notare che, essendo la dimensione di A uguale ad n,
                la dimensione della diagonale inferiore(di) è n-1 */
    
    for(i=0;i<=n-2;i++)
    {
        h=X[i+1]-X[i];       /*calcola h(i)*/
        hpiu=X[i+2]-X[i+1];  /*calcola h(i+1)*/
        
        delta=h/(h+hpiu);     /*calcola delta(i)*/
        
        ds[i+1]=delta; /*pone l'(i+1)-esimo elemento della diagonale superiore
                        uguale a delta(i).*/
        
        di[i]=(1-delta); /*pone l'i-esimo elemento della diagonale inferiore
                           uguale a 1-delta(i)*/
        
        dF[i]=(Y[i+1]-Y[i])/(X[i+1]-X[i]); /*calcola la i-esima differenza 
                                                divisa del primo ordine*/
    }
    dF[n-1]=(Y[n]-Y[n-1])/(X[n]-X[n-1]); /*calcola l' (n-1)-esima
                                               differenza divisa*/
}

void termini_noti(float *b,float *ds,float *di,float *dF,int n)
/*Funzione per la costruzione del vettore dei termini noti b=3*B*deltaEffe.
  I parametri ds e di sono rispettivamente la diagonale superiore e la
  diagonale inferiore della matrice B*/
{
    int i;
    
    b[0]=3*(ds[0]*dF[0]);
    b[n]=3*(di[n-1]*dF[n-1]);
    
    for(i=0;i<=n-2;i++)
        b[i+1]=3*((di[i]*dF[i])+(ds[i+1]*dF[i+1]));
}

void gauss(float *b,float *dp,float *ds,float *di,int n)
/*Funzione per la trasformazione del sistema "A lambda= b" in un sistema a 
  gradini
  Da notare che la matrice A è costituita dalla diagonale superiore(ds),
  dalla diagonale inferiore(di),e dalla diagonale principale(dp)*/
{
    int i;
    float molt;  /*variabile che contiene il valore del moltiplicatore*/
    
    dp[0]=2;  /*Pone il primo elemento della diagonale principale uguale a 2.
                Da notare che questo è anche il primo pivot*/ 
    
    for(i=0;i<=n-1;i++) /*ciclo sui passi*/
    {
        molt=di[i]/dp[i];  /*calcola il moltiplicatore*/
        dp[i+1]=2-molt*ds[i]; /*aggiorna il valore della diagonale principale*/
        b[i+1]=b[i+1]-molt*b[i]; /*aggiorna il vettore dei termini noti*/
    }    
}    


void back(float *b,float *dp,float *ds,int n)
/*Algoritmo di back substitutio per il calcolo delle incognite nel sistema
 A lambda = b.
 Da notare che le soluzioni lambda di tale sistema vengono memorizzate nel
 vettore b dei termini noti per una questione di risparmio di spazio*/
{
    int i;
    
    b[n]=b[n]/dp[n]; /* calcolo dell'n-sima soluzione*/
    for(i=n-1;i>=0;i--) /*ciclo sui passi*/
        b[i]=(b[i]-(ds[i]*b[i+1]))/dp[i]; /*calcolo delle restanti 
                                                soluzioni lambda(i)*/
}

void ricerca_binaria(float *X,int n,int *indice,float valuta)
/*Lo scopo di questa funzione è individuare l'intervallo in cui è contenuto
il punto in cui si vuole valutare(valuta) la spline
Se per esempio l'intervallo è [3,4] allora indice vale 3.*/
{
    int low,high,middle,trovato;
    
    low=0;
    high=n;
    trovato=0;
    
    
    while (trovato==0)  /*la condizione di uscita del ciclo è il momento in cui
                        l'intervallo è stato trovato(trovato=1)*/
    {
        middle=(low+high)/2;  /*middle divide a metà la porzione di vettore
                                su cui si effettua la ricerca*/
        if (valuta<X[middle]) 
        {
            high=middle-1;                
            if (valuta>=X[high]) 
            {
                *indice=high; 
                trovato=1;
            }
        }
        else
        {
            if (valuta>=X[middle])
            {
                low=middle+1;
                if (low!=n)
                {
                    if (valuta<X[low])
                    {
                        *indice=low-1;
                        trovato=1;
                    }
                }    
                else
                {
                    *indice=n-1;
                    trovato=1;
                }    
            }
            
        }
    }
}                            


void coeff_hermite(float *X,float *Y,float *b,float *Coeff,int n,int indice)
/*Calcola i 4 coefficienti del polinomio interpolante di hermite secondo 
la formula di Newton.
L'intervallo in cui calcola tali coefficienti è [x(indice),x(indice+1)]
Da notare che il vettore b ora contiene i valori delle incognite lambda.
Coeff è invece un vettore di 4 elementi nel quale vengono memorizzati
i 4 coefficienti*/
{
    int i,k;
    float diff_x,diff_div;
    
    diff_x=(X[indice+1]-X[indice]);
    Coeff[0]=Y[indice];    /*coefficiente a(indice)*/
    Coeff[1]=b[indice];    /*coefficiente b(indice)*/
    
    k=2;
    for(i=3;i>=k-1;i--)
    if (i>k)
    Coeff[i]= (Y[indice+1]-Y[indice])/diff_x; /*pone nell'ultima posizione
                                                (la terza) del
                                                vettore coeff la differenza 
                                                divisa del primo ordine 
                                                y[x(indice),x(indice+1)] 
                                               che serve per calcolare il 
                                               coefficiente c(indice)*/
    else    
    if (i==k)
    Coeff[i]=(Coeff[i+1]-b[indice])/diff_x;  /*pone nella seconda posizione
                                               del vettore coeff il coefficiente
                                               c(indice)*/   
    else
    Coeff[i+2]=(b[indice+1]+b[indice]-(2*Coeff[i+2]))/pow(diff_x,2); /*pone
                                                           nella terza posizione
                                                           del vettore coeff
                                                           il coefficiente
                                                           d(indice)*/     
}    

void Horner(float *X,float *Coeff,float valuta,int indice)
/*funzione per la valutazione della spline nel punto x = valuta*/
{
    int i;
    float s;
    
    s=Coeff[3];
    for (i=2;i>=0;i--)
    {
        if (i==2)                               
        s=(s*(valuta-X[indice+1]))+ Coeff[i]; /* entra nell' "if" solo una
                                                volta(i=2)*/         
        else
        s=(s*(valuta-X[indice]))+ Coeff[i];
    }       
    
    printf("\n\n Il valore della spline in x = %f e' : %f\n",valuta,s);     
    getchar();
}

void horner2(float *X,float *Y,float *b,float valuta,int n)
/*funzione per la valutazione della spline nel punto x = valuta nel caso in cui
il punto di valutazione è esterno all'intervallo [x(1)<x(2)......<x(n)],
cioè valuta<x(1) oppure valuta>x(n)*/
{ 
    float s;
    
    if (valuta<X[0])
    s=Y[0]+((valuta-X[0])*b[0]);
    else
    s=Y[n]+((valuta-X[n])*b[n]);
    
    printf("\n\n Il valore della  spline in x = %f e' : %f\n",valuta,s);
}
    
void menu(int *c)
{
    printf("\n                    Cosa desideri fare ? \n");
    printf("\n  [1] - Valutare il polinomio in un punto assegnato");
    printf("\n  [2] - Uscire dal programma");
    printf("\n\n Digita il numero corrispondente alla tua scelta e premi invio: ");
    scanf("%i",c);
}

main()
{
    float vet_X[max_punti]; 
    float vet_Y[max_punti];
    float vet_b[max_punti];
    float vet_diag_p[max_punti];
    float vet_diag_s[max_punti-1];
    float vet_diag_i[max_punti-1];
    float vet_deltaF[max_punti-1];
    float vet_coef[4];
    int dim;      /*numero di punti inseriti dall'utente*/
    int ind,scegli;
    
    float valutazione;  /*il punto in cui valutare*/
    
    carica_punti(vet_X,vet_Y,&dim);
    /*alle funzioni che seguono passo dim-1 perchè tutti i vettori partono
    dalla posizione zero*/
    
    A_B_dF(vet_diag_s,vet_diag_i,vet_deltaF,vet_X,vet_Y,dim-1);
    
    termini_noti(vet_b,vet_diag_s,vet_diag_i,vet_deltaF,dim-1);
    
    gauss(vet_b,vet_diag_p,vet_diag_s,vet_diag_i,dim-1);
    
    back(vet_b,vet_diag_p,vet_diag_s,dim-1);
    
    
    while (scegli!=2) /*visualizza il menù di scelta fino a quando la scelta
                        non è uguale a due, cioè fin quando l'utente non decide
                        di uscire dal programma*/
    {
  
    menu(&scegli); 
    switch(scegli)  
    {
      case 1 :  {
                      printf("\n      Inserisci il  punto in cui valutare: ");
                      scanf("%f",&valutazione);
                      if ((valutazione>=vet_X[0])&&(valutazione<=vet_X[dim-1]))
                      /*il punto di valutazione è contenuto nell'intervallo
                       [x(1)<x(2)......<x(n)]*/
                      {
                          ricerca_binaria(vet_X,dim-1,&ind,valutazione);
                          coeff_hermite(vet_X,vet_Y,vet_b,vet_coef,dim-1,ind);
                          Horner(vet_X,vet_coef,valutazione,ind);
                      }    
                      else
                      /*il punto di valutazione non è contenuto nell'intervallo
                       [x(1)<x(2)......<x(n)]*/    
                          horner2(vet_X,vet_Y,vet_b,valutazione,dim-1);
                          
                      printf("\n...premi invio per continuare\n");
                      //getche();
                      break;
                }                
          
      case 2 :   break;
      /*default gestisce la situazione in cui l'utente digita una scelta
      diversa da 1 o da 2.In tal caso visualizza un messaggio di errore*/
      default:  {printf("\n              Selezione sbagliata !!!\n\n");        
                 printf("\n...premi invio per continuare\n");
                 //getche();
                 break;
                }     
     
    }
    }
    
}
