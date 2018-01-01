#include <malloc.h>
#include <stdio.h>
#include "input.h"

/*funzione che gestisce lo  storage dinamico in memoria dell'input da tastiera*/
char* get_input(){
  int i=0;
  char *p;
  char *e="Memoria insufficiente";
  char carattere;

  /*
  alloco la quantità di memoria necessaria a contenere un tipo di dato char
  e faccio il casting del risultato (un puntatore a quella zona di memoria)
  al tipo puntatore di char (char *)
  */
  p = (char *) malloc(sizeof(char));
  if (p==NULL){
    return e;
  }
  p[i]=getchar();
  if (p[0]=='\n'){ /*Caso in cui viene premuto subito invio*/
    p[0]='\0';
    return p;
  }
  do{
    /*
    rialloco la memoria in modo da averne disponibile tanta quanta ne serve
    per ospitare (i+1) variabili di tipo char (totale caratteri nell'array)
    */
    ++i;
    p = (char *) realloc (p, (i+1) * sizeof(char));
    if (p==NULL){
      return e;
    }
    p[i] = getchar();
  }while(p[i] != '\n');
  p[i] = '\0';
  return p;
}


