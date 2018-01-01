#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "grafi.h"

int main(){
  int i, j ;
  GRAFO* G;
  int *pred;
  /*double** matr = (double**)malloc(sizeof(double*) * 5);
  for(i = 0; i < 5; ++i){
    matr[i] = (double*)malloc(sizeof(double) * 5);
  }
  for(i = 0; i < 5; ++i){
    for(j = 0; j < 5; ++j){
      matr[i][j] = 10;
    }
  }*/
  G = init_matr();
  leggi_grafo(G, "grafo.txt");
  /*for (i=0; i< 10; ++i)
    ins_vert(G, malloc(sizeof(int)));
  printf("%d\n", G->n_vet);
  printf("%d\n", G->n_nodi);
  G->funzioni.ins_arco(G, 1, 4, 32);
  G->funzioni.ins_arco(G, 4, 6, 45);
  G->funzioni.ins_arco(G, 4, 2, 45);
  G->funzioni.ins_arco(G, 2, 3, 45);
  G->funzioni.ins_arco(G, 3, 1, 45);
  printf("inserito\n");*/
  pred = (int*)malloc(sizeof(int) * G->n_vet);
  for(i = 0; i < G->n_vet; ++i)
    pred[i] = 0;
  /*BFS(&G, 3, pred);
  for(i = 0; i < G.n_vet; ++i)
    printf("%d -> ", pred[i]);*/
  //percorso_min(&G, 4, 1);
  printf("\n");
  //G.funzioni.cancVert(&G, 3);
  //trasposto_matr(&G);
  printf("\n\n\n\n");
  G->funzioni.stampa(G);
  printf("\n\n");
  if(aciclico(G))
    printf("aciclico\n");
  else
    printf("ciclico\n");
  //G->funzioni.trasposto(G);
  InserimentoFile(G,"GrafoMatr.txt");
  G->funzioni.cambia_rap(G);
  G->funzioni.stampa(G);
  percorso_min(G, 4, 1);
  InserimentoFile(G,"NuovoGrafo.txt");
  system("PAUSE");	
  return 0;
}
