typedef void*(*FNINSERT)(void*,int);
typedef void*(*FNINSARCO)(void*,int,int,double);
typedef void*(*FNDELARCO)(void*,int,int);
typedef void*(*FNCMPVALORE)(void*,void*);
typedef void*(*FNDELVERT)(void*,void*);

typedef struct funz{
    FNINSERT insert;
    FNINSARCO InsertArco;
    FNDELARCO CancArco;
    FNDELVERT CancVert;
    FNCMPVALORE ConfrontaValore;
}FUNZ;

typedef struct vertice{
    void *valore;
    char* colore;
    int eliminato;
}VERTICE;

typedef struct grafo{
    VERTICE* vert;
    void* struttura;
    int n_nodi;
    int n_vert;
    FUNZ funzione;
}GRAFO;

typedef struct pila{
    VERTICE* vertice;
    struct pila* next;
}PILA;

void InserisciVertice(GRAFO* G,void* nome);
void* ins_matr(void* M, int n_nodi);
void stampa(GRAFO* G);
void InserisciArco(GRAFO* G,int x,int y,double peso);
void InserisciArcoOrientato(GRAFO* G,int x,int y,double peso);
void CancellaArco(GRAFO* G,int x,int y);
void CancellaArcoOrientato(GRAFO* G,int x,int y);
int ConfrontaDouble(double x,double y);
void CancellaVertice(GRAFO* G,void* key);
int ConfrontaStringa(char* x,char* y);
char* GeneraStringa ();
void Trasposta(GRAFO* G);


PILA* InsertTesta(PILA* pila,VERTICE* vert);
VERTICE* PrelevaTesta(PILA* pila);
PILA* CancellaTesta(PILA* pila);
int vuota(PILA* pila);

