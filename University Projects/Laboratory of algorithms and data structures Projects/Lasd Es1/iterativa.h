#include "pila.h"

void StampaIter(NODO* radice,FNPRINT stampa);
NODO* InsertIter(NODO *Old,FNCMP Compare,void* var);
NODO* DeallocaIter(NODO* radice,FNPRINT stampa);
NODO* cancella(NODO* nodo);

NODO* InsertIter(NODO *Old,FNCMP Compare,void* var){
    int NonInserire=0;
    NODO* nodo;
    nodo=(NODO*)malloc(sizeof(NODO));
    nodo->valore=var;
    nodo->dx=NULL;
    nodo->sx=NULL;
    NODO* temp=NULL;
    NODO* temp2=Old;
    while(temp2){
        temp=temp2;
        if(Compare(temp2->valore,var)==-1){
            temp2=temp2->dx;}
        else if(Compare(temp2->valore,var)==1){
            temp2=temp2->sx;
        }
        else{
            printf("Valore gia inserito\n");
            NonInserire=1;
            break;
        }
    }
    if(NonInserire!=1){
        if(!temp){  //se il nodo attuale è vuoto creo un nuovo nodo
            Old=nodo;
        }
        else if(Compare(temp->valore,nodo->valore)==1){
            temp->sx=nodo;
        }
        else{
            temp->dx=nodo;
        }
    }
    return Old;
}

void StampaIter(NODO* radice,FNPRINT stampa){
    PILA* nuova=NULL;
    NODO* temp=NULL;
    int uscita=1;
    do{
        if(radice){ //se trovo un nodo non nullo lo inserisco nella mia pila e poi continuo ad analizzare il sottoalbero sinistro
            nuova=InsertTesta(nuova,radice);
            radice=radice->sx;
        }
        else { //se il nodo è nullo,risalgo nell'albero ed analizzo il sottoalbero destro
            if(vuota(nuova)){
                temp=PrelevaTesta(nuova);
                stampa(temp->valore);  //mi trovo in fase di risalita,stampo il valore contenuto nella pila
                radice=temp->dx;
                nuova=CancellaTesta(nuova);
            }
            else{
                uscita=0;
            }
        }
    }while(uscita);
}

NODO* DeallocaIter(NODO* radice,FNPRINT stampa){
    PILA* nuova=NULL;
    NODO* temp=NULL;
    int uscita=1;
    do{
        if(radice){ //se trovo un nodo non nullo lo inserisco nella mia pila e poi continuo ad analizzare il sottoalbero sinistro
            nuova=InsertTesta(nuova,radice);
            radice=radice->sx;
        }
        else {  //se il nodo è nullo,risalgo nell'albero ed analizzo il sottoalbero destro
            if(vuota(nuova)){
                temp=PrelevaTesta(nuova);
                radice=temp->dx;
                temp=cancella(temp);
                nuova=CancellaTesta(nuova);
            }
            else{
                uscita=0;
            }
        }
    }while(uscita);
    return radice;
}

NODO* cancella(NODO* nodo){
    nodo->sx=NULL;
    nodo->dx=NULL;
    free(nodo->valore);
    free(nodo);
    return nodo;
}

NODO* CancellaIter(NODO* radice,FNCMP compare,void* key){
    NODO* temp=NULL;
    NODO* rad=radice;
    NODO* padre=NULL;
    int uscita=1;
    do{
        if(radice){
            if(compare(radice->valore,key)>0){
                padre=radice;
                radice=radice->sx;
            }
            else if(compare(radice->valore,key)<0){
                padre=radice;
                radice=radice->dx;
            }
            else{
                temp=radice;
                if(!radice->dx){   //nodo con un solo sottoalbero
                    if(radice==padre->sx){
                        padre->sx=radice->sx;
                    }
                    else if(radice==padre->dx){
                        padre->dx=radice->sx;
                    }
                }
                else if(!radice->sx){   //nodo con un solo sottoalbero
                    if(radice==padre->sx){
                        padre->sx=radice->dx;
                    }
                    else if(radice==padre->dx){
                        padre->dx=radice->dx;
                    }
                }
                else{    //nodo con due sottoalberi
                    temp=StaccaNodo(radice->dx,radice);
                    free(radice->valore);
                    radice->valore=temp->valore;
                }
                free(temp);
                uscita=0;
            }
        }
        else{
            uscita=0;
        }
    }while(uscita);
    return rad;
}

NODO* CancellaRangeIter(NODO* radice ,FNCHK Check,void* start,void* end,FNCMP compare){
    PILA *pila=NULL;
    NODO* temp,*padre=NULL;
    NODO *curr=radice,*last=NULL,*rad=radice;
    while(pila!=NULL || curr != NULL){
        if (curr!=NULL){  //discesa a sinistra
            pila=InsertTesta(pila,curr);
            if(compare(curr->valore,start)>0){ //se la radice è minore di start,non scorro a sinistra
                curr=curr->sx;
            }
            else if(compare(curr->valore,end)<0){
                curr=curr->dx;
            }
        }
        else{ //risalita lungo l'albero
            curr=PrelevaTesta(pila);

            if(curr->dx==NULL || curr->dx==last){ //risalita da destra

                pila=CancellaTesta(pila);
                if(vuota(pila)){
                    padre=PrelevaTesta(pila);
                }
                else{
                    padre=NULL;
                }
                pila=InsertTesta(pila,curr);

                if(compare(curr->valore,end)<0 && compare(curr->valore,start)>0){
                    printf("Corrente: %d\n",*(int*)curr->valore);

                    temp=curr;                                 //INIZIO CANCELLAZIONE

                    if(!curr->dx){   //nodo con un solo sottoalbero
                        printf("trovato senza destro\n");
                        if (padre==NULL){   //cancellazione radice con sostituzione con il sottoalbero sinistro
                            printf("rad=NULL\n");
                            rad=curr->sx;
                            curr=curr->sx;
                        }
                        else if(curr==padre->sx){
                            padre->sx=curr->sx;
                        }
                        else if(curr==padre->dx){
                            padre->dx=curr->sx;
                        }

                    }
                    else if(!curr->sx){   //nodo con un solo sottoalbero
                        printf("trovato senza sinistro\n");
                        if (padre==NULL){   //cancellazione radice e sostituzione con il sottoalbero destro
                            printf("rad=NULL2\n");
                            rad=curr->dx;
                            curr=curr->dx;
                        }
                        else if(curr==padre->sx){
                            padre->sx=curr->dx;
                        }
                        else if(curr==padre->dx){
                            padre->dx=curr->dx;
                        }

                    }
                    else{    //nodo con due sottoalberi
                        printf("trovato con due\n");
                        temp=StaccaNodo(curr->dx,curr);
                        free(curr->valore);
                        curr->valore=temp->valore;
                    }
                    free(temp);
                }
                last=curr;
                pila=CancellaTesta(pila);
                curr=NULL;
            }
            else{
                curr=curr->dx; //risalita da sinistra
            }
        }
    }
    return rad;
}


