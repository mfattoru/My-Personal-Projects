/*=========================================================================
 Libreria funzioni per I/O e per PAC-MAN
                                                         di Luigi Lamberti

------------------------------------------------------------ 13.06.2011 --*/

#include <conio.h>
#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include <windows.h>


#define INVIO            13
#define ESC              27
#define SPAZIO           32

#define CURSORUP        328
#define CURSORLEFT      331
#define CURSORDOWN      336
#define CURSORRIGHT     333
#define PAUSE           112
#define BSIZE           113   //q
#define BSPEED          119   //w
#define BPATH           101   //e

#define MAXRIGHEVIDEO    50
#define MAXCOLONNEVIDEO  80

#define FACILE           49  //1
#define MEDIO            50  //2
#define DIFFICILE        51  //3

//---------------------------------------------------------------------
// La struttura contiene uno spazio sufficiente per il massimo delle
// finestre in modalità testo, piu` gli indicatori del numero
// dii righe e colonne effettivamente usate:
// Up-Left: Area[0][0]       Bottom-Right: Area[Nrighe-1][Ncolonne-1]
//
typedef struct mappa
{   int Area[MAXRIGHEVIDEO][MAXCOLONNEVIDEO],
        Nrighe,
        Ncolonne;
}MAPPA;

//---------------------------------------------------------------------
void    Clrscr              (void);
void    Gotoxy              (int x,int y);
void    LeggiStringa        (char *Stringa, int  LenMax);
int     LeggiTasto          (int Wait);
void    TextColor           (int Colore);
void    Window              (int Left, int Top, int Right, int Bottom);
void    VisualizzaMappa     (MAPPA *M,int X,int Y,int size,int* Muro,int Direzione);
int*    InizializzaMappa    (MAPPA* M,char* FileName);
int     CalcolaDimMappa     (MAPPA* Map,char* FileName);
float   dist_euclidea       (int startX, int startY, int endX, int endY);
int**   A_star              (MAPPA* map, int startX, int startY, int endX,int endY);
int**   adiacenti           (int x, int y, int maxrighe, int maxcolonne);
void    VediMin             (MAPPA* map, int** path);
void    cancella_path       (MAPPA* map, int** path);
void    MostraBonusA        (int Nrighe,int BonusS,int BonusV,int BonusP);
void    AggiornaBonusA      (int Colonna,int Riga,int valore);
int     Catturato           ();
