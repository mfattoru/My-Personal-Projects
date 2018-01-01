
/*=========================================================================
 Libreria funzioni per I/O e per PAC-MAN
                                                         di Luigi Lamberti

------------------------------------------------------------ 6.06.2011 --*/

#include "Console.h"
#include "heap.h"
#include <math.h>


/*===========================================================================
  Cancella lo schermo.
  L'ultima assegnazione di TextColor() viene propagata a tutta la finestra.
----------------------------------------------------------------------------*/
void Clrscr (void){
	COORD coord;
	DWORD written;
	CONSOLE_SCREEN_BUFFER_INFO info;

	coord.X = coord.Y = 0;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	FillConsoleOutputCharacter (GetStdHandle(STD_OUTPUT_HANDLE), ' ',
					  info.dwSize.X * info.dwSize.Y, coord, &written);
	Gotoxy (0, 0); // cursore su up-left
}


/*===========================================================================
  Posiziona il cursore di console alle coordinate x,y.
----------------------------------------------------------------------------*/
void Gotoxy
(   int x,         // indice di colonna
	int y          // indice di riga
)
{	COORD Cur = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}


/*===================================================================
  Funzione per la lettura di una stringa da tastiera.
  Saranno accettati al massimo LenMax-1 caratteri, inserendo il NULL
  finale; i caratteri eccedenti verranno persi;
  il LineFeed di chiusura (10) viene eliminato.
  La procedura chiamante deve allocare spazio non inferiore a LenMax.
---------------------------------------------------------------------*/
void LeggiStringa
(
    char *Stringa,      // puntatore alla stringa
    int  LenMax         // lunghezza massima dello spazio allocato
)
{   int i;

    fgets ( Stringa, LenMax, stdin );
    i = strlen(Stringa) - 1;         // elimina i codici di controllo
    while (i>=0 && Stringa[i] > 0 && Stringa[i]<32) Stringa[i--] = 0;
    fflush( stdin );
}


/*===========================================================================
  Lettura di un carattere da tastiera; il parametro Wait indica se e quanto
  occorre attendere che l'utente batta un tasto.
  I tasti ASCII (un byte nel buffer di tastiera) sono letti con _getch().
  I tasti speciali, inseriti nel buffer di tastiera con due byte
  (zero o 224 + il numero di tasto) sono letti con due _getch().

  OUT: Il codice Ascii oppure, il codice del tasto speciale+256:
    nessun tasto :   0
    Backspace    :   8          Enter       :  13       Esc         :  27
    Tab          :   9          Shift-Tab   : 271
    f1..f10      : 315..324     f11         : 389       f12         : 390
    Shift-f1..f10: 340..349     Shift-f11   : 391       Shift-f12   : 392
    Ctrl-f1..f10 : 350..359     Ctrl-f11    : 393       Ctrl-f12    : 394
    Alt-f1..f10  : 360..369     Alt-f11     : 395       Alt-f12     : 396
    Ins          : 338          Home        : 327       Page UP     : 329
    Cancel       : 339          End         : 335       Page DOWN   : 337
    Cursor UP    : 328          Cursor LEFT : 331
    Cursor DOWN  : 336          Cursor RIGHT: 333
    Ctrl-Crs UP  : 397          CtrlCrs LEFT: 371
    Ctrl-Crs DOWN: 401          CtrlCrsRIGHT: 372
    Alt-Crs UP   : 408          Alt-Crs LEFT: 411
    Alt-Crs DOWN : 416          AltCrs RIGHT: 413

  NON visualizza il carattere sullo schermo.
----------------------------------------------------------------------------*/
int LeggiTasto
(   int Wait           // Input: attesa massima in millesimi di secondo
)                      //        -1 attesa infinita;  0 non attende
{   int Prima, Dopo,
        Tasto = 0;

    Prima = clock();   // lettura in millesimi di secondo
    if (Wait<0) Wait = 0x7FFFFFFF;      // circa 25 giorni

    do Dopo = clock(); while (Dopo-Prima<Wait && !_kbhit());

    if (_kbhit())
    {   Tasto = _getch();
        if (Tasto == 0 || Tasto == 224) Tasto = _getch() + 256;
    }
    return ( Tasto );
}


/*===========================================================================
 Utilizzando la funzione SetConsoleTextAttribute(HANDLE,WORD)
 cambia il colore del testo da stampare in console.
----------------------------------------------------------------------------*/
void TextColor
(	int Colore    // codice numerico del colore
)
{	HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );
	SetConsoleTextAttribute ( h, Colore );
}


/*===========================================================================
  Apre una finestra di lavoro. Le dimensioni non possono eccedere 50x80.
----------------------------------------------------------------------------*/
void Window
(   int Left,
    int Top,
    int Right,
    int Bottom
)
{   SMALL_RECT R;

    R.Top  = Top;     R.Right  = Right;
    R.Left = Left;    R.Bottom = Bottom;
    SetConsoleWindowInfo (GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &R);
    Gotoxy (Left, Top);
}


/*==================================================================================
 Funzione che inizializza la mappa del labirinto leggendola da file
------------------------------------------------------------------------------------*/
int* InizializzaMappa(MAPPA *M,char* FileName){
    int *uscita=(int*) malloc(sizeof(int)*2);
    uscita[0]=-1;
    uscita[1]=-1;
    int x,y;
    FILE *file;
    char ch;
    file = fopen(FileName, "r");
    x=0;y=0;
    while(!feof(file)){
        ch=getc(file);
        if(ch=='|' || ch == '='  || ch=='#'){
            M->Area[y][x]=1;
        }
        else if(ch=='.'){
            M->Area[y][x]=0;
        }
        else if(ch=='E'){
            uscita[0]=x;
            uscita[1]=y;
            M->Area[y][x]=-2;
        }
        else if(ch=='\n'){
            x=-1;
            y++;
        }
        else{
            M->Area[y][x]=-1;
        }
        x++;
    }
    fclose(file);
    return uscita;
}

/*=======================================================================================================
 Funzione che calcola la dimensione della mappa del labirinto contenuto nel file passatogli in ingresso.
 Nel caso in cui la mapap non rispetti le dimensioni massime permesse dal programma,questa restituirà un
 codice di errore per segnalare all'utente la non correttezza della mappa
--------------------------------------------------------------------------------------------------------*/

int CalcolaDimMappa(MAPPA *Map,char* FileName){
    int Righe=0,Colonne=0,ris=-1;
    FILE *file;
    char ch;
    file = fopen(FileName, "r");
    if(file!=NULL){

        while(!feof(file)){
            ch=getc(file);
            if(ch=='\n'){
                if(Colonne==0){
                    Colonne=(ftell(file)/sizeof(char))-2; //da sottrasse lo \n
                }
                Righe++;
            }
        }
        fclose(file);
        Righe++;  //trova EOF all ultima riga e non \n quindi non viene conteggiata la riga
        if(Righe<=MAXRIGHEVIDEO && Colonne <=MAXCOLONNEVIDEO){
            Map->Nrighe=Righe;
            Map->Ncolonne=Colonne;
            ris=0;
        }
    }
    return ris;
}


/*===========================================================================
 Ridimensiona la window di testo in base al numero di righe e colonne
 necessarie, e rappresenta le pareti con opportuni simboli di testo,
 in base allo sviluppo dei muri.
 Ad ogni casella non vuota della matrice, viene assegnato un peso variabile
 in base ai vicini presenti: +1 destra, +2 alto, +4 sinistra, +8 sotto.
 Il peso indica il carattere da usare per rappresentare il muro.
----------------------------------------------------------------------------*/
void VisualizzaMappa (MAPPA *M,int X,int Y,int size,int* Muro,int Direzione){
    int   i, j, k,OldX,OldY;

    if (M)
    {   Window (0,0, M->Ncolonne-1, M->Nrighe+2);
        TextColor (0x0F);

        X=X-size;
        Y=Y-size;
        OldY=Y;
        OldX=X;

        if (X<0){
            X=0;
        }
        if(Y<0){
            Y=0;
        }
        size=2*size;
        //Vengono stampati soltanto i muri presenti nel rettangolo di visualizzazione
        for (i=X; i<OldX+size && i<M->Nrighe; i++)
            for (j=Y; j<OldY+size && j<M->Ncolonne; j++)
                if (M->Area[i][j])
                {
                    if(M->Area[i][j]==2){ //mio omino
                        TextColor(0x0E);
                        Gotoxy (j, i);
                        printf ("#");
                        TextColor(0x0F);
                    }
                    else if(M->Area[i][j]==-2){ //uscita dal labirinto
                        k=16;
                        Gotoxy(j,i);
                        printf ("%c", Muro[k]);
                    } //Visualizzazione fantasma
                    else if(M->Area[i][j]==3 || //Fantasma
                            M->Area[i][j]==7 || //Fantasma sul percorso minimo
                            M->Area[i][j]==9 || //Fantasma sul bonus
                            M->Area[i][j]==13){ //Fantasma sul Bonus e percorso minimo
                        Gotoxy(j,i);
                        TextColor(0x04);
                        printf("G");
                        TextColor(0x0F);  //la stampa del fantasma avviene sia quando si refresha la mappa sia quando il personaggio si muove
                    }
                    else if(M->Area[i][j]==4 ){  //percorso minimo
                        Gotoxy(j,i);
                        TextColor(0x0E);
                        printf(".");
                        TextColor(0x0F);
                    }
                    else if(M->Area[i][j]==6 ||  //bonus
                            M->Area[i][j]==10){  //bonus sul percorso minimo
                        Gotoxy(j,i);
                        TextColor(0x01);
                        printf("B");
                        TextColor(0x0F);
                    }
                    else{
                        k = 0;
                        if (j<M->Ncolonne-1 && M->Area[i][j+1]==1) k += 1;
                        if (i>0             && M->Area[i-1][j]==1) k += 2;
                        if (j>0             && M->Area[i][j-1]==1) k += 4;
                        if (i<M->Nrighe-1   && M->Area[i+1][j]==1) k += 8;
                        Gotoxy(j,i);
                        printf ("%c", Muro[k]);
                    }
                }
                else{
                    Gotoxy (j, i);
                    printf (" ");
                }

        if(Direzione==CURSORUP){
            i=OldX+size;
            if(i<M->Nrighe){  //non cancella la riga inferiore se questa esce dalle dimensioni del labirinto
                for (j=Y; j<Y+size && j<M->Ncolonne; j++){ //cancella la riga inferiore del riquadro
                    Gotoxy(j,i);
                    printf(" ");
                }
            }
        }
        else if(Direzione==CURSORDOWN){
            i=OldX-1;
            for (j=Y; j<Y+size && j<M->Ncolonne; j++){  //Cancella la riga superiore al riquadro
                Gotoxy(j,i);
                printf(" ");
            }

        }
        else if(Direzione==CURSORRIGHT){
            j=OldY-1;
            for (i=X; i<OldX+size && i<M->Nrighe; i++){  //cancella la riga alla sinistra del riquadro
                Gotoxy(j,i);
                printf(" ");
            }
        }
        else if(Direzione==CURSORLEFT){
            j=OldY+size;
            if(j<M->Ncolonne){                //impedisce la stampa al di fuori dell'area delimitata dal labirinto
                for (i=X; i<OldX+size && i<M->Nrighe; i++){  //cancella la riga alla sinistra del riquadro
                    Gotoxy(j,i);
                    printf(" ");
                }
            }
        }
    }
}


/*===========================================================================
  restituisce il valore della distanza euclidea tra 2 punti
----------------------------------------------------------------------------*/
float dist_euclidea(int startX, int startY, int endX, int endY){
    float ris = 0;
    ris = sqrt( pow(endX - startX, 2) + pow(endY - startY, 2) );
    return ris;
}



/*===========================================================================
  funzione che restituisce gli adiacenti di un punto dati X e Y
----------------------------------------------------------------------------*/
int** adiacenti(int x, int y, int maxrighe, int maxcolonne){
    int** ris = malloc(sizeof(int*) * 4);
    int i;
    for (i = 0; i < 4; ++i){
        ris[i] = malloc(sizeof(int) * 2);
    }
    ris[0][0] = (x + 1) % maxrighe;
    ris[0][1] = y;

    ris[1][0] = x;
    ris[1][1] = (y + 1) % maxcolonne;

    ris[2][0] = x;
    ris[2][1] = (y - 1 + maxcolonne) % maxcolonne;

    ris[3][0] = (x - 1 + maxrighe) % maxrighe;
    ris[3][1] = y;

    return ris;
}


/*===========================================================================
  funzione che inserisce in un array le cordinate dei punti
  del percorso trovato
----------------------------------------------------------------------------*/

void VediMin(MAPPA* map, int** path){
    int i = 0;
    while(path[i] != NULL){
        map->Area[ path[i][0] ] [ path[i][1] ] = map->Area[ path[i][0] ] [ path[i][1] ] + 4;
        ++i;
    }
}


/*===========================================================================
  funzione che cancella dalla mappa un il percorso minimo
----------------------------------------------------------------------------*/
void cancella_path(MAPPA* map, int** path){
    int i = 0;
    while(path[i] != NULL){
        if( map->Area[ path[i][0] ] [ path[i][1] ] == 4)
           map->Area[ path[i][0] ] [ path[i][1] ] = 0;
        ++i;
    }
}

int nodiVisitati(HEAP_EL* curr){
    int ris = 0;
    if(curr != NULL){
        ris = nodiVisitati(curr->prec) + 1;
    }
    return ris;
}


int** A_star(MAPPA* map, int startX, int startY, int endX,int endY){
    int found = 0, i = 0, inOpen, inClosed;
    float cost = 0;

    HEAP *closed, *open;
    HEAP_EL *curr;

    closed = (HEAP*)malloc(sizeof(HEAP));
    open = (HEAP*)malloc(sizeof(HEAP));

    open->dim_heap = 0;
    closed->dim_heap = 0;

    open->array = NULL;
    closed->array = NULL;

    int **adj,  **path;
    int* elemento = (int*)malloc(sizeof(int) * 2);
    int* valore;

    elemento[0] = startX;
    elemento[1] = startY;

    Inserimento(open, elemento, dist_euclidea(startX, startY, endX, endY), NULL);

    while(open->dim_heap > 0 || found != 1){

        curr = EstraiMinimo(open);
        valore = (int*) curr->elem;

        if( valore[0] == endX && valore[1] == endY){

            found = 1;

        }
        else{

            adj = adiacenti(valore[0], valore[1], map->Nrighe, map->Ncolonne);

            for(i = 0; i < 4; ++i){

                if(map->Area[ adj[i][0]] [ adj[i][1] ] != 1){

                    cost = nodiVisitati(curr) + 1 + dist_euclidea( adj[i][0], adj[i][1], endX, endY);
                    inOpen = XinCoda(open, adj[i][0], adj[i][1]);
                    inClosed = XinCoda(closed, adj[i][0], adj[i][1]);

                    if( inOpen > -1 && cost < open->array[inOpen].priorita){

                        elemento = (int*)open->array[inOpen].elem;
                        open->array[inOpen].prec = curr;
                        IncreaseKey(open, inOpen, cost);

                    }
                    else if(inClosed > -1 && cost < closed->array[inClosed].priorita){

                        DeleteKey(closed, inClosed);
                        elemento = (int*)malloc(sizeof(int) * 2);
                        elemento[0] = adj[i][0];
                        elemento[1] = adj[i][1];
                        Inserimento(open, elemento, cost, curr);

                    }
                    else if( inClosed < 0 && inOpen < 0){

                        elemento = (int*)malloc(sizeof(int) * 2);
                        elemento[0] = adj[i][0];
                        elemento[1] = adj[i][1];
                        Inserimento(open, elemento, cost, curr);

                    }
                }
            }
        }
        Inserimento(closed, valore, curr->priorita,curr->prec);
    }
    if (found){
        path = GeneratePath(closed, endX, endY);
    }
    else{
        path = NULL;
    }
    return path;
}

/*-----------------------------------------------------------------
  Funzione che mostra il numero di bonus posseduti dall utente
-----------------------------------------------------------------*/

void MostraBonusA(int Nrighe,int BonusS,int BonusV,int BonusP){
    Gotoxy(0,Nrighe);
    TextColor(0x0F);
    printf("#q BONUS RAGGIO: %d\n",BonusS);
    printf("#w BONUS VELOCITA: %d\n",BonusV);
    printf("#e BONUS PERCORSO: %d",BonusP);
}

/*-----------------------------------------------------------------
  Funzione che Aggiorna i Bonus dell utente non appena
  si raccoglie un nuovo bonus
------------------------------------------------------------------*/

void AggiornaBonusA(int Colonna,int Riga,int valore){
    Gotoxy(Colonna,Riga);
    printf("      ");
    Gotoxy(Colonna,Riga);
    TextColor(0x0F);
    printf("%d",valore);
}

int Catturato(){
    int i=0;
    int Tasto=ESC;
    TextColor(0x0A);
    Clrscr();
    Window (0,0, 70, 10);
    Gotoxy(15,4);
    printf("Sei Stato Catturato dal Mostro.");
    Gotoxy(17,5);
    printf("Premi un tasto qualsiasi per continuare");
    Gotoxy(17,6);
    printf("Premi ESC per uscire dal gioco");
    Gotoxy(1,9);
    printf("Tempo Rimanente: ");
    Gotoxy(17,9);
    do{
        printf("%2d",10-i);
        Gotoxy(35,7);
        Tasto=LeggiTasto(1000);
        i++;
        Gotoxy(17,9);
    }while(i<10 && Tasto==0);
    if(Tasto==NULL){
        Tasto=ESC;
    }
    return Tasto;
}
