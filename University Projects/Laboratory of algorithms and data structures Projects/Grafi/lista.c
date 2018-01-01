#include "lista.h"
#include <stdio.h>

// istanzia un elemento dello stack
LISTA* MakeLista(int valore, double peso){
  LISTA* nuovo = (LISTA*)malloc(sizeof(LISTA));
  nuovo->valore = valore;
  nuovo->peso = peso;
  nuovo->next = NULL;
  return nuovo;
}


 //inserisci in cima allo stack
LISTA* ins_testa(LISTA* pila, int valore, double peso ){
  LISTA* nuovo;
  nuovo = MakeLista(valore, peso);
  nuovo->next = pila;
  return nuovo;
}


// inserisci in  coda
LISTA* ins_coda(LISTA* pila, int valore, double peso ){
  if(pila){
    while(pila->next){
      pila = pila->next;
    }
    pila->next = MakeLista(valore, peso);
  }
  else{
    pila = MakeLista(valore, peso);
  }
  return pila;
}

 //cancella la testa
LISTA* del_testa_lista(LISTA* pila){
  LISTA* temp;
  temp = pila;
  pila = pila->next;
  free(temp);
  return pila;
}


 //preleva dalla cima dello stack
int pop_lista(LISTA* pila ){
  int valore = -100;
  if(pila != NULL)
    valore = pila->valore;
  return valore;
}



// restituisce 1 se lo stack è vuoto
int vuoto_list(LISTA* pila){
  int x = 0;
  if (pila == NULL)
    x = 1;
  return x;
}



// cancella elemento da lista
LISTA* canc_elemento(LISTA* lista, int elemento){
  if(lista != NULL){
    if(lista->valore == elemento){
      lista = del_testa_lista(lista);
    }
    else{
      lista->next = canc_elemento(lista->next, elemento);
    }
  }
  return lista;
} 


//cancella una lsita
LISTA* canc_lista(LISTA* lista){
  if(lista){
    canc_lista(lista->next);
    free(lista);
  }
  return NULL;
}
