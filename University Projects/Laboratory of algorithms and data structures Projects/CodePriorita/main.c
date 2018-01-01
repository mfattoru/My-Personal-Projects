#include <stdio.h>
#include "header.h"
#include <malloc.h>
#include <time.h>

int main(){
    int i=0;
    srand(time(NULL));
    HEAP *H;
    HEAP_EL* temp;
    H=malloc(sizeof(HEAP));
    H->dim_array=8;
    H->dim_heap=8;
    H->array=malloc(sizeof(HEAP_EL)*(H->dim_array));
    for(i=0;i<(H->dim_array);i++){
        ((H->array+i)->elem)=malloc(sizeof(int));
        ((H->array+i)->elem)=rand()%300;
        ((H->array+i)->priorita)=rand()%300;
    }
    stampa(H);
    BuildHeap(H);
    stampa(H);
    temp=minimo(H);
    printf("\nMINIMO: %d-%d",temp->elem,temp->priorita);
    temp=EstraiMinimo(H);
    printf("\nMINIMO ESTRATTO: %d-%d\n",temp->elem,temp->priorita);
    printf("\nSENZA MINIMO: ");
    stampa(H);
    printf("\nCHIAVE DECREMENTATA :");
    DecreaseKey(H,0,10);
    stampa(H);
    printf("\nCHIAVE INCREMENTATA :");
    IncreaseKey(H,6,300);
    stampa(H);
    Inserimento(H,237,600);
    printf("\nCHIAVE INSERITA\n");
    stampa(H);
    DeleteKey(H,1);
    printf("\nCHIAVE CANCELLATA\n");
    stampa(H);
    return 0;
}


