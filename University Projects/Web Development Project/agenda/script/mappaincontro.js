var map;
var indirizzi=new Array();
var flag=0;
/*rappresenta il numero di geocodifiche portate a termine viene utilizzata per 
 * essere sicuri che la funzione PosizionaMarker sia invocata solo quando sono
 * state portate a termine tutte le geocodifiche.
 */
var NumGeocode = 0;
var ciclo;
/*
 * La funzione initialize si occupa di recuperare i luoghi dal codice HTML
 *di effettuare la geocodifica di questi ultimi e di sommare tutte le latitudini
 * e le longitudini.
*/
function initialize( numLuoghi) {
  var lat =0;
  var lng =0;
  var i=0;
  var address;
//  istanziamo un elemento della classe Geocoder
  var geocoder = new google.maps.Geocoder();
//  recuperiamo tutti i luoghi dal codice HTML e li inseriamo in un array
  for(i = 0; i < numLuoghi; i++){
    indirizzi[i] = document.getElementById( i.toString() ).value;
  }
//  per ognuno dei luoghi effettuiamo la geocodifica 
  for(i=0; i < indirizzi.length; i++){
    address = indirizzi[i];
    geocoder.geocode( { 'address': address}, function(results, status) {
    if (status == google.maps.GeocoderStatus.OK) {
	lat = lat + results[0].geometry.location.lat();//somma delle latitudini
	lng = lng + results[0].geometry.location.lng();//somma delle longitudini
	NumGeocode++;
      }
      else {
	alert("Geocode was not successful for the following reason: " + status);
      }
      
    });
  }
/*Poichè le richieste ai server di Google sono asincrone e per tanto non ci è dato di conoscere
* con esattezza il momento dell'avvenuta risposta invochiamo la funziona PosizionaMarker a 
* intervalli di dieci milisecondi controllando che effettui i suoi compiti solo al termine 
* di tutte le operazioni di Geocodifica
*/
ciclo=setInterval(function (){PosizionaMarker(lat,lng,NumGeocode)},10);
}

/*
 * La funzione PosizionaMarker controlla che tutte le operazioni di geocodifica siano terminate
 * e in caso affermativo calcolerà il baricentro del poligono avente per vertici i luoghi geocodificati  
*/
function PosizionaMarker(lat,lng,num) {
    if(num == indirizzi.length){
     // istanziamo un nuovo geocoder
     var geocoder = new google.maps.Geocoder();
     //calcoliamo la latitudine e la longitudine del baricentro
     lat=lat/indirizzi.length;
     lng=lng/indirizzi.length;
     //codifichiamo la latitudine e la longitudine in un indirizzo
     var coordinate=new google.maps.LatLng(lat,lng);
     geocoder.geocode( { 'latLng': coordinate}, function(results, status) {
       //se la codifica ha avuto successo
       if (status == google.maps.GeocoderStatus.OK) {
	if(results[1]){
	  //riempiamo il campo con id luogo con l'indirizzo del baricentro
 	  document.getElementById("Luogo").value = results[1].formatted_address; 
	 // settiamo le opzioni della mappa centrandola nel baricentro
	  var mapOptions = {
	    zoom: 8,
	    center:coordinate,
	    mapTypeId: google.maps.MapTypeId.ROADMAP
	  };
	  //istanziamo la mappa
	  map = new google.maps.Map(document.getElementById("map_canvas"), mapOptions);
	  //istanziamo e posizioniamo il marker
	  var marker= new google.maps.Marker({
	    map: map,
	    position: coordinate
	  });
	}
      }
      else {
	alert("Geocode was not successful for the following reason: " + status);
      }
    });
     clearInterval(ciclo);
   }
}

