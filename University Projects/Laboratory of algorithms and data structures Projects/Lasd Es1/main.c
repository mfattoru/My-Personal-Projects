#include <stdio.h>
#include "libreria.h"
#include "Compare.h"
#include "insert.h"
#include "iterativa.h"


int main(){
    NODO* Albero=NULL;
	char scelta;
	void *parola,*start,*end;
	srand(time(NULL));
	do{

		printf("Cosa vuoi fare:\n");
		printf("1)Inserisci nodo nella lista\n");
		printf("2)Stampa lista\n");
		printf("3)Dealloca lista\n");
		printf("4)Cancella un elemento dalla lista\n");
		printf("5)Cancella da lista tramite parametri\n");
		printf("0)Per uscire\n");
		printf("SCELTA:");
		scelta=_getch();
		fflush(stdin);
		switch(scelta){
			case '1':
				printf("\nDigita la parola da inserire\n");
				parola=RandInt();
				printf("CREAZIONE AVVENUTA ");
				Albero=InsertIter(Albero,&CompareInt,parola);
				printf("\n\n");
				break;
			case '2':
				printf("\nEcco la lista stampata\n\n");
				printf("STAMPA ITERATIVA\n");
				StampaIter(Albero,&PrintInt_iter);
				printf("\nSTAMPA RICORSIVA\n");
				StampaInt(Albero);
				printf("\n\n");
				break;
			case '3':
				Albero= DeallocaIter(Albero,&PrintInt_iter);
				printf("\nLista deallocata\n");
				printf("\n\n");
				break;
			case '4':
                printf("\nInserisci la parola da cancellare\n");
                parola=InputInt();
                //Albero=Cancella(Albero,parola,&CompareInt);
                Albero=CancellaIter(Albero,&CompareInt,parola);
                printf("\n\n");
                break;
            case '5':
                printf("Inserire stringa di partenza\n");
                start=InputInt();
                printf("start %d\n",*(int*)start);
                printf("inserire stringa di fine\n");
                end=InputInt();
                printf("end %d\n",*(int*)end);
                Albero=CancellaRangeIter(Albero,&CheckDispari,start,end,&CompareInt);
		}
	}while(scelta!='0');
	return 0;
}
