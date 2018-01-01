#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "libreria.h"

NODO* Insert(NODO *Old,FNCMP Compare,void* var){
    NODO* nuovo=Old;
    if(Old){
        if(Compare(Old->valore,var)==-1){
            nuovo->dx=Insert(Old->dx,Compare,var);
        }
        else if(Compare(Old->valore,var)==1){
            nuovo->sx=Insert(Old->sx,Compare,var);
        }
        else{
            printf("Valore gia inserito\n");
        }
    }
    else{
        nuovo=(NODO*)malloc(sizeof(NODO));
        nuovo->valore=var;
		nuovo->dx=NULL;
		nuovo->sx=NULL;
    }
    return nuovo;
}

void StampaStr (NODO* Radice){
    if(Radice){
        StampaStr(Radice->sx);
        printf("%s -> ",(char*)Radice->valore);
        StampaStr(Radice->dx);
    }
}

void StampaInt(NODO* Radice){
    if(Radice){
        StampaInt(Radice->sx);
        printf("%d -> ",*((int*)Radice->valore));
        StampaInt(Radice->dx);
    }
}

void StampaFlt(NODO* Radice){
    if(Radice){
        StampaFlt(Radice->sx);
        printf("%f -> ",*((float*)Radice->valore));
        StampaFlt(Radice->dx);
    }
}

NODO* Dealloca(NODO *Radice){
      if(Radice){
        Radice->sx=Dealloca(Radice->sx);
        Radice->dx=Dealloca(Radice->dx);
        free(Radice->valore);
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

NODO* Cancella(NODO* Radice,void* var,FNCMP Compare){
    NODO* temp;
    if(Radice){
        if(Compare(Radice->valore,var)>0){  //parola inserita più piccola della parola attuale
            Radice->sx=Cancella(Radice->sx,var,Compare);
        }
        else if(Compare(Radice->valore,var)<0){    //parola inserita più grande della parola attuale
            Radice->dx=Cancella(Radice->dx,var,Compare);
        }
        else{   //parola trovata
            temp=Radice;
            if(!Radice->dx){   //nodo con un solo sottoalbero
                Radice=Radice->sx;
            }
            else if(!Radice->sx){   //nodo con un solo sottoalbero
                Radice=Radice->dx;
            }
            else{    //nodo con due sottoalberi
                printf("trovato\n");
                temp=StaccaNodo(Radice->dx,Radice);
                free(Radice->valore);
                Radice->valore=temp->valore;
            }
            free(temp);
        }
    }
    return Radice;
}


NODO* EliminaRange(NODO* Albero ,FNCHK Check,void* start,void* end,FNCMP Compare){
    NODO* temp=NULL;
    int min,max,x;
    if(Albero){
        min=Compare(Albero->valore,start); //se la stringa attuale è maggiore di start,min sarà uguale a 1
        max=Compare(Albero->valore,end); //se la stringa attuale è minore di end ,max saràuguale a -1
        if(max<0){   //la stringa attuale è minore della stringa end,posso scorrere l'albero destro
            Albero->dx=EliminaRange(Albero->dx,Check,start,end,Compare);
        }
        if(min>0){   //la stringa attuale è maggiore della stringa start,posso scorrere l'albero sinistro
            Albero->sx=EliminaRange(Albero->sx,Check,start,end,Compare);
        }
        if(min>0 && max<0){  //parola in range
            x=Check(Albero->valore);
            if(x>0){
                temp=Albero;
                if(!Albero->dx){
                    Albero=Albero->sx;
                }
                else if(!Albero->sx){
                    Albero=Albero->dx;
                }
                else{
                    temp=StaccaNodo(Albero->dx,Albero);
                    free(Albero->valore);
                    Albero->valore=temp->valore;
                }
                free(temp);
            }
        }
    }
    return Albero;
}

int CheckPari(int* x){     //restituisce 1 se il numero è pari,zero altrimenti
    int res=0;
    if(*x%2==0){
        res=1;
    }
    return res;
}

int CheckDispari(int* x){     //restituisce 1 se il numero è dispari,zero altrimenti
    int res=0;
    if(*x%2!=0){
        res=1;
    }
    return res;
}

int CheckLungPari(char* x){
    int res=0;
    if(strlen(x)%2==0){
        res=1;
    }
    return res;
}

int CheckLungDispari(char* x){
    int res=0;
    if(strlen(x)%2!=0){
        res=1;
    }
    return res;
}



void PrintInt_iter(int* x){
    printf("%d -> ",*(int*)x);
}

void PrintFloat_iter(float* x){
    printf("%f -> ",*(float*)x);
}

void PrintStr_iter(char* x){
    printf("%s -> ",x);
}
