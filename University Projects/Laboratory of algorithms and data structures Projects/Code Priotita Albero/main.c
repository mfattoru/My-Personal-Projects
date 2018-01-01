#include "header.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(){
    HEAP *temp;
    HEAP* H;
    H=malloc(sizeof(int));
    H=NULL;
    int i=0;
    srand(time(NULL));
    while(i<30){
        H=Inserimento(H,rand()%300,rand()%300);
        i++;
    }
    printf("INSERIMENTO:\n");
    stampa(H);

    temp=Massimo(H);
    printf("\nVALORE: %d\n",temp->priorita);
    BuildHeap(H);
    printf("\nHEAPIFY\n");
    stampa(H);
    temp=Massimo(H);
    printf("\nVALORE: %d\n",temp->priorita);
    printf("\nESTRAI MASSIMO\n");
    temp=EstraiMassimo(H);
    printf("\nVALORE: %d\n",temp->priorita);
    printf("\nALBERO DOPO ESTRAZIONE\n");
    stampa(H);
    printf("\nDECREASE KEY\n");
    DecreaseKey(H,100);
    stampa(H);
    printf("\nINCREASE KEY\n");
    IncreaseKey(H,500);
    stampa(H);

    printf("\nDELETE KEY\n");
    H=DeleteKey(H->sx,H);
    stampa(H);

    return 0;

}
