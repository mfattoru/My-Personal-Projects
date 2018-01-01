//  Impostazione Array
var day_of_week = new Array('Dom','Lun','Mar','Mer','Gio','Ven','Sab');
var month_of_year = new Array('Gennaio','Febbraio','Marzo','Aprile','Maggio','Giugno','Luglio','Agosto','Settembre','Ottobre','Novembre','Dicembre');

//  Dichiarazione ed inizializzazione variabili
var Calendar = new Date();


//-------------------------------------------Estrazione Dati Da Url-------------------------------------------------------
//si è implementato un metodo per permettere al javascript di recuperare alcuni valori passati alla pagina calendario.html
//tramite riscrittura dell'url,ovvero analizzando l'url della pagina ed estraendo da esso le variabili anno mese e giorno
//necessarie per permetterci di stabilire il giorno selezionato dall'utente
//------------------------------------------------------------------------------------------------------------------------

var args = new Array();
var query = window.location.search.substring(1); //mi ritorna la parte di url successiva al ?
if (query){
  var strList = query.split('&');  //divido query in sottostringhe delimitate dal carattere &
  for(str in strList){		//analizzo tutti gli elementi della sottostringa
    var parts = strList[str].split('='); //divido nuovamente la sottostringa in due parti,delimitata dal carattere = in modo da avere il nome della variabile ricevuta e il suo valore
    args[unescape(parts[0])] = unescape(parts[1]);   //creo un array associativo in cui l'indice dell'array sarà il nome della variabile
  }
}


var year = args['anno'];	    // Ritorna l'anno selezionato
var month = args['mese']-1;    	    // Ritorna il mese selezionato (0-11)
var today = args['giorno'];        // Ritorna il giorno selezionato (1-31)
var Calendar = new Date();


//--------------------------------------se vengono passati dei parametri in input--------------------------------
//nel caso in cui l'utente abbia selezionato dalla pagina calendario una data diversa da quella corrente,dovremo
//calcolarci alcuni adti necessari alla corretta inizializzazione del calendario
//---------------------------------------------------------------------------------------------------------------
if(year!=null && month!=null && today!=null){
  
  var weekday;    // rappresenterà il giorno della settimana (1-7)
  var bisestile=1;  //useremo questa variabile per sapere se l'anno è bisestile (0) o non bisestile (1)
  var G,M,va,A,C,s1;
  var mese=month+1;


//--------------------------------------------Algoritmo Del Calendario Perpetuo-----------------------------------------
//Il calendario perpetuo è un algoritmo che permette di ricavare il giorno della settimana (lunedì, martedì, mercoledì, 
//giovedì, venerdì, sabato, domenica) di un giorno qualsiasi, conoscendone solo la data. 
//----------------------------------------------------------------------------------------------------------------------
  if (today >= 1 && today<= 31 && (year%100) >= 0 && (year%100) <= 99){
    G = today%7;
    if ((year%100 !=0 || year%400 ==  0) && year%4 == 0) bisestile = 0; //è bisestile
      switch(mese){
	case 1:
	if (bisestile == 1 ) M = 0;
	else if (bisestile == 0  ) M = 6;
	break;
      case 2:
	if (bisestile == 1 ) M = 3;
	else if (bisestile == 0  ) M = 2;
	break;
      case 3:
	M = 3;
	break; 
      case 4:
	M = 6;break;
      case 5:
	M = 1;break;
      case 6:
	M = 4;break;
      case 7:
	M = 6;break;
      case 8:
	M = 2;break;
      case 9:
	M = 5;break;
      case 10:
	M = 0;break;
      case 11:
	M = 3;break;
      case 12:
	M = 5;break;
    }
    va = parseInt( ((year%100)%28)/4 );
    A = ((year%100)%28) + va;
    s1=parseInt(year/100);
    switch(s1%4){
      case 0:
	C = 6;break;
      case 1:
	C = 4;break;
      case 2:
	C = 2;break;
      case 3:
	C = 0;break;
    }
    weekday =(G+M+A+C)%7;
  }
}
else{  //visualizzo il calendario basandomi sulla data corrente
  var year = Calendar.getFullYear();	    // ritorna l'anno corrente
  var month = Calendar.getMonth();    // ritorna il mese corrente (0-11)
  var today = Calendar.getDate();    // ritorna il giorno corrente (1-31)
  var weekday = Calendar.getDay();    // ritorna il giorno della settimana corrente (1-7)
  var mese=month+1;
}

var DAYS_OF_WEEK = 7;    // variabile che delimita il numero di giorni in una settimana
var DAYS_OF_MONTH = 31;  //variabile che delimita il massimo numero di giorni di un mese
var cal;    // stringa contentente il codice finale della pagina


Calendar.setDate(1);    // Inizializza il calendario al giorno 1
Calendar.setMonth(month);    // inizializza il calendario al mese selezionato
Calendar.setFullYear(year);  //inizializza l'anno all'anno selezionato




/* variabili per la formattazione della tabella*/

var url= '../jsp/listaeventi.jsp?year='+year+'&month='+mese+'&day='   //indirizzo per la visualizzazione degli eventi
var TR_start = '<TR>';  //inizio t-riga
var TR_end = '</TR>';	//fine t-tiga
var highlight_start = '<TD WIDTH="45" ><TABLE align=center CELLSPACING=0 BORDER=2 BGCOLOR=DEDEFF BORDERCOLOR="red"><TR><TD WIDTH=45><B><a href="'+url; //inizio TD per il giorno da evidenziare
var highlight_end   = '</a></TD></TR></TABLE></B>'; //fine del TD per il giorno da evidenziare
var TD_start = '<TD width="30"><a href="'+ url;  //Inizio TD per gli elementi con link
var TD_end = '</A></TD>'; //fine TD per gli elementi con link
var TD_start_no = '<TD WIDTH="30"><CENTER>';  //Inizio TD per gli elementi senza link
var TD_end_no = '</CENTER></TD>';  //fine TD per gli elementi senza link



/* Inizio della scrittura del codice del calendario*/
cal ='<!DOCTYPE html><html><head><title>Home Page</title></head><body>'
cal +=  '<TABLE align=center BORDER=1 CELLSPACING=1 CELLPADDING=0 BORDERCOLOR=BBBBBB><TR><TD>';
cal += '<TABLE align=center BORDER=1 CELLSPACING=3 CELLPADDING=2>' + TR_start;
cal += '<TD COLSPAN="' + DAYS_OF_WEEK + '" BGCOLOR="#FFFF00"><CENTER><B>';
cal += month_of_year[month]  + '   ' + year + '</B>' + TD_end + TR_end;  //scrittura del mese e dell'anno selezionato
cal += TR_start;



// Ciclo per la scrittura dei giorni della settimana
for(index=0; index < DAYS_OF_WEEK; index++){
  cal += TD_start_no + day_of_week[index]  + TD_end_no;
}

cal += TD_end + TR_end;
cal += TR_start;

// Riempimento di spazi vuoti delle celle antecedenti il giorno della settimana selezionato
for(index=0; index < Calendar.getDay(); index++){
  cal += TD_start_no + ' ' + TD_end_no;
}

//-------------------------Calcolo del numeri di giorni di cui è composto il mese corrente----------------------------
switch(month){
  case 3: //aprile
  case 5: //giugno
  case 8: //settembre
  case 10: //novembre
    DAYS_OF_MONTH=30;
    break;
  case 1: //febbraio
    if(year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) //bisestile
      DAYS_OF_MONTH=29;
    else
      DAYS_OF_MONTH=28; //non bisestile
    break;
  default:
    DAYS_OF_MONTH=31; //gennaio,marzo,maggio,luglio,agosto,ottobre,dicembre
    break;
}
    

// Ciclo per la stampa di tutti i giorni del calendario
for(index=0; index < DAYS_OF_MONTH; index++){
  //if( Calendar.getDate() > index ){
    //ritorna il prossimo giorno della settimana da stampare
    week_day =Calendar.getDay();
    // Inizio di una nuova t-riga se è il primo giorno della settimana
    if(week_day == 0){
      cal += TR_start;
    }//se non sono finiti i giorni della settimana da stampare stampa il giorno
    if(week_day != DAYS_OF_WEEK){
      // recupero il giorno corrente
      var day  = Calendar.getDate();
      // Evidenzia e stampa il giorno se è il giorno da me selezionato precedentemente altrimenti
      if( today==Calendar.getDate() ){
	cal += highlight_start + day +'"style="text-decoration:none">'+ '<center>' + day + '</center>' + highlight_end + TD_end_no;
      }
      // stampa il giorno
      else{
	cal += TD_start + day + '"style="text-decoration:none">' + '<center>' + day + '</center>' + TD_end;
      }
    }
    // chiudo la riga se è finita la settimana
    if(week_day == DAYS_OF_WEEK){
      cal += TR_end;
    }
  //}
  // incremento il giorno fino alla fine del mese
  Calendar.setDate(Calendar.getDate()+1);
  
}// end for loop

//-------------------combobox per la selezione di giorno,mese e anno------------------------- 
var i=0;
var x=1;
cal += '</TD></TR></TABLE></TABLE><BR>';
cal+='Seleziona Una Data:';
cal+='<form name="Boxform" align="center" method="POST" action="../jsp/redirectcalendario.jsp">';
cal+='<select name = Boxgiorno>';
cal+='<option></option>';

for(i=1;i<=31;i++){
  cal+='<option value="'+i+'">'+i+'</option>';
}
cal+='</select>';
cal+='<select name=Boxmese>';
cal+='<option></option>';

for(i=0,x=1;i<12;i++,x++){
  cal+='<option value="'+x+'">'+month_of_year[i]+'</option>';
}
cal+='</select>';
cal+='<select name = Boxanno>';
cal+='<option></option>';
corrente = new Date()
for(i=corrente.getFullYear()-5;i<=corrente.getFullYear()-(-30);i++){      //range di anni compreso tra 5 anni precedenti al corrente e 30 anni superiori al corrente
  cal+='<option value="'+i+'">'+i+'</option>';
}
cal+='</select>';
cal+='<input type="submit" value="Seleziona Data"/>';
cal+='</form>';
cal+='<br>';
cal+='<button onclick="window.location=\'../static/calendario.html\'">Data Corrente</button>';
cal+='&emsp;';
cal+='<button onclick="window.location=\'../jsp/rubrica.jsp\'">Rubrica</button>';
cal+='&emsp;';
cal+='<button onclick="window.location=\'../jsp/logout.jsp\'">Logout</button>';
cal+='</body></html>'
//  Stampa Calendario
document.write(cal);


