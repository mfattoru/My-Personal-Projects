#include <stdio.h>
#include "grafi.h"
#include <stdlib.h>

/******************************************************************************************
 FUNZIONI GENERICHE
 ******************************************************************************************/

//-------------------------legge grafo da file----------------------------------------
void leggi_grafo(GRAFO* grafo, char* nome_file){
  if(grafo){
    //printf("fatto\n");        
    leggi_vertici(nome_file, grafo);
    leggi_archi(nome_file, grafo);
  }
}

//-----------------------legge e inserisce i vertici------------------------------------

void leggi_vertici(char* nome_file,GRAFO* grafo){
  FILE* file;
  char c;
  int i = 0, n = 0, j = 0;
  char* nome_nodo = NULL;
  if((file = fopen(nome_file,"r")) == NULL){
    printf("Errore apertura file\n");
  }
  else{
    getc(file);  
    fscanf(file,"%d",&n);  //lettura numero vertici
    getc(file);
    printf("%d\n", n);
    for(j = 0; j < n; j++){
      nome_nodo = (char*)malloc(sizeof(char));                               
      while((c = getc(file))!= '-'){
        nome_nodo = (char*)realloc(nome_nodo,(i+1)*sizeof(char));
        nome_nodo[i] = c;
        i++;
      }
      nome_nodo = (char*)realloc(nome_nodo,(i+1)*sizeof(char));
      nome_nodo[i] = '\0';
      i = 0;
      ins_vert(grafo, nome_nodo);
      while(((c = getc(file)) != ';') );  
    }
    fclose(file);
  }
}

//--------------------------------------------------------------------------------------

//-------------------legge e inserisce gli archi----------------------------------------

void leggi_archi(char* nome_file,GRAFO* grafo){
  FILE* file;
  char c;
  double peso;
  int i = 0,j = 0, k = 0;
  char *nome_nodo = NULL;
  if((file = fopen(nome_file,"r")) == NULL){
    printf("Errore apertura file\n");
  }
  else{
    while( (c = getc(file)) != '.' ){
      ungetc(c, file);
      while((c = getc(file))!= '>');
      do{
        if((c = getc(file)) == '('){
          fscanf(file, "%lf", &peso);
          printf("%f\n", peso);
          getc(file);
        }
        else{
          peso = 1;
          ungetc(c,file);
        }
        while(((c = getc(file)) != ';') && (c != '(') && c!= ' '){
          nome_nodo = (char*)realloc(nome_nodo,(i+1)*sizeof(char));
          *(nome_nodo + i) = c;
          i++;
        }
        nome_nodo = (char*)realloc(nome_nodo,(i+1)*sizeof(char));
        *(nome_nodo + i) = '\0';
        if(c == '(')
          ungetc(c,file);
        for(k = 0; k < grafo->n_vet; k++){
                        
          if(grafo->vert[k].eliminato == 0 && strcmp(grafo->vert[k].id ,nome_nodo) == 0 )
            grafo->funzioni.ins_arco(grafo, j , k, peso);
        }
        i = 0;
      }while( c != ';');
      j++;
    }
    fclose(file);
  }
}

//--------------------------------------------------------------------------------------




//------------------ inserimento di un nuovo vertice nel grafo---------------------------
void ins_vert(GRAFO* G, void* newid){
  int i = 0, j = 0;
  if(G){
    if(G->vert){
      /*l'array dei vertici è gia allocato allora, se necessario, provvedo 
      al ridimensionamento dell'array, all'inserimento del nuovo vertice
      e all'inizializzazione dei nuovi vertici ponendo eliminato = 1 */ 
      if(G->n_nodi != 0 && G->n_nodi%10 == 0){
        G->vert = (VERTICE*)realloc(G->vert, sizeof(VERTICE) * (G->n_nodi + 10) );
        G->vert[G->n_nodi].id = newid;
        G->vert[G->n_nodi].eliminato = 0;
        G->n_vet += 10;
        for(i = G->n_nodi +1; i < G->n_vet; ++i)
          G->vert[i].eliminato = 1;
        ++G->n_nodi; 
      }
      else{
        for(i = 0; i < G->n_vet; ++i){
          if(G->vert[i].eliminato){
            G->vert[i].eliminato = 0;
            G->vert[i].id = newid;
            ++G->n_nodi;
           break;
          }
        }
      }
    }
    else{
      /*l'array dei vertici non è allocato e quindi provvedo all'allocazione,
      all'inserimento del vertice e all'inizializzazione 
      di tutti i vertici ponendo eliminato = 1  */
      G->vert = (VERTICE*)malloc(sizeof(VERTICE) * 10);
      G->vert[0].eliminato = 0;
      G->vert[0].id = newid;
      G->n_vet = 10;
      for(i = 1 ; i < G->n_vet; ++i)
        G->vert[i].eliminato = 1;
      ++G->n_nodi;
    }
    /* dopo l'inserimento del vertice richiamo la funzione
    specifica per la struttura utilizzata che provvede all'adattamento
    della stessa in seguito all'inserimento */
    G->struttura = (G->funzioni).insVert(G->struttura, G->n_vet);
  }
}

//------------------------------------------------------------------------------------------------

//------------cancellazione di un vertice da un grafo----------------------------------------------
void canc_vert(GRAFO* G, int i){
  if(G && G->vert){
    if(i < G->n_vet && G->vert[i].eliminato == 0){
      /*se il vertice non è gia stato eliminato allora 
      lo elimino e modifico la struttura */
      G->vert[i].eliminato = 1;
      G->funzioni.cancVert(G, i);
    }
  }
}

//-------------------------------------------------------------------------------------------------


//----------------DFS-----------------------------------------------------------------------------
void DFS( GRAFO* G, int* pred){
  int i = 0;
  if(G && G->vert){
    /*inizializzazione del grafo*/
    for(i = 0; i < G->n_vet; ++i){
      if(G->vert[i].eliminato == 0 ){
        strcpy(G->vert[i].colore, "bianco");
        pred[i] = -1;
      }
    }
    for(i = 0; i < G->n_vet; ++i){
      if(G->vert[i].eliminato == 0 && strcmp(G->vert[i].colore, "bianco") == 0){
        G->funzioni.DFS_visita(G, i , pred);
      }
    }
  }
}

//-------------------------------------------------------------------------------------------------


//----------------- ricerca percorso minimo dal vertica start al vertice end ----------------------
void percorso_min(GRAFO* G, int start, int end){
  int *pred, i;
  if(G && start < G->n_vet && end < G->n_vet){
    if(G->vert[start].eliminato == 0 && G->vert[end].eliminato == 0){
      pred = (int*)malloc(sizeof(int) * G->n_vet);
      for(i = 0; i < G->n_vet; ++i)
        pred[i] = -1;
      G->funzioni.BFS(G, start, pred);
      stampaPercorso(start, end, pred);
    }
  }
}

//-------------------------------------------------------------------------------------------------


//------------------------stampa del percorso da start a end --------------------------------------
void stampaPercorso(int start, int end, int* pred){
  if(start == end){
    printf("%d -> ", start);
  }
  else if(pred[end] < 0){
    printf("non esiste un percorso tra %d e %d", start, end);
  }
  else{
    stampaPercorso(start, pred[end], pred);
    printf("%d -> ", end);
  }
}

//-------------------------------------------------------------------------------------------------


//-------------------------verifica aciclicità----------------------------------------------------
int aciclico( GRAFO* G){
  int i = 0, ris = 1;
  if(G && G->vert){
    /*inizializzazione del grafo*/
    for(i = 0; i < G->n_vet; ++i){
      if(G->vert[i].eliminato == 0 ){
        strcpy(G->vert[i].colore, "bianco");
      }
    }
    for(i = 0; i < G->n_vet; ++i){
      if(G->vert[i].eliminato == 0 && strcmp(G->vert[i].colore, "bianco") == 0){        
        ris = G->funzioni.aciclico_visita(G, i);
        if (ris == 0)     // se trova un cilo non c'è bisogno che 
          break;          // esamini gli altri nodi
      }
    }
  }
  return ris;
}

//-------------------------------------------------------------------------------------------------

//---------------Gestisce la scrittura su file del grafo in base alla struttura dati utilizzata---------
void InserimentoFile(GRAFO* G,char* NomeFile){
    int cont=0,i=0,j=0;
    FILE *fd;
    if(G && G->vert){
        fd = fopen(NomeFile, "w");
        for(i = 0; i < G->n_vet; ++i){
            if(G->vert[i].eliminato == 0)
        	 cont++;
        }
        if (cont > 0){    //se ho almeno un vertice
            fprintf(fd,"(%d)",cont);   //inserisci numero di vertici del grafico
            for(i = 0; i < G->n_vet; ++i){
	            if(G->vert[i].eliminato==0){ //se l'eleemnto non è stato eliminato:
	                fprintf(fd,"%s->",G->vert[i].id);  //inserisci nome del vertice nel file
	                G->funzioni.InsFile(G,fd,i);
                }
            }
        }
        fprintf(fd,".");
    }
    fclose(fd);
}



//-------------------------------------------------------------------------------------------


/******************************************************************************************
 FUNZIONI PER LA GESTIONE DI UNA MATRICE DI ADIACENZA
 ******************************************************************************************/

//----------------------inizializzazione matrice di adiacenza----------------------------------
GRAFO* init_matr(){
  GRAFO* grafo = (GRAFO*)malloc(sizeof(GRAFO));
  grafo->n_nodi = 0;
  grafo->n_vet = 0;
  grafo->struttura = NULL;
  grafo->vert = NULL;
  grafo->funzioni.insVert = &ins_vert_matr;
  grafo->funzioni.ins_arco = &ins_arco_matr;
  grafo->funzioni.cancVert = &canc_vert_matr;
  grafo->funzioni.canc_arco = &canc_arco_matr;
  grafo->funzioni.BFS = &BFS_matr;
  grafo->funzioni.DFS_visita = &DFS_visita_matr;
  grafo->funzioni.stampa = &stampa_matr;
  grafo->funzioni.aciclico_visita = &aciclico_matr;
  grafo->funzioni.cambia_rap = &MatrToList;
  grafo->funzioni.trasposto = &trasposto_matr;
  grafo->funzioni.InsFile = &ModFileMatrice;
  return grafo;
}


//--------------------------------------------------------------------------------------------

//----------------------inserimento di un nuovo vertice in una matrice-----------------------------
void* ins_vert_matr(void* M, int n_nodi){
  int i, j;
  double** matr;
  if(M){
    /*se la matrice è allocata provvedo, se necessario a ridimensionarla e
    a inizializzare i nuovi elementi a 0 */
    matr = (double**)(M);
    if(n_nodi != 0 && n_nodi%10 == 0){
      matr = (double**)(realloc(matr, sizeof(double*) * (n_nodi + 10) ));
      for(i=0; i < n_nodi; ++i){
        matr[i] = (double*)(realloc(matr[i], sizeof(double) * (n_nodi + 10) ));
      }
      for(i; i < n_nodi + 10; ++i){
        matr[i] = (double*)malloc( sizeof(double) * (n_nodi + 10) );
      }
      for(j = 0; j < 10; ++j){  
        for(i = 0; i < n_nodi + 10; ++i){
          matr[i][n_nodi + j] = 0;
          matr[n_nodi + j][i] = 0;
        }
      }
    }
  }
  else{
    /*se la matrice non è allocata allora la alloco e 
    inizializzo tutti i suoi elementi a 0 */
    matr = (double**)malloc(sizeof(double*) * 10 );
    for(i = 0; i < 10; ++i){
      matr[i] = (double*)malloc( sizeof(double) * 10 );  
    }
    for(j = 0; j < 10; ++j){  
      for(i = 0; i < 10; ++i){
        matr[i][j] = 0;
      }
    }
  }
  return matr;
}  

//-------------------------------------------------------------------------------------------------

//------------- funzione di stampa della matrice di adiacenza--------------------------------------
void stampa_matr(GRAFO* G){
  int i, j, cont = 0, max = 0;
  double **matr;
  matr = (double**)G->struttura;
  for(i = 0; i < G->n_vet; ++i){
    if(G->vert[i].eliminato == 0)
      max = i;
  }
  /*scorro gli elementi della matrice*/
  for(i = 0; i <= max; ++i){
    for(j = 0; j <= max; ++j){
      printf("%4.2f - ", matr[i][j]);
    }
    printf("\n");
    if(cont == (G->n_nodi * G->n_nodi))
      break;
  }
}

//-------------------------------------------------------------------------------------------------

//------------------------inserimento di un arco in una matrice------------------------------------
void ins_arco_matr(GRAFO* G, int a, int b, double peso){
  double **matr;
  if(G){
    /*se il grafo è allocato controllo che gli indici non siano troppo grandi
    e che i vertici corrispondenti non siano stati eliminati */
    if(a < G->n_vet && b < G->n_vet && G->vert[a].eliminato == 0 && G->vert[b].eliminato == 0){
      matr = G->struttura;
      matr[a][b] = peso;
    }
  }
} 

//-------------------------------------------------------------------------------------------------

//---------------cancellazione di un arco da matrice di adiacenza----------------------------------
void canc_arco_matr(GRAFO* G, int a, int b){
  double **matr;
  if(G){
    /*se il grafo è allocato controllo che gli indici non siano troppo grandi
    e che i vertici corrispondenti non siano stati eliminati */
    if(a < G->n_vet && b < G->n_vet && G->vert[a].eliminato == 0 && G->vert[b].eliminato == 0){
      matr = G->struttura;
      matr[a][b] = 0;
    }
  }
}


//-----------------cancellazione di un vertice dalla matrice di adiacenza--------------------------
void canc_vert_matr(GRAFO* G, int ind){
  int i = 0;
  double **matr;
  if(G && G->struttura){
    matr = G->struttura;
    for(i = 0; i < G->n_vet; ++i){
      matr[ind][i] = 0;
      matr[i][ind] = 0;
    }
  }
}

//-------------------------------------------------------------------------------------------------

//--------------------------calcolo del grafo trasposto su matrice di adiacenza--------------------
void trasposto_matr(GRAFO* G ){
  int i, j;
  double **matr, **trasp;
  if(G && G->struttura){
    matr = G->struttura;
    
    
    trasp = (double**)malloc(sizeof(double*) * G->n_vet);
    for(i = 0; i < G->n_vet; ++i){                                 //alloco la matrice trasposta
      trasp[i] = (double*)malloc(sizeof(double) * G->n_vet);
    }
    
    
    for(i = 0; i < G->n_vet; ++i){
      for(j = 0; j < G->n_vet; ++j){
        trasp[i][j] = matr[j][i];               //riempio la matrice trasposta
      }
    }
    G->struttura = (void*)trasp;
    
    
    free(matr);                 //dealloco la vecchia matrice
  }
}
//-------------------------------------------------------------------------------------------------


//-----------------------BFS- visita in ampiezza con riempimento dell'array dei predecessori----------------------------------
void BFS_matr(GRAFO* G, int s, int* pred){
  STACK* coda = NULL;
  double** matr;
  int i, u, cont = 0;
  /*controllo che il grafo e l'array dei predecessori esistano
   e che il vertice di partenza non sia stato eliminato */
  if(G && pred && s < G->n_vet && G->vert[s].eliminato == 0){
    matr = G->struttura;
    /*i vertici non sono in coda e li inizializzo 
    tutti al colore bianco */
    for(i = 0; i < G->n_vet; ++i){
      if(i != s && G->vert[i].eliminato == 0){
        strcpy(G->vert[i].colore, "bianco");
      }
    }
    /*quando un vertice va in coda diventa grigio */
    strcpy(G->vert[s].colore, "grigio");
    pred[s] = -1;
    coda = accoda(coda, s);
    while(vuoto(coda) != 1){
      u = pop(coda);
      cont = 0;
      /*scorro i vertici adiacenti ad "u" e se sono bianchi li metto in coda */
      for(i = 0; i < G->n_vet; ++i){
        if(G->vert[i].eliminato == 0 && matr[u][i] > 0){
          ++cont;
          if(strcmp(G->vert[i].colore, "bianco") == 0){
            strcpy(G->vert[i].colore, "grigio");
            pred[i] = u;
            accoda(coda, i);
          }
          if(cont == G->n_nodi)
            break;
        }
      }
      /*finita la visita di "u" posso toglierlo dalla coda e colorarlo di nero */
      coda = del_testa(coda);
      strcpy(G->vert[u].colore, "nero");
    }
  }
}

//--------------------------------------------------------------------------------------------------





//------------DFS_visita per matrice---------------------------------------------------------------
void DFS_visita_matr( GRAFO* G, int v , int* pred){
  int i = 0;
  double** matr;
  if(G && pred){
    strcpy(G->vert[v].colore, "grigio");
    matr = G->struttura;
    for(i = 0; i < G->n_vet; ++i){
      if(G->vert[i].eliminato == 0 && strcmp(G->vert[i].colore, "bianco") == 0 && matr[v][i] > 0){
        pred[i] = v;
        DFS_visita_matr(G, i, pred);
      }
    }
    strcpy(G->vert[v].colore, "nero");
  } 
}

//------------------------------------------------------------------------------------------------



//------------verifica aciclicità per matrice---------------------------------------------------------------
int aciclico_matr( GRAFO* G, int v){
  int i = 0, ris = 1;
  double** matr;
  if(G){
    strcpy(G->vert[v].colore, "grigio");
    matr = G->struttura;
    for(i = 0; i < G->n_vet; ++i){
      if(G->vert[i].eliminato == 0 && strcmp(G->vert[i].colore, "bianco") == 0 && matr[v][i] > 0){                                  
        ris = aciclico_matr(G, i);                   //se il nodo è bianco continua
        if(ris == 0)
          break;
      }
      else if(G->vert[i].eliminato == 0 && strcmp(G->vert[i].colore, "grigio") == 0 && matr[v][i] > 0){
        ris = 0;                              //se il nodo non è bianco allora c'è un ciclo
        break;
      }
    }
    strcpy(G->vert[v].colore, "nero");
  }
  return ris; 
}

//--------------------------------------------------------------------------------------------


//-----------------------restituisc il grafo passato in input sotto forma di lista di adiacenza-------

void MatrToList(GRAFO* G){
  LISTA** lista;
  LISTA* curr;
  double** matr;
  double peso;
  int i = 0, j = 0;
  
  if(G && G->struttura){
    matr = (double**)G->struttura;
    lista = (LISTA**)malloc(sizeof(LISTA*) * G->n_vet);      //alloco la nuova struttura
    for(i = 0; i < G->n_vet; ++i){
      lista[i] = NULL;
    }
    
    
    G->struttura = (void*)lista;
    for(i = 0; i < G->n_vet; i++){
      for(j = 0; j < G->n_vet; j++){
        peso = matr[i][j];
        if( peso != 0)                  //inserisco gli archi nella nuova struttura
          ins_arco_lista(G, i, j, peso);
      }
    }
    
    
    free(matr);                           //dealloco la vecchia struttura
  }
  
  // setto le funzioni per la lista di adiacenza
  G->funzioni.insVert = &ins_vert_lista;
  G->funzioni.ins_arco = &ins_arco_lista;
  G->funzioni.cancVert = &canc_vert_lista;             
  G->funzioni.canc_arco = &canc_arco_lista;
  G->funzioni.BFS = &BFS_lista;
  G->funzioni.DFS_visita = &DFS_visita_lista;            
  G->funzioni.stampa = &stampa_lista;
  G->funzioni.aciclico_visita = &aciclico_lista;
  G->funzioni.cambia_rap = &ListToMatr;
  G->funzioni.trasposto = &trasposto_lista;
  G->funzioni.InsFile = &ModFileLista;
}

//----------------------------------------------------------------------------------------------


//-----------Gestisce la scrittura su file del grafo secondo regole prestabilite----------------
void ModFileMatrice(GRAFO* G,FILE* fd,int i ){
    double** Matr=G->struttura;
    int j=0;
    for(j = 0; j <= G->n_vet; ++j){
        if(G->vert[i].eliminato==0){
            if(Matr[i][j]==1){  //se l'arco ha costo unitario
                fprintf(fd," ");
            }
            else if(Matr[i][j]!=0){   //se l'arco ha costo diverso da 1 ed esiste
                fprintf(fd,"(%.2lf)",Matr[i][j]);
            }

            if(Matr[i][j]!=0){  //se l'arco esiste
                fprintf(fd,"%s",G->vert[j].id);
            }

        }
    }
    fprintf(fd,";");
}


//-----------------------------------------------------------------------------------------------




/******************************************************************************************
 FUNZIONI PER LA GESTIONE DI UNA LISTA DI ADIACENZA
/*****************************************************************************************/

//----------------------inizializzazione matrice di adiacenza----------------------------------
GRAFO* init_lista(){
  GRAFO* grafo = (GRAFO*)malloc(sizeof(GRAFO));
  grafo->n_nodi = 0;
  grafo->n_vet = 0;
  grafo->struttura = NULL;
  grafo->vert = NULL;
  grafo->funzioni.insVert = &ins_vert_lista;
  grafo->funzioni.ins_arco = &ins_arco_lista;
  grafo->funzioni.cancVert = &canc_vert_lista;
  grafo->funzioni.canc_arco = &canc_arco_lista;
  grafo->funzioni.BFS = &BFS_lista;
  grafo->funzioni.DFS_visita = &DFS_visita_lista;
  grafo->funzioni.stampa = &stampa_lista;
  grafo->funzioni.aciclico_visita = &aciclico_lista;
  grafo->funzioni.cambia_rap = &ListToMatr;
  grafo->funzioni.trasposto = &trasposto_lista;
  grafo->funzioni.InsFile = &ModFileLista;
  return grafo;
}


//--------------------------------------------------------------------------------------------



//--------------------------stampa di una lista di adiacenza------------------------------

void stampa_lista(GRAFO* G){
  int i, vert, cont = 0;
  double peso;
  LISTA** lista;
  LISTA* curr;
  if(G == NULL) printf("NULL G");
  if(G->struttura == NULL) printf("NULL struttura");
  if(G && G->struttura){
    lista = (LISTA**)G->struttura;
    for(i = 0; i < G->n_vet; ++i){
      curr = lista[i];
      printf("adiacenti di %d:\n" , i);
      if(G->vert[i].eliminato == 0)
        cont++;
      while(curr){
        vert = curr->valore;
        peso = curr->peso;
        printf("a\t nodo: %d peso: %4.2f \n", vert, peso);
        curr = curr->next;
      }
      if(cont == G->n_nodi)
        break;
    }
  }
}

//.--------------------------------------------------------------------------------------


//---------------inserimento di un vertice in una lista di adiacenza----------------------

void* ins_vert_lista(void* struttura, int n_nodi){
  LISTA** lista;
  int i = 0;
  lista = (LISTA**)struttura;
  if(lista == NULL){
    lista = (LISTA**)malloc(sizeof(LISTA*) * 10);
    for(i = 0; i < n_nodi; i++){
      lista[i] = NULL;
    }
  }
  else if(n_nodi % 10 == 0){
    lista = (LISTA**)realloc(lista, sizeof(LISTA*) * (n_nodi + 10) );
    for(i = n_nodi; i < n_nodi + 10; i++){
      lista[i] = NULL;
    }
  }
  return lista;
}

//---------------------------------------------------------------------------------------


//----------------------inserimento di un arco in una lista di adiacenza------------------

void ins_arco_lista(GRAFO* grafo, int start, int end, double peso){
  LISTA** lista;
  if(grafo){
    if(grafo->struttura){
      if(start < grafo->n_vet && end < grafo->n_vet && grafo->vert[start].eliminato == 0 && grafo->vert[end].eliminato == 0){
        lista = (LISTA**)grafo->struttura;
        lista[start] = ins_testa(lista[start], end, peso);
      }
    }
  }
}

//----------------------------------------------------------------------------------------



//--------------------------cancellazione arco da una lista di adiacenza------------------------

void canc_arco_lista(GRAFO* grafo, int start, int end){
LISTA** lista;
  if(grafo){
    if(grafo->struttura){
      if(start < grafo->n_vet && end < grafo->n_vet && grafo->vert[start].eliminato == 0 && grafo->vert[end].eliminato == 0){
        lista = (LISTA**)grafo->struttura;
        lista[start] = canc_elemento(lista[start], end);
      }
    }
  }
}
//-----------------------------------------------------------------------------------------



//------------------------cancellazione di un vertice da una lista di adiacenza---------------

void canc_vert_lista(GRAFO* G, int ind){
  LISTA** lista;
  int i = 0;
  if(G){
    if(G->struttura){
      lista = (LISTA**)G->struttura;
      for(i = 0; i < G->n_vet; ++i){
        lista[i] = canc_elemento(lista[i], ind);
      }
      lista[ind] = canc_lista(lista[ind]);
    }
  }
}

//--------------------------------------------------------------------------------------------


//---------------------------trasposto in lista di adiacenza-----------------------------------

void trasposto_lista(GRAFO* G ){
  LISTA **lista, **trasp;
  LISTA *curr;
  int i = 0, vert;
  double peso;
  if(G && G->struttura){
    
    
    trasp = (LISTA**)malloc(sizeof(LISTA*) * G->n_vet); 
    for(i = 0; i < G->n_vet; ++i){
      trasp[i] = NULL;                     //alloco il grafo trasposto e lo inizializzo
    }
    lista = (LISTA**)G->struttura;
    G->struttura = (void*)trasp;
    
    
    for(i = 0; i < G->n_vet; ++i){
      curr = lista[i];
      while(curr){
        vert = curr->valore;
        peso = curr->peso;                 //riampio il grafo trasposto
        ins_arco_lista(G, vert, i, peso);
        curr = curr->next;
      }
    }
    
    for(i = 0; i < G->n_vet; ++i){
      canc_lista(lista[i]);              //dealloco il vecchio grafo
    } 
    free(lista);
    
  }
}

//----------------------------------------------------------------------------------------------


//-----------------------BFS- visita in ampiezza con riempimento dell'array dei predecessori--------------------
void BFS_lista(GRAFO* G, int s, int* pred){
  STACK* coda = NULL;
  LISTA** lista;
  LISTA* curr;
  int i, u;
  /*controllo che il grafo e l'array dei predecessori esistano
   e che il vertice di partenza non sia stato eliminato */
  if(G && pred && s < G->n_vet && G->vert[s].eliminato == 0){
    lista = (LISTA**) G->struttura;
    /*i vertici non sono in coda e li inizializzo 
    tutti al colore bianco */
    for(i = 0; i < G->n_vet; ++i){
      if(i != s && G->vert[i].eliminato == 0){
        strcpy(G->vert[i].colore, "bianco");
      }
    }
    /*quando un vertice va in coda diventa grigio */
    strcpy(G->vert[s].colore, "grigio");
    pred[s] = -1;
    coda = accoda(coda, s);
    while(vuoto(coda) != 1){
      u = pop(coda);
      curr = lista[u];
      /*scorro i vertici adiacenti ad "u" e se sono bianchi li metto in coda */
      while(curr){
        i = curr->valore;
        if(strcmp(G->vert[i].colore, "bianco") == 0){
          strcpy(G->vert[i].colore, "grigio");
          pred[i] = u;
          accoda(coda, i);
        }
        curr = curr->next;
      }
      /*finita la visita di "u" posso toglierlo dalla coda e colorarlo di nero */
      coda = del_testa(coda);
      strcpy(G->vert[u].colore, "nero");
    }
  }
}

//-------------------------------------------------------------------------------------------------


//-----------------------------DFS visita per lista di adicenza-------------------------------------

void DFS_visita_lista( GRAFO* G, int v , int* pred){
  int i = 0;
  LISTA** lista;
  LISTA* curr;
  if(G && pred){
    strcpy(G->vert[v].colore, "grigio");
    lista = G->struttura;
    curr = lista[v];
    while(curr){
      i = curr->valore;
      if(strcmp(G->vert[i].colore, "bianco") == 0 ){
        pred[i] = v;
        DFS_visita_lista(G, i, pred);
      }
      curr = curr->next;
    }
    strcpy(G->vert[v].colore, "nero");
  } 
}

//------------------------------------------------------------------------------------------------


//----------------------verifica aciclicità lista di adiacenza------------------------------------

int aciclico_lista( GRAFO* G, int v){
  int i = 0, ris = 1;
  LISTA** lista;
  LISTA* curr;
  if(G){
    strcpy(G->vert[v].colore, "grigio");
    lista = G->struttura;
    curr = lista[v];
    while(curr){
      i = curr->valore;
      if(strcmp(G->vert[i].colore, "bianco") == 0 ){
        ris = aciclico_lista(G, i);
        if(ris == 0)
          break;
      }
      else if(strcmp(G->vert[i].colore, "grigio") == 0 ){
        ris = 0;                              //se il nodo non è bianco allora c'è un ciclo
        break;
      }
      curr = curr->next;
    }
    strcpy(G->vert[v].colore, "nero");
  }
  return ris; 
}

//---------------------------------------------------------------------------------------------------------


//-----------------------restituisc il grafo passato in input sotto forma di matrice di adiacenza-----------

void ListToMatr(GRAFO* G){
  LISTA** lista;
  LISTA* curr;
  double** matr;
  double peso;
  int i = 0, j = 0;
  
  
  if(G && G->struttura){
    lista = (LISTA**)G->struttura;
    matr = (double**)malloc(sizeof(double*) * G->n_vet);      //alloco la nuova struttura
    for(i = 0; i < G->n_vet; ++i){
      matr[i] = (double*)malloc(sizeof(double) * G->n_vet);
    }
    
    
    for(i = 0; i < G->n_vet; ++i){
      for(j = 0; j < G->n_vet; ++j){             //inizializzo la matrice
        matr[i][j] = 0;
      }
    }
    
    G->struttura = (void*)matr;
    for(i = 0; i < G->n_vet; i++){
      curr = lista[i];
      while(curr){
        j = curr->valore;
        peso = curr->peso;                  //inserisco gli archi nella nuova struttura
        ins_arco_matr(G, i, j, peso);
        curr = curr->next;
      }
    }
    
    
    for(i = 0; i < G->n_vet; i++){
      lista[i] = canc_lista(lista[i]);         //dealloco la vecchia struttura
    }
    free(lista);
  }
  
  //setto le funzioni per la matrice di adiacenza
  G->funzioni.insVert = &ins_vert_matr;
  G->funzioni.ins_arco = &ins_arco_matr;
  G->funzioni.cancVert = &canc_vert_matr;
  G->funzioni.canc_arco = &canc_arco_matr;
  G->funzioni.BFS = &BFS_matr;
  G->funzioni.DFS_visita = &DFS_visita_matr;
  G->funzioni.stampa = &stampa_matr;
  G->funzioni.aciclico_visita = &aciclico_matr;
  G->funzioni.cambia_rap = &MatrToList;
  G->funzioni.trasposto = &trasposto_matr;
  G->funzioni.InsFile = &ModFileMatrice;
}

//----------------------------------------------------------------------------------------------------


//----------------Gestisce la scrittura su file del grafo secondo regole prestabilite-----------------
void ModFileLista(GRAFO* G,FILE* fd,int i){
    LISTA* curr;
    LISTA** lista;
    lista = (LISTA**)G->struttura;
    curr = lista[i];  //elemento corrente
    while(curr){    //inserisci adiacenti dell elemento corrente nel file
        if(curr->peso!=1){
            fprintf(fd,"(%.2lf)",curr->peso);
        }
        else{
            fprintf(fd," ");
        }
        fprintf(fd,"%s",G->vert[curr->valore].id);
        curr = curr->next;
    }
    fprintf(fd,";");

}
