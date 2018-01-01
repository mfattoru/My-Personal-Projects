typedef int(*FNCMP)(void*,void*);
typedef int(*FNCHK)(void*);
typedef void(*FNPRINT)(void*);

typedef struct _nodo
{ 	void* valore;
	struct _nodo* sx;
	struct _nodo* dx;
}NODO;

NODO* Insert(NODO *Old,FNCMP Compare,void* var);
void StampaStr (NODO* Radice);
void StampaInt(NODO* Radice);
void StampaFlt(NODO* Radice);
NODO* Dealloca(NODO *Radice);
NODO* StaccaNodo(NODO* Radice,NODO* Padre);
NODO* Cancella(NODO* Radice,void* var,FNCMP Compare);
int CheckDispari(int* x);
int CheckPari(int* x);
NODO* EliminaRange(NODO* Albero ,FNCHK Check,void* start,void* end,FNCMP Compare);
void PrintInt_iter(int* x);
void PrintFloat_iter(float* x);
void PrintStr_iter(char* x);






