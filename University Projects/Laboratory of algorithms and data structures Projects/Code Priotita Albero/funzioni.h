#include <stdio.h>

typedef struct heap{
    int priorita;
    void* elem;
    heap* sx;
    heap* dx;
    heap* padre;
    heap* ultimo;
}HEAP;

