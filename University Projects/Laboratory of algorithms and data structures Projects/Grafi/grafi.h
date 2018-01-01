#include "stack.h"
#include "lista.h"

//------------------definizone tipi funzioni-------------------------------------------------------
typedef void*(*FNINSVERT)(void* , int);
typedef void (*FNINSARCO)(void* , int , int , double);
typedef void (*FNCANCARCO)(void* , int , int );
typedef void (*FNCANCVERT)(void* , int);
typedef void (*FNRIC)(void* , int , int* );
typedef int (*FNACI)(void* , int );
typedef void (*FNSTP)(void*);
typedef void (*FNMOD)(void*,FILE*,int);

//-------------------------------------------------------------------------------------------------

//--------------------------definizione strutture--------------------------------------------------
typedef struct funz{
  FNINSVERT insVert;
  FNINSARCO ins_arco;   
  FNCANCARCO canc_arco;
  FNCANCVERT cancVert;
  FNRIC BFS;
  FNRIC DFS_visita;
  FNACI aciclico_visita;
  FNSTP stampa;
  FNSTP trasposto;
  FNSTP cambia_rap;
  FNMOD InsFile;
}FUNZ;


typedef struct vertice{
  void* id;       // identificativo del nodo
  int eliminato;  //flag per il cntrollo sull'eliminazione
  char colore[7];
} VERTICE;


typedef struct grafo {
  struct vertice *vert;  //array dei vertici
  void *struttura;       // puntatore alla struttura utilizzata (matrice o lista di adiacenza)
  int n_nodi;            // numero di nodi inseriti
  int n_vet;             //grandezza effettiva del vettore
  struct funz funzioni;  // struttura che contiene le funzione relative alla struttura utilizzata
} GRAFO;

//-------------------------------------------------------------------------------------------------


//-------------------prototipi di funzioni---------------------------------------------------------

/******************************************************************************************
 FUNZIONI GENERICHE
/*****************************************************************************************/

void leggi_grafo(GRAFO* grafo, char* nome_file);
void leggi_vertici(char* nome_file,GRAFO* grafo);
void leggi_archi(char* nome_file,GRAFO* grafo);
void ins_vert(GRAFO* , void* newid); // inserimento di un nuovo vertice
void canc_vert(GRAFO* G, int i); // cancellazione di un vertice dal grafo
void DFS( GRAFO* G, int* pred);// visita in profondità
void percorso_min(GRAFO* G, int start, int end); // ricerca del percorso minimo dal vertica start al vertice end
void stampaPercorso(int start, int end, int* pred); // stampa del percorso da start a end
int aciclico( GRAFO* G);
void InserimentoFile(GRAFO* G,char* NomeFile);

/******************************************************************************************
 FUNZIONI PER LA GESTIONE DI UNA MATRICE DI ADIACENZA
/*****************************************************************************************/
GRAFO* init_matr();
void stampa_matr(GRAFO* G);  // stampa di una matrice di adiacenza
void* ins_vert_matr(void* M, int n_nodi); // ridimensionamentop della matrice di adiacenza
void ins_arco_matr(GRAFO* G, int a, int b, double peso); //inserimento di un arco nella matrice di adiacenza
void canc_arco_matr(GRAFO* G, int a, int b); //cancellazione di un arco da matrice di adiacenza
void canc_vert_matr(GRAFO* G, int ind); // cancellazione di un vertice dalla matrice di adiacenza
void trasposto_matr(GRAFO* G ); //calcolo del grafo trasposto su matrice di adiacenza
void BFS_matr(GRAFO* G,int v, int* pred); // visita in ampiezza con riempimento dell'array dei predecessori 
void DFS_visita_matr( GRAFO* G, int v , int* pred);//visita in profondità per matrice
int aciclico_matr( GRAFO* G, int v );
void MatrToList(GRAFO* G);
void ModFileLista(GRAFO* G,FILE* fd,int i);


/******************************************************************************************
 FUNZIONI PER LA GESTIONE DI UNA LISTA DI ADIACENZA
/*****************************************************************************************/
GRAFO* init_lista();
void stampa_lista(GRAFO* G);
void* ins_vert_lista(void* struttura, int n_nodi);
void ins_arco_lista(GRAFO* grafo, int start, int end, double peso);
void canc_arco_lista(GRAFO* G, int start, int end);
void canc_vert_lista(GRAFO* G, int ind);
void trasposto_lista(GRAFO* G );
void BFS_lista(GRAFO* G,int v, int* pred);
void DFS_visita_lista( GRAFO* G, int v , int* pred);
int aciclico_lista( GRAFO* G, int v );
void ListToMatr(GRAFO* grafo);
void ModFileMatrice(GRAFO* G,FILE* fd,int i );



//-------------------------------------------------------------------------------------------------
