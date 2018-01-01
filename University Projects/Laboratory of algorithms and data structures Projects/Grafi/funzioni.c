#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "funzioni.h"


void InserisciVertice(GRAFO* G,void* nome){
    int i;
    if(G){
        //printf("nodi:%d\n",G->n_nodi);
        //printf("casa3\n");
        if(G->vert){
            //printf("casa2\n");
            if(G->n_nodi%10==0 && G->n_nodi!=0){  //check
                //printf("casa3\n");
                G->vert=(VERTICE*)realloc(G->vert,sizeof(VERTICE)*(G->n_vert+10));
                G->vert[G->n_nodi].valore=nome;
                G->vert[G->n_nodi].eliminato=0;
                G->n_vert+=10;
                G->n_nodi+=1;
                for(i=G->n_nodi;i<G->n_vert;i++){
                    //printf("casa4\n");
                    (G->vert[i]).eliminato=1;
                }
            }
            else{
                for(i=0;i<G->n_vert;i++){
                    //printf("cane\n");
                    if(G->vert[i].eliminato){
                        //printf("cane2\n");
                        G->vert[i].valore=nome;
                        G->vert[i].eliminato=0;
                        G->n_nodi+=1;
                        break;
                    }
                }
            }
        }
        else{
            //printf("casa4\n");
            G->vert=(VERTICE*)malloc(sizeof(VERTICE)*10);
            //printf("casa5\n");
            G->n_vert=10;
            G->vert[0].valore=nome;
            G->vert[0].eliminato=0;
            //printf("casa6\n");
            G->n_nodi+=1;
            for(i=1;i<G->n_vert;i++){
                G->vert[i].eliminato=1;
            }
            //printf("casa7\n");
            //printf("casa8\n");
        }
        G->struttura=G->funzione.insert(G->struttura,G->n_nodi);
        //printf("nodi:%d\n",G->n_nodi);
        //printf("erba2\n");
    }
}



void* ins_matr(void* M, int n_nodi){
    double** matr1=NULL;
    int i,j;
    if(M){
        matr1=(double**)(M);
        if(n_nodi%10==0 && n_nodi!=0){
            //printf("erba\n");
            matr1=(double**)realloc(matr1,sizeof(double*)*(n_nodi+10));
            for(i=0;i<n_nodi;i++){
                matr1[i]=(double*)realloc(matr1[i],sizeof(double)*(n_nodi+10));
            }
            for(i=n_nodi;i<(n_nodi+10);i++){
                matr1[i]=(double*)malloc(sizeof(double)*(n_nodi+10));
            }
            for(j=0;j<(n_nodi+10);j++){
                for(i=n_nodi;i<n_nodi+10;i++){
                    matr1[i][j]=0;
                    matr1[j][i]=0;
                }
            }
            //printf("erba1\n");
        }
    }
    else{
        //printf("albero\n");
        matr1=(double**)malloc(sizeof(double*) * 10);
        //printf("albero2\n");
        for(i=0;i<10;i++){
            matr1[i]=(double*)malloc(sizeof(double)*10);
        }
        //printf("albero1\n");
        for(j=0;j<10;j++){
            for(i=0;i<10;i++){
                matr1[i][j]=0;
            }
        }
    }
    return matr1;
}

void stampa(GRAFO* G){
    int i,j,skip;
    double** matr;
    matr=(double**)G->struttura;
    if(G){
        for(i=0;i<G->n_vert;i++){
            skip=0;
            //printf("I=%d\n",i);
            for(j=0;j<G->n_vert;j++){

                /*if(j==0){
                    printf("vertice: %s\n",(char*)G->vert[i].valore);
                }*/

                if(!G->vert[i].eliminato && !G->vert[j].eliminato){
                    //printf(" J= %d ",j);
                    printf("%5.2f ",matr[i][j]);
                    skip=0;
                }
                else {
                    skip=1;
                }
            }
            if(skip==0){
                printf("\n\n");
            }
        }
    }
    else{
        printf("grafo null");
    }
}

void InserisciArcoOrientato(GRAFO* G,int x,int y,double peso){
    double** matr;
    if(G){
        matr=(double**)G->struttura;
        if(x<G->n_vert && y<G->n_vert && G->vert[x].eliminato!=1 && G->vert[y].eliminato!=1){
            matr[x][y]=peso;
        }
    }
}

void InserisciArco(GRAFO* G,int x,int y,double peso){
    double** matr;
    if(G){
        matr=(double**)G->struttura;
        if(x<G->n_vert && y<G->n_vert && G->vert[x].eliminato!=1 && G->vert[y].eliminato!=1){
            matr[x][y]=peso;
            matr[y][x]=peso;
        }
    }
}

void CancellaArco(GRAFO* G,int x,int y){
    double** matr;
    if(G){
        matr=(double**)G->struttura;
        if(x<G->n_vert && y<G->n_vert && G->vert[x].eliminato!=1 && G->vert[y].eliminato!=1){
            matr[x][y]=0;
            matr[y][x]=0;
        }
    }
}

void CancellaArcoOrientato(GRAFO* G,int x,int y){
    double** matr;
    if(G){
        matr=(double**)G->struttura;
        if(x<G->n_vert && y<G->n_vert && G->vert[x].eliminato!=1 && G->vert[y].eliminato!=1){
            matr[x][y]=0;
        }
    }
}

void CancellaVertice(GRAFO* G,void* key){
    int i=0;
    for(i=0;i<G->n_vert;i++){
        printf("i: %d",i);
        if(!G->vert[i].eliminato){
            printf("key: %s \t vertice: %s\n",(char*)key,G->vert[i].valore);
            if(G->funzione.ConfrontaValore( G->vert[i].valore,key) ){
                printf("uguali!\n");
                G->vert[i].eliminato=1;
            }
        }
    }
}

int ConfrontaDouble(double x,double y){
    int res;
    if(x==y){
        res=0;
    }
    else{
         res=1;
    }
    return res;
}

char* GeneraStringa (){
    int i;
    char *array;
    array=malloc(sizeof(char)*11);
    //srand (time(NULL));
    for (i=0; i<10; ){
        array[i++] = (char) ((rand() % 26)+ 65);
    }
    array[i]='\0';
    printf("generata: %s \n",array);
    return array;
}


int ConfrontaStringa(char* x,char* y){
    int res;
    if(strcmp(x,y)){
        res=0;
    }
    else{
         res=1;
    }
    return res;
}

void Trasposta(GRAFO* G){
    int i,j,skip;
    double** matr;
    matr=(double**)G->struttura;
    if(G){
        for(i=0;i<G->n_vert;i++){
            //printf("I=%d\n",i);
            for(j=0;j<G->n_vert;j++){
                skip=0;
                /*if(j==0){
                    printf("vertice: %s\n",(char*)G->vert[i].valore);
                }*/

                if(!G->vert[i].eliminato && !G->vert[j].eliminato){
                    //printf(" J= %d ",j);
                    printf("%5.2f ",matr[j][i]);
                    skip=0;
                }
                else {
                    skip=1;
                }
            }
            if(skip==0){
                printf("\n\n");
            }
        }
    }
    else{
        printf("grafo null");
    }
}

void BFS(GRAFO* G,VERTICE* V){
    PILA* pila;
    //inizializza tutti i vertici del grafo a bianco,distanza a -infinito

    //inizializza il vertice V a grigio,distanza a 0

    //accoda V

    //finchè la coda non diventa vuota:
        //preleva la testa della coda
        //analizza tutti gli adiacenti all'elemento estratto
            //se l'elemento è bianco posta il colore a grigio,aggiorna il predecessore
            //accoda l'elemento
        //cancella la testa della coda ponendo l'elemento con colore uguale a nero
}
