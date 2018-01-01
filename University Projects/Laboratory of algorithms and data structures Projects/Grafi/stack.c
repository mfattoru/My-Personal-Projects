//GESTIONE DI UNO STACK

#include <stdio.h>
#include "stack.h"

// istanzia un elemento dello stack
STACK* MakeStack(int valore){
  STACK* nuovo = (STACK*)malloc(sizeof(STACK));
  nuovo->valore = valore;
  nuovo->next = NULL;
  return nuovo;
}


 //inserisci in cima allo stack
STACK* push(STACK* pila, int valore){
  STACK* nuovo;
  nuovo = MakeStack(valore);
  nuovo->next = pila;
  return nuovo;
}


// inserisci in  coda
STACK* accoda(STACK* pila, int valore ){
  if(pila){
    while(pila->next){
      pila = pila->next;
    }
    pila->next = MakeStack(valore);
  }
  else{
    pila = MakeStack(valore);
  }
  return pila;
}

 //cancella la testa
STACK* del_testa(STACK* pila){
  STACK* temp;
  temp = pila;
  pila = pila->next;
  free(temp);
  return pila;
}


 //preleva dalla cima dello stack
int pop(STACK* pila ){
  int valore = -100;
  if(pila != NULL)
    valore = pila->valore;
  return valore;
}



// restituisce 1 se lo stack è vuoto
int vuoto(STACK* pila){
  int x = 0;
  if (pila == NULL)
    x = 1;
  return x;
}


