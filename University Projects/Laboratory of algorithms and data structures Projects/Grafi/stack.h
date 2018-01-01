//GESTIONE DI UNO STACK


typedef struct stack {
  int valore;
  struct stack* next;
} STACK;


STACK* MakeStack(int ); // istanzia un elemento dello stack
STACK* push(STACK* , int ); //inserisci in cima allo stack
STACK* accoda(STACK* pila, int valore );// inserisce in coda
int pop(STACK* pila ); //preleva dalla cima dello stack
STACK* del_testa(STACK* pila); // cancella dalla testa;
int vuoto(STACK* ); // restituisce 1 se lo stack e' vuoto
