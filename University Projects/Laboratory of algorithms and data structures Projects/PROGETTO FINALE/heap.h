typedef struct heap_el{
    void* elem;
    float priorita;
    struct heap_el *prec;
}HEAP_EL;

typedef struct heap{
    HEAP_EL *array;
    int dim_array;
    int dim_heap;
}HEAP;


int         sinistro        (int i);
int         destro          (int i);
int         padre           (int i);
void        swap            (HEAP_EL* primo,HEAP_EL* secondo);
void        heapify         (HEAP *H,int i);
void        BuildHeap       (HEAP *H);
HEAP_EL*    minimo          (HEAP *H);
HEAP_EL*    EstraiMinimo    (HEAP* H);
void        stampa          (HEAP *H);
void        DecreaseKey     (HEAP *H,int i,float val);
void        IncreaseKey     (HEAP *H,int i,float val);
void        Inserimento     (HEAP *H,void* key,float prio,HEAP_EL* prev);
void        DeleteKey       (HEAP *H,int i);
int**       GeneratePath    (HEAP* closed,int endX,int endY);
int         XinCoda         (HEAP *H, int x , int y );

