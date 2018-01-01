//  Impostazione Array
var day_of_week = new Array('Dom','Lun','Mar','Mer','Gio','Ven','Sab');
var month_of_year = new Array('Gennaio','Febbraio','Marzo','Aprile','Maggio','Giugno','Luglio','Agosto','Settembre','Ottobre','Novembre','Dicembre');

//  Dichiarazione ed inizializzazione variabili
var Calendar = new Date();
var visualday; //variabile utilizzata per il corretto allineamento dei div.permette di inserire 01 e non 1 all'interno delle celle


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
var month = args['mese']-1;    	    // Ritorna il mese selezionato (1-12)
var Calendar = new Date();





//--------------------------------------se vengono passati dei parametri in input--------------------------------
//nel caso in cui l'utente abbia selezionato dalla pagina calendario una data diversa da quella corrente,dovremo
//calcolarci alcuni adti necessari alla corretta inizializzazione del calendario
//---------------------------------------------------------------------------------------------------------------
if(year!=null && month!=null){
  
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
//-------------------------------------calcolo del mese successivo e precedente------------------------------------

if(mese==1){
	var nextmonth = parseInt(mese)+1;		
	var previousmonth =12;
	var nextyear=year;			    
	var previousyear=parseInt(year)-1;
}
else if(mese==12){
	var nextmonth = 1;		
	var previousmonth =parseInt(mese)-1;
	var nextyear=parseInt(year)+1;			    
	var previousyear=year;
}
else{		//shift desto e sinistro di un mese dove nn è necessario cambiare anno
	var nextmonth = parseInt(mese)+1;		
	var previousmonth =parseInt(mese)-1;
	var nextyear=year;			    
	var previousyear=year;
}





var DAYS_OF_WEEK = 7;    // variabile che delimita il numero di giorni in una settimana
var DAYS_OF_MONTH = 31;  //variabile che delimita il massimo numero di giorni di un mese
var cal;    // stringa contentente il codice finale della pagina


Calendar.setDate(1);    // Inizializza il calendario al giorno 1
Calendar.setMonth(month);    // inizializza il calendario al mese selezionato
Calendar.setFullYear(year);  //inizializza l'anno all'anno selezionato




/* variabili per la formattazione della tabella*/
var width_popup=500;
var height_popup=500;
var ris_top = Math.floor((screen.height)/2)-(height_popup/2);
var ris_left = Math.floor((screen.width)/2)-(width_popup/2);
var url= '../php/imprevisti.php?data='+year+'-'+mese+'-'   //indirizzo per la visualizzazione degli eventi
var TR_start = '<DIV  class="riga">';  //inizio t-riga
var TR_end = '</DIV>';	//fine t-tiga
var highlight_start = '<DIV id="selectedrow" class="cella"><B><a href="'+url; //inizio TD per il giorno da evidenziare
var highlight_end   = '</a></B></DIV>'; //fine del TD per il giorno da evidenziare
var TD_start = '<DIV class="cella"><a href="'+ url;  //Inizio TD per gli elementi con link
var TD_end = '</A></DIV>'; //fine TD per gli elementi con link
var TD_start_no = '<DIV id="empty" class="cella">';  //Inizio TD per gli elementi senza link
var TD_end_no = '</DIV>';  //fine TD per gli elementi senza link
var TD_start_week = '<DIV class="weekday">';  //Inizio TD per gli elementi senza link
var TD_end_week = '</DIV>';  //fine TD per gli elementi senza link
var popup_start = ' onclick="window.open(\'http:\/\/viaggieservizi.altervista.org\/php\/imprevisti.php?data='+year+'-'+mese+'-';
var popup_end ='\'';
var button_previous= '<DIV class="switch"> <a href="../php/redirectcalendario.php?anno='+ previousyear+'&mese='+previousmonth+'"> \< </a></DIV>';
var button_next= '<DIV class="switch"> <a href="../php/redirectcalendario.php?anno='+nextyear+'&mese='+nextmonth+'"> \> </a> </DIV>';

/* Inizio della scrittura del codice del calendario*/
cal ='<!DOCTYPE html><html><head><title>Home Page</title></head><body>'
cal += '<div id="tab" class="tabella"> <DIV class="riga" align="center">';

cal += button_previous;

cal += '<DIV id="testa" class="cella"><B>';
cal += month_of_year[month]  + '   ' + year + '</B>' + TD_end;  //scrittura del mese e dell'anno selezionato

cal += button_next + TR_end;

cal += TR_start;



// Ciclo per la scrittura dei giorni della settimana
for(index=0; index < DAYS_OF_WEEK; index++){
  cal += TD_start_week + day_of_week[index]  + TD_end_week;
}

cal += TR_end;
//cal += TR_start;

// Riempimento di spazi vuoti delle celle antecedenti il giorno della settimana selezionato
for(index=0; index < Calendar.getDay(); index++){
	if(index==0){ //inizia riga soltanto se sono presenti spazi vuoti da riempire
		cal += TR_start;
	}
	cal += TD_start_no + '00' + TD_end_no;
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
	  if(day <10){
		visualday= "0"+day;
	  }
	  else{
		visualday=day;
	  }
      // Evidenzia e stampa il giorno se è il giorno da me selezionato precedentemente altrimenti
      if( today==Calendar.getDate() ){
		cal += highlight_start + day + '"' + '"style="text-decoration:none">'+  visualday  + highlight_end;
      }
      // stampa il giorno
      else{
		cal += TD_start +day+ '"' +'"style="text-decoration:none">' + visualday + TD_end;
      }
    }
    // chiudo la riga se è finita la settimana
    if(week_day == DAYS_OF_WEEK-1){
      cal += TR_end;
    }
  //}
  // incremento il giorno fino alla fine del mese
  Calendar.setDate(Calendar.getDate()+1);
  
}// end for loop

if(Calendar.getDay()!=0){
	for(index=Calendar.getDay(); index < DAYS_OF_WEEK; index++){
		cal += TD_start_no + '00' + TD_end_no;
	}
}


cal += '</DIV></DIV></body></html>';
//  Stampa Calendario
document.write(cal);


