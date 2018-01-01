#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>


typedef struct _nodo
{ 	char stringa[30];
	struct _nodo* sx;
	struct _nodo* dx;
}NODO;

void Input(char* valore,int lun);
NODO* Insert(NODO *Old,char* parola);
void stampa(NODO *Lista);
NODO* Dealloca(NODO *Lista);
NODO* Cancella(NODO *Lista);
char* CercaMax(NODO* Radice);
NODO* CancellaMax(NODO* Radice);
NODO* RicercaNodo(NODO* Radice,char* parola);
/*NODO* Fondi(NODO* Lista1,NODO* Lista2);
NODO* EliminaRange(NODO* Lista1 ,int pari,char* start,char* end);*/

int main()
{	NODO* Albero=NULL;
    NODO* Albero2=NULL;
    NODO* Albero3=NULL;
    char start[30];
    char end[30];
    int pari;
	char scelta;
	char scelta2;
	char parola[30];
	char temp;
	do{
		printf("Cosa vuoi fare:\n");
		printf("1)Inserisci nodo nella lista\n");
		printf("2)Stampa lista\n");
		printf("3)Dealloca lista\n");
		printf("4)Cancella un elemento dalla lista\n");
		printf("5)Unisci due liste\n");
		printf("6)Cancella da lista tramite parametri\n");
		printf("0)Per uscire\n");
		printf("SCELTA:");
		scelta=_getch();
		switch(scelta){
			case '1':
				printf("\nDigita la parola da inserire\n");
				Input(parola,30);
				Albero=Insert(Albero,parola);
				printf("\n\n");
				break;
			case '2':
				printf("\nEcco la lista stampata\n\n");
				stampa(Albero);
				printf("\n\n");
				break;
			case '3':
				Albero=Dealloca(Albero);
				printf("\nLista deallocata\n");
				printf("\n\n");
				break;
			case '4':
                printf("\nInserisci la parola da cancellare\n");
                Input(parola,30);
                Albero=Cancella(RicercaNodo(Albero,parola));
                printf("\n\n");
                break;
            /*case '5':
                printf("\nCrea una nuova lista\n");
                do{
                    printf("\nDigita la parola da inserire\n");
				    Input(parola,30);
				    Albero2=Insert(Albero2,parola);
				    printf("\nVuoi continuare ad inserire elementi nella seconda lista? Y/N\n");
                    scelta2=_getch();
                }while(scelta2=='Y' || scelta2=='y');
                stampa(Albero2);
                printf("\n\n");
                Albero3=Fondi(Albero,Albero2);
                printf("\nStampa della tera lista\n\n");
                stampa(Albero3);
                printf("NULL\n\n");
                break;
            case '6':
                printf("Inserire stringa di partenza\n");
                Input(start,30);
                printf("inserire stringa di fine\n");
                Input(end,30);
                do{
                    printf("Vuoi cancellare le stringhe pari o dispari?  P/D\n");
                    temp=_getch();
                    if(temp=='P' || temp=='p'){
                        pari=1;
                    }
                    else{
                        pari=0;
                    }
                }while( temp!='p' && temp!='P' && temp!='d' && temp!='D');
                Albero=EliminaRange(Albero ,pari,start,end);*/
		}
	}while(scelta!='0');
	return 0;
	}


void Input(char* valore,int lun)
{ 	int i=0;
	valore=fgets(valore,lun,stdin);
	for(i=0;valore[i]<0 || valore[i]>32;i++);
	valore[i]=0;
	fflush(stdin);
}

NODO* Insert(NODO *Old,char* parola)
{ 	NODO* nuovo=Old;
    if(Old){
        if(strcmp(parola,Old->stringa)>0){
            nuovo->dx=Insert(Old->dx,parola);
        }
        else if(strcmp(parola,Old->stringa)<0){
            nuovo->sx=Insert(Old->sx,parola);
        }
        else{
            printf("stringa gia inserita\n");
        }
    }
    else{
        nuovo=(NODO*)malloc(sizeof(NODO));
		strcpy(nuovo->stringa,parola);
		nuovo->dx=NULL;
		nuovo->sx=NULL;
    }
    return nuovo;
}

void stampa (NODO* Radice){
    if(!Radice){}
    else{
        stampa(Radice->sx);
        printf("%s   ",Radice->stringa);
        stampa(Radice->dx);
    }
}

NODO* Dealloca(NODO *Radice){
      if(!Radice) {      }
      else{
        Radice->sx=Dealloca(Radice->sx);
        Radice->dx=Dealloca(Radice->dx);
        free(Radice);
      }
      return NULL;
}

NODO* StaccaNodo(NODO* Radice,NODO* Padre){
    if(Radice->sx){
        StaccaNodo(Radice->sx,Radice);
    }
    else{
        if(Radice->dx){      //se il nodo minimo ha un nodo destro ,assegno il nodo al ramo sinistro del padre
            Padre->sx=Radice->dx;
        }
        else(){
            Padre->sx=NULL;   //se il nodo minimo non ha figli stacco direttamente il nodo
        }
    }
    return Radice;
}

NODO* CancellaMax(NODO* Radice){
    NODO* temp=NULL;
    if(Radice->sx){
        Radice->sx=CancellaMax(Radice->sx);
        temp=Radice->sx;
    }
    else{
        free(Radice);
    }
    return temp;
}

NODO* RicercaNodo(NODO* Radice,char* parola){
    if(Radice){
        if(strcmp(Radice->stringa,parola)==0){  //devo richiamare stacca nodo(radice->dx,Radice);
            return Radice;
        }
        else if(strcmp(Radice->stringa,parola)>0){
            Radice->sx=RicercaNodo(Radice->sx,parola);
        }
        else if(strcmp(Radice->stringa,parola)<0){
            Radice->dx=RicercaNodo(Radice->dx,parola);
        }
    }
    emichele - Michelelse{
        printf("elemento non trovato\n\n");
        return NULL;
    }
}

NODO* Cancella(NODO* Radice,parola){
    NODO* temp=NULL;
    if(Radice){
        if(strcmp(Radice->stringa,parola)==0){
            if(!Radice->dx && !Radice->sx){ //se il nodo destro ed il nodo sinistro sono nulli
                free(Radice);
                return NULL;
            }
            else if((!Radice->dx && Radice->sx) || (Radice->dx && !Radice->sx)){
                strcpy(Radice->stringa,CercaMax(Radice->dx));
                Radice->dx=CancellaMax(Radice->dx);
                return Radice;
            }
        }
        else if(strcmp(Radice->stringa,parola)>0){
            Radice->sx=Cancella(Radice->sx,parola);
        }
        else if(strcmp(Radice->stringa,parola)<0){
            Radice->dx=Cancella(Radice->dx,parola);
    }
}
    /*if(!Lista){
        printf("Lista terminata\n\n");
        return temp;
    }
    else if (strcmp(Lista->stringa,parola)==0){
        temp=Lista->next;
        free(Lista);
        printf("elemento cancellato\n\n");
        return temp;

    }
    else if(strcmp(Lista->stringa,parola)>0){
        printf("Elemento non trovato");
    }
    else{
        printf("passo al prossimo elemento\n\n");
        Lista->next=Cancella(Lista->next,parola);
        return Lista;
    }
}*/

/*NODO* Duplica(NODO* Lista){
    NODO* nuovo=NULL;
    if(Lista){
        nuovo=(NODO*)malloc(sizeof(NODO));
        strcpy(nuovo->stringa,Lista->stringa);
        nuovo->next=Duplica(Lista->next);
    }
    return nuovo;
}

NODO* Fondi(NODO* Lista1,NODO* Lista2){
    NODO* nuova=NULL;
    if(!Lista1){
        nuova=Duplica(Lista2);
        printf("duplica lista2\n");
    }
    else if(!Lista2){
        nuova=Duplica(Lista1);
        printf("duplica lista1\n");
    }
    else if (Lista1 && Lista2){
        nuova=(NODO*)malloc (sizeof(NODO));
        if(strcmp(Lista1->stringa,Lista2->stringa)>0){
            strcpy(nuova->stringa,Lista2->stringa);
            nuova->next=Fondi(Lista1,Lista2->next);
            printf("inserimento stringa 1\n");
        }
        else if(strcmp(Lista1->stringa,Lista2->stringa)<0){
            strcpy(nuova->stringa,Lista1->stringa);
            nuova->next=Fondi(Lista1->next,Lista2);
            printf("inserimento stringa2\n");
        }
        else if(strcmp(Lista1->stringa,Lista2->stringa)==0){
            strcpy(nuova->stringa,Lista1->stringa);
            nuova->next=Fondi(Lista1->next,Lista2->next);
            printf("parole uguali\n");
        }
    }
    return nuova;
}

NODO* EliminaRange(NODO* Lista1 ,int pari,char* start,char* end){
    NODO* temp=Lista1;
    if(Lista1){
        if(strcmp(Lista1->stringa,start)>0 && strcmp(Lista1->stringa,end)<0){
            if(strlen(Lista1->stringa)%2==0){   //stringa pari
                if(pari){        //condizione pari
                    Lista1->next=EliminaRange(Lista1->next,pari,start,end);
                    temp=Lista1->next;
                    free(Lista1);
                }
                else{
                    Lista1->next=EliminaRange(Lista1->next,pari,start,end);
                }
            }
            else{  //stringa dispari
                if(!pari){       //condizione dispari
                    Lista1->next=EliminaRange(Lista1->next,pari,start,end);
                    temp=Lista1->next;
                    free(Lista1);
                }
                else{
                    Lista1->next=EliminaRange(Lista1->next,pari,start,end);
                }
            }
        }
        else{  //fuori range
            Lista1->next=EliminaRange(Lista1->next,pari,start,end);
        }
    }
    return temp;
}

*/
