#include <stdio.h>

typedef struct heap{
    int priorita;
    void* elem;
    struct heap* sx;
    struct heap* dx;
    struct heap* padre;
    struct heap* ultimo;
}HEAP;

HEAP* Inserimento(HEAP *H,int prio,void* key);
void stampa(HEAP* H);
void BuildHeap(HEAP *H);
void heapify(HEAP *H);
void swap(HEAP* primo,HEAP* secondo);
HEAP* Massimo(HEAP* H);
HEAP* EstraiMassimo(HEAP* H);
void DecreaseKey(HEAP* H,int val);
void IncreaseKey(HEAP *H,int val);
HEAP* DeleteKey(HEAP* H,HEAP* Rad);
