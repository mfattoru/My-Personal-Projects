
/* 
 * La funzione Initialize si occupa di recuperare un indirizzo dal codice HTML,
 * effettuare la geocodifica di quest'ultimo, instanziare una mappa centrandola 
 * nell'indirizzo recuperato e lì posizionarvi un marker.
 */
function initialize() {
  var map;
//   viene instanziata un elemento della classe Geocoder
  var geocoder = new google.maps.Geocoder();
//   recuperiamo dal codice HTML l'elemento con Id luogo
  var address=document.getElementById("luogo").innerHTML;
// si richiama il metodo geocode che servirà a trasformare l'indirizzo in coordinate
  geocoder.geocode( { 'address': address}, function(results, status) {
     if (status == google.maps.GeocoderStatus.OK) { //se la geocodifica ha avuto successo
      var mapOptions = {//settiamo le opzioni per la configurazione della mappa 
	zoom: 8,
	center:results[0].geometry.location,//il centro  sarà il risultato della geocodifica
	mapTypeId: google.maps.MapTypeId.ROADMAP
      };
      //istanziamo la mappa
      map = new google.maps.Map(document.getElementById("map_canvas"), mapOptions);
      marker= new google.maps.Marker({//instanziamo e posizioniamo un marker all'indirizzo geocodificato
	map: map,
	position: results[0].geometry.location
      });
    }
    else {//Errore in caso di codifica non riuscita
      alert("Geocode was not successful for the following reason: " + status);
    }
  }); 
}
