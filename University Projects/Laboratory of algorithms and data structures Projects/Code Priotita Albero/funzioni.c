#include "header.h"
#include <stdio.h>
#include <malloc.h>


void swap(HEAP* primo,HEAP* secondo){
    HEAP temp;
    /*temp=secondo;
    if(secondo==secondo->padre->dx){  //se secondo è nodo destro di primo
        secondo->sx=primo->sx;
        secondo->dx=primo;
    }
    else if(secondo==secondo->padre->sx){   //se secondo è nodo sinistro di primo
        secondo->dx=primo->dx;
        secondo->sx=primo;
    }
    secondo->padre=primo->padre;
    primo->padre=secondo;
    primo->sx=temp->sx;
    primo->dx=temp->dx;*/
    temp.priorita=primo->priorita;
    temp.elem=primo->elem;
    primo->priorita=secondo->priorita;
    primo->elem=secondo->elem;
    secondo->priorita=temp.priorita;
    secondo->elem=temp.elem;
}

void heapify(HEAP *H){
    HEAP *temp=NULL;
    if(H){
        if(H->sx && H->sx->priorita > H->priorita){
            temp=H->sx;
        }
        else {
            temp=H;
        }
        if(H->dx && (H->dx->priorita > temp->priorita)){
            temp=H->dx;
        }
        if (temp!=H){
            swap(H,temp);
            heapify(temp);
        }
    }
}

HEAP* Massimo(HEAP* H){
    if(!H){
        printf("ALBERO VUOTO\n");
        return NULL;
    }
    else{
        return H;
    }
}

HEAP* EstraiMassimo(HEAP* H){
    HEAP* temp;
    temp=malloc(sizeof(HEAP));
    HEAP* canc;
    int trovato=0;
    if(!H){
        printf("ALBERO VUOTO\n");
    }
    else{

        temp->dx=H->dx;  //copio i valori che mi servono...mda creare una finzione che copia i dati
        temp->sx=H->sx;
        temp->ultimo=H->ultimo;  //salvato indirizzo di memoria dell'ultimo elemento
        temp->elem=H->elem;
        temp->priorita=H->priorita;
        temp->padre=H->padre;

        if(H->sx && H->dx){   //albero con due sottoalberi

            //TROVO IL NUOVO ULTIMO
            if(H->ultimo->padre->dx==H->ultimo){  //ultimo è sottoalbero destro
                H->ultimo->padre->dx=NULL;
                H->ultimo=H->ultimo->padre->sx;    //aggiornato ultimo
            }
            else{
                H->sx=temp->sx;
                H->dx=temp->dx;
                while(trovato==0){
                    if(H->ultimo->padre && H->ultimo->padre->dx == H->ultimo){  //risalita da dx
                        H->ultimo=H->ultimo->padre->sx;
                        while(H->ultimo->dx){
                            H->ultimo=H->ultimo->dx;
                        }
                        trovato=1;
                    }
                    else if(H->ultimo->padre && H->ultimo->padre->sx==H->ultimo){ //risalita da sx
                        H->ultimo=H->ultimo->padre;
                    }
                    else if(H->ultimo->padre==NULL){
                        while(H->ultimo->dx!=NULL){
                            H->ultimo=H->ultimo->dx;
                        }
                        trovato=1;
                    }
                }

                //H->padre=NULL;

                temp->ultimo->padre->sx=NULL;
            }
            H->elem=temp->ultimo->elem;   //adesso H punta al vecchio ultimo,ora devo ricollegare la testa dell'albero
            H->priorita=temp->ultimo->priorita;

        }
        else if(H->sx){   //albero con solo il sottoalbero sinistro
            canc=H->sx;
            H->elem=H->sx->elem;
            H->priorita=H->sx->priorita;
            H->dx=H->sx->dx;
            H->sx=H->sx->sx;
            H->padre=NULL;
            free(canc);
        }
        else{
            /*H->elem=NULL;
            H->priorita=NULL;
            H->dx=NULL;
            H->sx=NULL;
            H->padre=NULL;*/  //dovrei o cambiare strutturazione oppure passare un puntatore a puntatore per mettere a null il puntatore reale della funzione
        }
        heapify(H);
    }
    return temp;
}

void BuildHeap(HEAP *H){
    if(H){

        BuildHeap(H->sx);
        BuildHeap(H->dx);
        heapify(H);
    }
}

void DecreaseKey(HEAP* H,int val){
    if(val>H->priorita){
        printf("PRIORITA MAGGIORE DI QUELLA ATTUALE\n");
    }
    else{
        H->priorita=val;
        heapify(H);
    }
}

void IncreaseKey(HEAP *H,int val){
    if(val<H->priorita){
        printf("PRIORITA MINORE DI QUELLA ATTUALE\n");
    }
    else{
        H->priorita=val;
        heapify(H->padre);
    }
}

HEAP* Inserimento(HEAP *H,int prio,void* key){
    HEAP *temp;
    int trovato=0;
    temp=malloc(sizeof(HEAP));
    temp->priorita=prio;
    temp->elem=key;
    temp->padre=NULL;
    temp->sx=NULL;
    temp->dx=NULL;
    temp->ultimo=NULL;
    if(!H){
        H=temp;
        H->ultimo=temp;
    }
    else{
        if(!H->sx){
            H->sx=temp;
            H->sx->padre=H;
            H->ultimo=temp;
        }
        else if(H->ultimo->padre && H->ultimo==H->ultimo->padre->sx){
            temp->padre=H->ultimo->padre;
            H->ultimo->padre->dx=temp;
            H->ultimo=temp;
        }
        else{
            while(trovato==0){
                if(H->ultimo->padre && H->ultimo->padre->dx == H->ultimo){  //risalita da dx
                    H->ultimo=H->ultimo->padre;
                }
                else if(H->ultimo->padre && H->ultimo->padre->sx==H->ultimo){ //risalita da sx
                    H->ultimo=H->ultimo->padre->dx;
                    while(H->ultimo->sx){
                        H->ultimo=H->ultimo->sx;
                    }
                    trovato=1;
                }
                else if(H->ultimo->padre==NULL){
                    while(H->ultimo->sx!=NULL){
                        H->ultimo=H->ultimo->sx;
                    }
                    trovato=1;
                }
            }
            H->ultimo->sx=temp;
            temp->padre=H->ultimo;
            H->ultimo=H->ultimo->sx;
        }
    }
    return H;
}

HEAP* DeleteKey(HEAP* H,HEAP* Rad){
    HEAP* temp;
    int trovato=0;
    temp=malloc(sizeof(HEAP));
    if(H && Rad){
        if(H->sx && H->dx){  //albero con due sottoalberi
            //copio i valori che mi servono...mda creare una finzione che copia i dati

            temp->ultimo=Rad->ultimo;  //salvato indirizzo di memoria dell'ultimo elemento
            temp->elem=H->elem;
            temp->priorita=H->priorita;
            temp->padre=H->padre;
            if(Rad->ultimo->padre && Rad->ultimo->padre->dx==Rad->ultimo){  //ultimo è sottoalbero destro
                Rad->ultimo->padre->dx=NULL;
                Rad->ultimo=Rad->ultimo->padre->sx;    //aggiornato ultimo
            }
            else{
                while(trovato==0){
                    if(Rad->ultimo->padre && Rad->ultimo->padre->dx == Rad->ultimo){  //risalita da dx
                        Rad->ultimo=Rad->ultimo->padre->sx;
                        while(Rad->ultimo->dx){
                            Rad->ultimo=Rad->ultimo->dx;
                        }
                        trovato=1;
                    }
                    else if(Rad->ultimo->padre && Rad->ultimo->padre->sx==Rad->ultimo){ //risalita da sx
                        Rad->ultimo=Rad->ultimo->padre;
                    }
                    else if(Rad->ultimo->padre==NULL){
                            while(Rad->ultimo->dx!=NULL){
                            Rad->ultimo=Rad->ultimo->dx;
                        }
                        trovato=1;
                    }
                }
                temp->ultimo->padre->sx=NULL;

            }
            H->elem=temp->ultimo->elem;   //adesso H punta al vecchio ultimo,ora devo ricollegare la testa dell'albero
            H->priorita=temp->ultimo->priorita;
            free(temp->ultimo);

        }
        else if(H->sx){  //albero con solo il sottoalbero sinistro
            if(H->padre && H->padre->dx==H){
                H->padre->dx=H->sx;
                H->sx->padre=H->padre;
            }
            else if(H->padre && H->padre->sx==H){
                H->padre->sx=H->sx;
                H->sx->padre=H->padre;
            }
            else{
                Rad=H->sx;
            }
            free(H);
        }
        else{
            free(H);
            Rad=NULL;
        }
        if(Rad!=NULL){
            heapify(Rad);
        }
    }
    return Rad;
}

void stampa(HEAP* H){
    if(H){
        printf("%d - %d -> ",H->priorita,H->elem);
        stampa(H->sx);
        stampa(H->dx);

    }
}
