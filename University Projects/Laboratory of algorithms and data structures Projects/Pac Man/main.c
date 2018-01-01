
#include "console.h"
#include <stdio.h>
#include "heap.h"

/*=========================================================================
 Gestione di un Labirinto stile PAC-MAN
                                                    di Luigi Lamberti

 Il programma utiliza una libreria di funzioni per la gestione dell'I/O
 da tastiera e su schermo.
 La libreria e` aggiunta al progetto in formato sorgente, in modo da
 consentire eventuali modifiche e/o aggiunte.
 Le scelta nei nomi dell'italiano e della camel-notation,
 consente di evidenziare queste funzioni da quelle standard.

 La mappa e` uno spazio toroidale con i bordi destro e sinistro contigui,
 e analogamente i bordi superiore e inferiore.

 Il progamma e'proposto SOLO a TITOLO DI ESEMPIO per l'utilizzo delle
 funzioni di I/O in modo testo.

------------------------------------------------------------ 13.06.2011 --*/

int main (void){
	MAPPA Map;
    int   PacX, PacY,          // colonna/riga del nostro omino
          NewX, NewY,
          GhostX,GhostY,       // colonna/riga del fantasma
          NewGhostX,NewGhostY,
          DiffX,DiffY,
          BonusX,BonusY,        // colonna/riga del bonus
          BonusP=0,               //visualizza perscorso minimo
          BonusV=0,               //aumenta velocità del personaggio
          BonusS=0;               //aumenta grandezza finestra
                    // colonna/riga nella verifica del movimento
    int   PacDirezione,        // una delle 4 direzioni possibili
          PacPrima,
          PacDopo,
          PacWait,              // timer in millesimi di secondo
          Tasto,
          GhostPrima,
          GhostDopo,
          GhostWait,            // timer in millesimi di secondo
          pausa=-1,
          BonusPrima,
          BonusDopo,
          BonusWait,            // timer in millesimi di secondo
          choise,
          SpeedPrima,
          SpeedDopo,
          SpeedWait,    //dutara Bonus Speed
          PathPrima,
          PathDopo,
          PathWait,     //dutara Bonus Path
          SizePrima,
          SizeDopo,
          SizeWait,     //dutara Bonus Size
          SUsato=0,     //bonus size usato
          VUsato=0,     //Bonus velocita usato
          PUsato=0,     //Bonus Percorso Minimo Usato
          Mosse=0,
          Handicap=7;
    int raggio=5;
    int **path,         //variagile contenente il percorso minimo da seguire
        **GhostPath,    //variagile contenente il percorso minimo che il fantasma deve seguire
        *uscita;        //coordinate dell'uscita dal labirinto
    int end=1;
    char* FileName;     //nome del file contenente il labirinto
    //---------------------------------------------------------------------
    //Set Caratteri Utilizzati Per La Rappresentazione Della Mappa
    int   Muro[] = {177, 196, 179 , 192, 196, 196, 217, 193,
                    179, 218, 179, 195, 191, 194, 180, 197,69};

    //Lettura nome del file contenente il labirinto da standard input

    Window (0,0, 70, 10);
    Gotoxy(10,5);
    TextColor(0x0A);
    FileName=(char*)malloc(sizeof(char)*30);
    printf("Inserisci Il Nome del File Contenente il Labirinto: ");
    Gotoxy(32,7);
    LeggiStringa (FileName,30);
    Clrscr();
    TextColor(0x0F);



    //---------------------------------------------------------------------
    // All'inizio del programma inizializzo un nuovo generatore di
    // pseudocasuali basandomi sull'orario attuale
    //---------------------------------------------------------------------
    srand( (unsigned)time( NULL ) );

    //---------------------------------------------------------------------
	// Calcolo la dimensione della mappa e verifica dell'esistenza del file
    //---------------------------------------------------------------------
	if(CalcolaDimMappa(&Map,FileName)){
	    TextColor(0x0A);
	    Window (0,0, 70, 10);
        Gotoxy(14,2);
        printf("Impossibile Caricare Il Labirinto Da File");
        Gotoxy(14,3);
        printf("L'errore potrebbe essere causato da:");
        Gotoxy(14,5);
        printf("-File Inesistente");
        Gotoxy(14,6);
        printf("-File non Conforme Alle specifiche");
        Gotoxy(14,8);
        system("Pause");
        return -1;
    }


    //---------------------------------------------------------------------
	// Operazioni di caricamento e visualizzazione della mappa labirinto
    //---------------------------------------------------------------------
    Window (0,0, Map.Ncolonne-1, Map.Nrighe+2);
    uscita = InizializzaMappa(&Map,FileName);
    if(uscita[0]==-1){
        TextColor(0x0A);
        Window (0,0, 70, 10);
        Gotoxy(10,5);
        printf("Mappa Progettata Male: Uscita non presente\n");
        Gotoxy(10,6);
        system("pause");
        return -1;
    }
    //---------------------------------------------------------------------
    // Il nostro omino viene posizionato su una casella vuota a caso
    //---------------------------------------------------------------------
    do
    {   PacX = rand() % Map.Ncolonne;
        PacY = rand() % Map.Nrighe;
    }
    while ( Map.Area[PacY][PacX] );

	// qualsiasi metodo per il display del labirinto in modo testo
    VisualizzaMappa (&Map,PacY,PacX,raggio,Muro,0);
    MostraBonusA(Map.Nrighe,BonusS,BonusV,BonusP);



    PacDirezione =   0;                         // inizialmente fermo
    PacWait      = 100;                         // in millisecondi
    GhostWait    = 200;
    BonusWait    = 50000;
    //---------------------------------------------------------------------
    //stampa del nostro omino
    //---------------------------------------------------------------------
    TextColor(0x0E);
    Gotoxy(PacX,PacY);
    printf("#");
    Map.Area[PacY][PacX] = 2;

    //---------------------------------------------------------------------
    // timer per il movimento ogni tot millisecondi
    //---------------------------------------------------------------------
    PacPrima = clock();
    GhostPrima = clock();
    BonusPrima = clock();

    //---------------------------------------------------------------------
    // Posizionamento fantasma
    //---------------------------------------------------------------------
    do{
        GhostX = rand() % Map.Ncolonne;
        GhostY = rand() % Map.Nrighe;
    }while ( Map.Area[GhostY][GhostX] );
    Map.Area[GhostY][GhostX]=3;


    //---------------------------------------------------------------------
    // Con un ciclo di polling vengono esaminati i vari oggetti del gioco
    //---------------------------------------------------------------------
    do
    {
        //------------------------------------------------------------------
        // se non viene battuto alcun tasto, Tasto vale zero, e PacMan
        // permane nel suo stato di quiete o di moto rettilineo uniforme
        //------------------------------------------------------------------
        Tasto = LeggiTasto(0);
        //-----------------------------------------------------------------------------------
        //se vieme battuto un tasto di spostamento,cambiamo la direzione del nostro PacMan
        //-----------------------------------------------------------------------------------
        if (Tasto==CURSORUP || Tasto==CURSORDOWN || Tasto==CURSORRIGHT || Tasto==CURSORLEFT){
             PacDirezione = Tasto;
        }

        //------------------------------------------------------------------------------
        // Alla pressione dei tasti 1,2 e 3 viene cambiata la difficoltà del gioco
        //------------------------------------------------------------------------------
        if(Tasto==FACILE){  //Pressione Tasto 1
            raggio=5;
            Handicap=7;
            GhostWait=200;
            Clrscr();
            VisualizzaMappa (&Map,PacY,PacX,raggio,Muro,0);
            MostraBonusA(Map.Nrighe,BonusS,BonusV,BonusP);
        }
        else if(Tasto==MEDIO){ //Pressione Tasto 2
            raggio=4;
            Handicap=6;
            GhostWait=150;
            Clrscr();
            VisualizzaMappa (&Map,PacY,PacX,raggio,Muro,0);
            MostraBonusA(Map.Nrighe,BonusS,BonusV,BonusP);
        }
        else if(Tasto==DIFFICILE){ //Pressione Tasto 3
            raggio=3;
            Handicap=5;
            GhostWait=150;
            Clrscr();
            VisualizzaMappa (&Map,PacY,PacX,raggio,Muro,0);
            MostraBonusA(Map.Nrighe,BonusS,BonusV,BonusP);
        }
        //----------------------------------------------------------------------------
        // Alla pressione del tasto "P" viene messo in pausa il gioco
        //----------------------------------------------------------------------------
        if (Tasto==PAUSE && pausa==-1){
            pausa=0;
            Clrscr();
            Gotoxy(Map.Ncolonne/2-1,Map.Nrighe/2-1);
            TextColor(0x0A);
            printf("PAUSA\n");
        }
        else if(Tasto==PAUSE && pausa==0){
            pausa=-1;
            Clrscr();
            VisualizzaMappa (&Map,PacY,PacX,raggio,Muro,0);
            MostraBonusA(Map.Nrighe,BonusS,BonusV,BonusP);
        }

        //------------------------------------------------------------------------------
        // Tramite la pressione dei tasti "q","w" ed "e" vengono attivati eventuali
        // Bonus raccolti precedentemente
        //-------------------------------------------------------------------------------
        if(Tasto==BSPEED && BonusV>0){  //Bonus velocità
            PacWait-=50;
            SpeedPrima=clock();
            SpeedWait=BonusV*5000;
            VUsato=1;
            BonusV=0;
            AggiornaBonusA(19,Map.Nrighe+1,BonusV);
        }
        else if(Tasto==BPATH && BonusP>0){  //Bonus percorso minimo
            path = A_star(&Map, PacY, PacX, uscita[1], uscita[0] );
            VediMin(&Map, path);
            Map.Area[uscita[1]][uscita[0]]=-2;
            VisualizzaMappa (&Map,PacY,PacX,raggio,Muro,0);
            PathPrima=clock();
            PathWait=BonusP*5000;
            PUsato=1;
            BonusP=0;
            AggiornaBonusA(19,Map.Nrighe+2,BonusP);
        }
        else if(Tasto==BSIZE && BonusS>0){   //Bonus Ampiezza finestra
            raggio+=3;
            SizePrima=clock();
            SizeWait=BonusS*5000;
            SUsato=1;
            BonusS=0;
            Clrscr();
            VisualizzaMappa (&Map,PacY,PacX,raggio,Muro,0);
            MostraBonusA(Map.Nrighe,BonusS,BonusV,BonusP);
        }

        //--------------------------------------------------------------------------
        // disattivazione dei bonus dopo un determinato periodo di tempo trascorso
        // stimato in base al numero di bonus raccolti
        //----------------------------------------------------------------------------
        SpeedDopo=clock();
        PathDopo=clock();
        SizeDopo=clock();

        if(SpeedDopo-SpeedPrima > SpeedWait && VUsato==1){
            PacWait+=50;
            VUsato=0;
        }
        if(PathDopo-PathPrima>PathWait && PUsato==1){
            cancella_path(&Map,path);
            PUsato=0;
            Clrscr();
            VisualizzaMappa (&Map,PacY,PacX,raggio,Muro,0);
            MostraBonusA(Map.Nrighe,BonusS,BonusV,BonusP);
        }
        if(SizeDopo-SizePrima > SizeWait && SUsato==1){
            raggio-=3;
            SUsato=0;
            Clrscr();
            VisualizzaMappa (&Map,PacY,PacX,raggio,Muro,0);
            MostraBonusA(Map.Nrighe,BonusS,BonusV,BonusP);
        }

        //----------------------------------------------------------------------------------
        // Movimento del Nostro Pacman
        //----------------------------------------------------------------------------------
        PacDopo = clock();

        if (PacDopo - PacPrima > PacWait && pausa!=0) { // movimento ogni decimo di secondo
            NewX = PacX;
            NewY = PacY;
            // l'universo di gioco e' toroidale
            if (PacDirezione==CURSORUP   ) NewY = (PacY-1+Map.Nrighe)  % Map.Nrighe;
            if (PacDirezione==CURSORLEFT ) NewX = (PacX-1+Map.Ncolonne)% Map.Ncolonne;
            if (PacDirezione==CURSORDOWN ) NewY = (PacY+1) % Map.Nrighe;
            if (PacDirezione==CURSORRIGHT) NewX = (PacX+1) % Map.Ncolonne;


            DiffX=NewX-PacX;
            DiffY=NewY-PacY;
            //------------------------------------------------------------------------------
            // Stampa Grafico grafico in conseguenza dell'attraversamento del toroide
            //------------------------------------------------------------------------------
            if((DiffX!=0 && DiffX!=1 && DiffX!=-1 ) || (DiffY!=0 && DiffY!=1 && DiffY!=-1)){   //rispettare toroide
                Clrscr();
                MostraBonusA(Map.Nrighe,BonusS,BonusV,BonusP);
            }
            // si sposta solo se e' vuoto
            if (Map.Area[NewY][NewX] == 0 ||  //area vuota
                Map.Area[NewY][NewX] == 4 ||  //percorso minimo
                Map.Area[NewY][NewX] == 6 ||  //Bonus
                Map.Area[NewY][NewX] == 10)    //Bonus sul percosro minimo
            {     //Bonus

                //-----------------------------------------------------------------------
                // Cattura Bonus Da Parte del Nostro PacMan
                //-----------------------------------------------------------------------
                if(Map.Area[NewY][NewX]==6 ||  //cattura bonus
                   Map.Area[NewY][NewX]==10){  //cattura bonus sul percorso minimo
                    choise=rand()%3;
                    if(choise==0){
                        BonusP+=1;
                        AggiornaBonusA(19,Map.Nrighe+2,BonusP);
                    }
                    else if(choise==1){
                        BonusV+=1;
                        AggiornaBonusA(19,Map.Nrighe+1,BonusV);
                    }
                    else if(choise==2){
                        BonusS+=1;
                        AggiornaBonusA(17,Map.Nrighe,BonusS);
                    }
                }


                Gotoxy (PacX, PacY);
                printf (" ");
                Map.Area[PacY][PacX] = 0;

                PacX = NewX;
                PacY = NewY;

                Map.Area[PacY][PacX] = 2;
                VisualizzaMappa(&Map,NewY,NewX,raggio,Muro,PacDirezione);

            }
            //----------------------------------------------------------------
            // Spostamento del nostro PacMan Sul fantasma
            //------------------------------------------------------------------
            else if(Map.Area[NewY][NewX] == 3){
                Map.Area[PacY][PacX]=0;
                do{
                    PacX = rand() % Map.Ncolonne;
                    PacY = rand() % Map.Nrighe;
                }while ( Map.Area[PacY][PacX] );
                Map.Area[PacY][PacX]=2;

                Tasto=Catturato();

                if (Tasto!=ESC){
                    PacDirezione=0;  //il mostro non continua a muoversi sulla vecchia direzione dopo esser stato riposizionato sul labirinto
                    Clrscr();
                    VisualizzaMappa(&Map,PacY,PacX,raggio,Muro,0);
                    MostraBonusA(Map.Nrighe,BonusS,BonusV,BonusP);
                }
                else{
                    pausa=0;
                }
            }
            //---------------------------------------------------------------
            // Uscita Raggiunta
            //----------------------------------------------------------------
            else if( Map.Area[NewY][NewX] == -2){
                Gotoxy (PacX, PacY);
                printf (" ");
                Map.Area[PacY][PacX] = 0;

                VisualizzaMappa(&Map,NewY,NewX,raggio,Muro,0);

                PacX = NewX;
                PacY = NewY;
                TextColor(0x0E);
                Gotoxy (PacX, PacY);
                printf ("#");
                Map.Area[PacY][PacX] = 2;
                Clrscr ();
                TextColor(0x0A);
                Window (0,0, 58,9);
                printf("                                                           \n");
                printf("   |===================================================|   \n");
                printf("   ||                                                 ||   \n");
                printf("   ||  #     #  #  #####  #####  ####  ###  #    #    ||   \n");
                printf("   ||   #   #   #    #      #    #  #  #  # #   # #   ||   \n");
                printf("   ||    # #    #    #      #    #  #  ###  #  #####  ||   \n");
                printf("   ||     #     #    #      #    ####  # #  # #     # ||   \n");
                printf("   ||                                                 ||   \n");
                printf("   |===================================================|   \n");
                printf("                                                           ");
                end=0;
                pausa=0;
            }
            PacPrima = PacDopo;
        }
        //-----------------------------------------------------------------------------------
        // Movimento del Fantasma
        //-----------------------------------------------------------------------------------
        GhostDopo = clock();
        if (GhostDopo - GhostPrima > GhostWait && pausa!=0){
            int Direzione;
            NewGhostX = GhostX;
            NewGhostY = GhostY;
            Mosse=Mosse%10;
            if((NewGhostX >=PacX-raggio &&
               NewGhostX <= PacX+raggio &&
               NewGhostY >= PacY-raggio &&
               NewGhostY <= PacY+raggio )||
               Mosse < Handicap){ //se si trova nel riquadro oppure se sta effettuando una mossa lungo
                   //il percorso  minimo

                GhostPath = A_star(&Map, PacY, PacX, GhostY,GhostX);
                if(GhostPath[1] != NULL){
                    NewGhostX=GhostPath[1][1];
                    NewGhostY=GhostPath[1][0];
                }
                else{  //PacMan catturato
                    Map.Area[PacY][PacX]=0;
                    do{
                        PacX = rand() % Map.Ncolonne;
                        PacY = rand() % Map.Nrighe;
                    }while ( Map.Area[PacY][PacX] );
                    Map.Area[PacY][PacX]=2;

                    Tasto=Catturato();

                    if (Tasto!=ESC){
                        PacDirezione=0;  //il mostro non continua a muoversi sulla vecchia direzione dopo esser stato riposizionato sul labirinto
                        Clrscr();
                        VisualizzaMappa(&Map,PacY,PacX,raggio,Muro,0);
                        MostraBonusA(Map.Nrighe,BonusS,BonusV,BonusP);
                    }
                    else{
                        pausa=0;
                    }
                }

                if(!(NewGhostX >=PacX-raggio && NewGhostX <= PacX+raggio && NewGhostY >= PacY-raggio && NewGhostY <= PacY+raggio )){
                    Mosse++;
                }
            }
            else{  //se non si trova nel riquardo alterna mosse casuali a mosse lungo il percorso minimo
                Direzione = rand() % 4;
                if (Direzione==0 ) NewGhostY = (GhostY-1+Map.Nrighe)  % Map.Nrighe;
                if (Direzione==1 ) NewGhostX = (GhostX-1+Map.Ncolonne)% Map.Ncolonne;
                if (Direzione==2 ) NewGhostY = (GhostY+1) % Map.Nrighe;
                if (Direzione==3 ) NewGhostX = (GhostX+1) % Map.Ncolonne;
                Mosse++;
            }

            if(Map.Area[NewGhostY][NewGhostX]==0 || //percorso vuoto
               Map.Area[NewGhostY][NewGhostX]==4 || //percorso minimo
               Map.Area[NewGhostY][NewGhostX]==6 || //bonus
               Map.Area[NewGhostY][NewGhostX]==10|| //bonus + percorso minimo
               Map.Area[NewGhostY][NewGhostX]==2 ||
               Map.Area[NewGhostY][NewGhostX]==5)  //Mangia Omino
            {
                Map.Area[NewGhostY][NewGhostX] = Map.Area[NewGhostY][NewGhostX]+3; //nuova posizione
                Map.Area[GhostY][GhostX] = Map.Area[GhostY][GhostX]-3;  //vecchia posizione
                VisualizzaMappa(&Map,PacY,PacX,raggio,Muro,0);
                GhostX = NewGhostX;
                GhostY = NewGhostY;
            }
            GhostPrima = GhostDopo;
        }

        //-------------------------------------------------------------------
        // Comparsa dei bonus
        //-------------------------------------------------------------------
        BonusDopo = clock();
        if (BonusDopo - BonusPrima > BonusWait && pausa!=0){
            BonusWait    = 5000+rand()%30000;
            do{
                BonusX = rand() % Map.Ncolonne;
                BonusY = rand() % Map.Nrighe;
            }while ( Map.Area[BonusY][BonusX]);
            Map.Area[BonusY][BonusX] = Map.Area[BonusY][BonusX]+6;
            BonusPrima=BonusDopo;
        }


    }
    while (Tasto != ESC && end != 0);
    if(Tasto!=ESC){
        LeggiTasto(10000);
    }
    return 0;
}
