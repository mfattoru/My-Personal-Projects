#include <malloc.h>
#include "funzioni.h"

int vuota(PILA* pila){
    int res=0;
    if(pila){
        res=1;
    }
    return res;
}

PILA* InsertTesta(PILA* pila,VERTICE* vert){
    PILA* temp;
    temp=(PILA*)malloc(sizeof(PILA));
    temp->vertice=vert;
    temp->next=NULL;
    if(pila){
        temp->next=pila;
    }
    return temp;
}

VERTICE* PrelevaTesta(PILA* pila){
    return pila->vertice;
}

PILA* CancellaTesta(PILA* pila){
    PILA* temp=NULL;
    if(pila){
        temp=pila->next;
        free(pila);
    }
    return temp;
}

PILA* InserisciCoda(PILA *pila, VERTICE* vert){
    PILA *temp,*ultimo;
    temp=(PILA*)malloc(sizeof(PILA));
    temp->vertice=vert;
    temp->next=NULL;
    if(pila){
        ultimo=pila;
        while(ultimo->next){
            ultimo=ultimo->next;
        }
        ultimo->next=temp;
    }
    else{
        pila=temp;
    }
    return pila;
}
