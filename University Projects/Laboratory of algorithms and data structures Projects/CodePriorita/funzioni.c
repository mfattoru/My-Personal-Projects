#include "header.h"
#include <stdio.h>
#include <limits.h>

int sinistro(int i){
    return 2*i+1;
}

int destro(int i){
    return 2*i+2;
}

int padre(int i){
    if(i!=0){
        return (i-1)/2;
    }
    else return -1;
}

void swap(HEAP_EL* primo,HEAP_EL* secondo){
    HEAP_EL temp;
    temp=*(primo);
    *(primo)=*(secondo);
    *(secondo)=temp;
}

void heapify(HEAP *H,int i){
    int l,r,min;
    l=sinistro(i);
    r=destro(i);
    if(l<H->dim_heap && ((H->array+l)->priorita)<((H->array+i)->priorita)){
        min=l;
    }
    else {
        min=i;
    }
    if(r<H->dim_heap && ((H->array+r)->priorita)<((H->array+min)->priorita)){
        min=r;
    }
    if (min!=i){
        swap(H->array+i,H->array+min);
        heapify(H,min);
    }
}


void BuildHeap(HEAP *H){
    int n,i;
    n=H->dim_array;
    H->dim_heap=n;
    for(i=(n/2-1);i>=0;--i){
        heapify(H,i);
    }
}

HEAP_EL* minimo(HEAP *H){
    if(H->dim_heap<1){
        printf("HEAP VUOTO \n");
        return NULL;
    }
    else{
        return H->array;
    }
}

HEAP_EL* EstraiMinimo(HEAP* H){
    HEAP_EL *temp=(HEAP_EL*)malloc(sizeof(HEAP_EL));
    if(H->dim_heap<1){
        printf("HEAP VUOTO\n");
        temp=NULL;
    }
    else{

        *temp=*(H->array);
        *(H->array)=*(H->array+(H->dim_heap-1));
        H->dim_heap=H->dim_heap-1;
        heapify(H,0);
    }
    return temp;
}

void stampa(HEAP *H){
    int k=0;
    printf("\n");
    for(k=0;k<H->dim_heap;k++){
        printf("%d -> ",(int*)((H->array+k)->priorita));
    }
}

void DecreaseKey(HEAP *H,int i,int val){
    if(val>(H->array+i)->priorita){
        printf("PRIORITA MAGGIORE DI QUELLA ATTUALE\n");
    }
    else{
        (H->array+i)->priorita=val;
        heapify(H,0);
    }
}

void IncreaseKey(HEAP *H,int i,int val){
    if(val<(H->array+i)->priorita){
        printf("PRIORITA MINORE DI QUELLA ATTUALE\n");
    }
    else{
        (H->array+i)->priorita=val;
        while(i>-1 && (H->array+padre(i))->priorita < (H->array+i)->priorita){
            swap(H->array+i,H->array+padre(i));
            i=padre(i);
        }
    }
}

void Inserimento(HEAP *H,int prio,void* key){
    H->dim_heap+=1;
    if(H->dim_heap>H->dim_array){
        realloc(H->array,sizeof(HEAP_EL)*5);
        H->dim_array+=5;
    }
    (H->array+(H->dim_heap))->priorita=INT_MIN;
    (H->array+(H->dim_heap))->elem=key;
    IncreaseKey(H,H->dim_heap,prio);
 }

 void DeleteKey(HEAP *H,int i){
    if(H->dim_heap<1){
        printf("\nHEAP VUOTO\n");
    }
    else{
        swap(H->array+i,H->array+H->dim_heap-1);
        /*if((H->array+H->dim_heap-1)->priorita > (H->array+i)->priorita){
            printf("CASA");
            IncreaseKey(H,i,(H->array+H->dim_heap-1)->priorita);
        }
        else{
            printf("CASA2");
            DecreaseKey(H,i,(H->array+H->dim_heap-1)->priorita);
        }*/
        H->dim_heap-=1;
        heapify(H,i);

    }
 }

