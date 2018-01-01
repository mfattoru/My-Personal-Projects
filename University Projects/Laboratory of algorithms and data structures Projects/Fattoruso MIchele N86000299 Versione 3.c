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
NODO* Cancella(NODO* Radice,char* Parola);
NODO* EliminaRange(NODO* Albero ,int pari,char* start,char* end);
NODO* StaccaNodo(NODO* Radice,NODO* Padre);

int main(){
    NODO* Albero=NULL;
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
		printf("5)Cancella da lista tramite parametri\n");
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
                Albero=Cancella(Albero,parola);
                printf("\n\n");
                break;
            case '5':
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
                Albero=EliminaRange(Albero ,pari,start,end);
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
    if(Radice){
        stampa(Radice->sx);
        printf("%s   ",Radice->stringa);
        stampa(Radice->dx);
    }
}

NODO* Dealloca(NODO *Radice){
      if(Radice){
        Radice->sx=Dealloca(Radice->sx);
        Radice->dx=Dealloca(Radice->dx);
        free(Radice);
      }
      return NULL;
}

NODO* StaccaNodo(NODO* Radice,NODO* Padre){
    if(Radice){
        if(Radice->sx){
            return StaccaNodo(Radice->sx,Radice);
        }
        else{
            if(Radice==Padre->sx){      //se il nodo minimo ha un nodo destro ,assegno il nodo al ramo sinistro del padre
                Padre->sx=Radice->dx;
            }
            else{
                Padre->dx=Radice->dx;   //se il nodo minimo non ha figli stacco direttamente il nodo
            }
        }
    }
    return Radice;
}

NODO* Cancella(NODO* Radice,char* parola){
    NODO* temp;
    if(Radice){
        if(strcmp(Radice->stringa,parola)>0){  //parola inserita più piccola della parola attuale
            Radice->sx=Cancella(Radice->sx,parola);
        }
        else if(strcmp(Radice->stringa,parola)<0){    //parola inserita più grande della parola attuale
            Radice->dx=Cancella(Radice->dx,parola);
        }
        else{   //parola trovata
            temp=Radice;
            if(!Radice->dx){   //nodo con un solo sottoalbero
                Radice=Radice->sx;
            }
            else if(!Radice->sx){   //nodo con un slo sottoalbero
                Radice=Radice->dx;
            }
            else{    //nodo con due sottoalberi
                temp=StaccaNodo(Radice->dx,Radice);
                strcpy(Radice->stringa,temp->stringa);
            }
            free(temp);
        }
    }
    return Radice;
}


NODO* EliminaRange(NODO* Albero ,int pari,char* start,char* end){
    NODO* temp=NULL;
    int min,max;
    if(Albero){
        min=strcmp(Albero->stringa,start);
        max=strcmp(Albero->stringa,end);
        if(min>0){   //la stringa attuale è maggiore della stringa start,posso scorrere l'albero destro
            Albero->dx=EliminaRange(Albero->dx,pari,start,end);
        }
        if(max<0){   //la stringa attuale è minore della stringa end,posso scorrere l'albero sinistro
            Albero->sx=EliminaRange(Albero->sx,pari,start,end);
        }
        if(min>0 && max<0){  //parola in range
            if((pari && strlen(Albero->stringa)%2==0) || (!pari && strlen(Albero->stringa)%2!=0)){
                temp=Albero;
                if(!Albero->dx){
                    Albero=Albero->sx;
                }
                else if(!Albero->sx){
                    Albero=Albero->dx;
                }
                else{
                    temp=StaccaNodo(Albero->dx,Albero);
                    strcpy(Albero->stringa,temp->stringa);
                }
                free(temp);
                /*
                Albero=EliminaRange(Albero,pari,start,end);
                dopo aver staccato il nodo dal sottoalbero destro rieffettuo il controllo sul nuovo nodo per sapere se quesrto
                deve essere anch'esso eliminato trovandosi nel range,ma ho optato per l'altra soluzione credendola più efficiente,
                visto che scorrendo per prima tutto l'albero è più probabile che il metodo StaccaNodo venga invocato meno volte
                risparmiando computazione
                */
            }
        }
    }
    return Albero;
}



