typedef struct _pila{
    NODO* nodo;
    struct _pila* next;
}PILA;

PILA* InsertTesta(PILA* pila,NODO* nodo);
NODO* PrelevaTesta(PILA* pila);
PILA* CancellaTesta(PILA* pila);
int vuota(PILA* pila);

int vuota(PILA* pila){
    int res=0;
    if(pila){
        res=1;
    }
    return res;
}

PILA* InsertTesta(PILA* pila,NODO* nodo){
    PILA* temp;
    temp=(PILA*)malloc(sizeof(PILA));
    temp->nodo=nodo;
    temp->next=NULL;
    if(pila){
        temp->next=pila;
    }
    return temp;
}

NODO* PrelevaTesta(PILA* pila){
    return pila->nodo;
}

PILA* CancellaTesta(PILA* pila){
    PILA* temp=NULL;
    if(pila){
        temp=pila->next;
        free(pila);
    }
    return temp;
}




