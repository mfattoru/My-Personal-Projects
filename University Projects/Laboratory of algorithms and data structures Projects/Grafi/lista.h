//GESTIONE DI UNO STACK


typedef struct lista {
  int valore;
  double peso;
  struct lista* next;
} LISTA;


LISTA* MakeLista(int, double ); // istanzia un elemento dello stack
LISTA* ins_testa(LISTA* , int , double); //inserisci in cima allo stack
LISTA* ins_coda(LISTA* pila, int valore, double );// inserisce in coda
int pop_lista(LISTA* pila ); //preleva dalla cima dello stack
LISTA* del_testa_lista(LISTA* pila); // cancella dalla testa;
int vuoto_list(LISTA* ); // restituisce 1 se lo stack e' vuoto
LISTA* canc_elemento(LISTA* lista, int elemento); // cancella elemento da lista
LISTA* canc_lista(LISTA* lista); // cancella una lista
