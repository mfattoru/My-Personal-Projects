#include "heap.h"
#include <stdio.h>
#include <limits.h>
#include <malloc.h>
#include <float.h>

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
    HEAP_EL *temp=(HEAP_EL*)malloc(sizeof(HEAP_EL));
    if(H->dim_heap<1){
        temp=NULL;
    }
    else{
        *temp=*(H->array);
    }
    return temp;
}

HEAP_EL* EstraiMinimo(HEAP* H){
    HEAP_EL *temp=(HEAP_EL*)malloc(sizeof(HEAP_EL));
    if(H->dim_heap<1){
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
        printf("[%d][%d] %f -> ",*(int*)((H->array+k)->elem),*(int*)((H->array+k)->elem+sizeof(int)),((H->array+k)->priorita));
    }
}

void DecreaseKey(HEAP *H,int i,float val){
    if(val<(H->array+i)->priorita){
        //printf("PRIORITA MAGGIORE DI QUELLA ATTUALE\n");
    }
    else{
        (H->array+i)->priorita=val;
        heapify(H,0);
    }
}

void IncreaseKey(HEAP *H,int i,float val){
    int x;
    if(val>(H->array+i)->priorita){
        //printf("PRIORITA MINORE DI QUELLA ATTUALE\n");
    }
    else{
        (H->array+i)->priorita=val;
         if(padre(i)<0){
            x=0;
         }
        else{
            x=padre(i);
        }
        while(i>-1 && (H->array+x)->priorita > (H->array+i)->priorita){
            if(padre(i)<0){
                x=0;
            }
            else{
                x=padre(i);
            }
            swap(H->array+i,H->array+x);
            i=padre(i);
        }
    }
}

void Inserimento(HEAP *H,void* key,float prio,HEAP_EL* prev){
    if(H->array == NULL){
        H->array = (HEAP_EL*)malloc(sizeof(HEAP_EL) * 5);
        H->dim_array = 5;
    }

    else if(H->dim_heap>=H->dim_array){
        H->array= (HEAP_EL*)realloc(H->array,sizeof(HEAP_EL)*(H->dim_array+5));
        H->dim_array+=5;
    }

    (H->array+(H->dim_heap))->priorita=FLT_MAX;
    (H->array+(H->dim_heap))->elem=key;
    (H->array+(H->dim_heap))->prec=prev;
    IncreaseKey(H,H->dim_heap,prio);
    H->dim_heap+=1;
 }

 void DeleteKey(HEAP *H,int i){
    if(H->dim_heap<1){
        printf("\nHEAP VUOTO\n");
    }
    else{
        swap(H->array+i,H->array+H->dim_heap-1);
        H->dim_heap-=1;
        heapify(H,i);

    }
 }



int XinCoda(HEAP *H, int x , int y ){
  int ris = -1, i = 0;
  int *elem;
  if(H->dim_heap > 0){
    for(i = 0; ris < 0 && i < H->dim_heap; ++i){
      elem = (int*)H->array[i].elem;
      if(elem[0] == x && elem[1] == y)
        ris = i;
    }
  }
  return ris;
}



int** GeneratePath(HEAP* closed,int endX,int endY){
    int dim = 0, i = 0, j = 0;
    HEAP_EL* curr = (HEAP_EL*)malloc(sizeof(HEAP_EL));
    HEAP_EL* temp;
    int* valore;
    int** path = (int**)malloc(sizeof(int*) * 10);
    for(i = 0; i < 10 ; ++i){
        path[i] = (int*)malloc(sizeof(int) * 2);
    }
    dim = 10;
    *curr = closed->array[XinCoda(closed, endX, endY)];
    i = 0;
    temp = curr;
    while(curr->prec != NULL){
        if (i != 0 && i % 10 == 0){
            path = (int**)realloc(path, sizeof(int*) * (dim + 10) );
            for(j = dim; j < dim +10; ++j){
                path[j] = (int*)malloc(sizeof(int) * 2);
            }
            dim += 10;
        }
        valore = (int*)curr->elem;
        path[i][0] = valore[0];
        path[i][1] = valore[1];
        curr = curr->prec;
        ++i;
    }
    if(i % 10 == 0){
        path = (int**)realloc(path, sizeof(int*) * (dim + 1) );
    }
    path[i] = NULL;
    return path;
}



