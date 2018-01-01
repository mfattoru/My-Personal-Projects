/*
* Questa funzione ha il compito di analizzare i campi OraInizio e OraFine contenuti in alcune form dell'applicazione
* la funzione prenderà in ingresso dai rispettivi campi delle form i valori inseriti e controllerà che l'ora di fine 
* dell'evento non sia mai inferiore all'ora di inizio dell'evento.nel caso in cui il controllo vada a buon fine la funzione 
* ritornerà true e quindi la form procederà al submit dei dati,altrimenti la funzione mostrerà un messaggio di errore 
* tramite la funzione alert suggerendo all'utente di controllare i campi inseriti
*/

function controllo(){ 
  var pattern;
  with(document.checkOra) { //ricerca le variabili all'interno del form checkOra
    if(!checkOra(OraInizio.value,OraFine.value)){
      return false 
    }
  } 
  return true; 
} 

//converto l'orario in secondi per poi effettuarne un confronto
function checkOra(Inizio,Fine){
  var Start=Inizio.split(":");  //divide il campo Inizio(contenente un ora) in ora,minuti e secondi e li assegna all'array Start
  var End=Fine.split(":");	 //divide il campo Fine(contenente un ora) in ora,minuti e secondi e li assegna all'array End
  var SecStart;
  var SecEnd;
  if(Start[2]==null){ //se l'utente non ha inserito i secondi,considera i secondi pari a zero
    Start[2]=0;
  }
  if(End[2]==null){	//se l'utente non ha inserito i secondi,considera i secondi pari a zero
    End[2]=0;
  }
  SecStart=Start[0]*3600 + Start[1]*60 + Start[2];  //trasforma l'orario in secondi
  SecEnd=End[0]*3600+ End[1]*60 + End[2];	     //trasforma l'orario in secondi
  if(SecStart<SecEnd){	//confronta i secondi di entrambe gli orari
    return true;
  }
  else{ //se l'ora finale è antecedente all'ora iniziale allora ritorna un errore
    alert("Controlla l'ora di inizio e di fine dell'evento");
    return false;
  }
}