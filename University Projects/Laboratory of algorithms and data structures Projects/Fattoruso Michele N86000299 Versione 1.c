#include <stdio.h>
#include <string.h>

struct nodo {
    char str[100];
    struct nodo *next;
};

typedef struct nodo* Pnodo;
    
Pnodo inserimento (Pnodo N,char string[]);
void stampa (Pnodo N);
Pnodo crea_nodo(char string[]);
void dealloca(Pnodo N);

int main(){
    Pnodo L=NULL;
    int scelta=0;
    char stringa[100];
    Pnodo T;
    do{
    printf("\n SCEGLI COSA VUOI FARE: \n");
    printf("1) INSERIMENTO NELLA LISTA \n");
    printf("2) STAMPA DELLA LISTA \n");
    printf("3) DEALLOCA LA LISTA \n");
    printf("4) ESCI DAL PROGRAMMA\n");
    printf("\n SCELTA: ");
        scanf("%d",&scelta);
        switch(scelta){
            case 1:
                printf("\n INSERISCI STRINGA \n");
                scanf("%s",&stringa);
                L=inserimento(L,stringa);
                printf("ELEMENTO INSERITO\n");
                break;
            case 2:
                stampa(L);
                printf("LISTA STAMPATA\n");
                break;
            case 3:
                dealloca(L);
                printf("LSTA DEALLOCATA");
                break;
            case 4:
                printf("CIAO !!");
            default:
                printf("SCELTA NON VALIDA\n");
                break;
        }
    }while(scelta != 4);
}

Pnodo crea_nodo(char string[]){
    Pnodo temp;
    temp =(struct nodo*) malloc(sizeof(struct nodo));
    strcpy(temp->str,string); 
    temp->next = NULL;
    return temp;
}

Pnodo inserimento (Pnodo N,char string[]){
    if(N==NULL){
        N=crea_nodo(string);
    }
    else{
        if(strcmp(N->str,string)<0){
            N->next=inserimento(N->next,string);
        }
        else if (strcmp(N->str,string)==0){
            printf("STRINGA GIA INSERITA\n");
        }
        else{
            Pnodo temp = crea_nodo(string);
            temp->next= N;
            N=temp;
        }
    }
    return N;
}

void stampa (Pnodo N){
    if (N==NULL){
        printf("FINE \n");
    }
    else{
        printf("%s",N->str);
        printf(" -> ");
        stampa(N->next);
    }
}

void dealloca(Pnodo N){
    if(N->next != NULL){
        dealloca(N->next);
    }
    free(N);
    
}

        
    
     
