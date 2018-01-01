var directionsDisplay;
var directionsService = new google.maps.DirectionsService();
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
  var address="Napoli"
// si richiama il metodo geocode che servirà a trasformare l'indirizzo in coordinate
  
  directionsDisplay = new google.maps.DirectionsRenderer();
 
  geocoder.geocode( { 'address': address}, function(results, status) {
     if (status == google.maps.GeocoderStatus.OK) { //se la geocodifica ha avuto successo
      var mapOptions = {//settiamo le opzioni per la configurazione della mappa 
	zoom: 12,
	center:results[0].geometry.location,//il centro  sarà il risultato della geocodifica
	mapTypeId: google.maps.MapTypeId.ROADMAP
      };
      //istanziamo la mappa
      map = new google.maps.Map(document.getElementById("map_canvas"), mapOptions);
      directionsDisplay.setMap(map);
    }
    else {//Errore in caso di codifica non riuscita
      alert("Geocode was not successful for the following reason: " + status);
    }
  }); 
  calcRoute();
}




function calcRoute() {
  //var selectVehicle = document.getElementById('vehicle').value;
  var selectedMode = "DRIVING"
  var start = document.getElementById('loc').innerHTML;
  var end = document.getElementById('end').innerHTML;
  var request = {
      origin:start,
      destination:end,
	  provideRouteAlternatives:true,
      travelMode: google.maps.TravelMode[selectedMode],
      transitOptions: {
    	departureTime: new Date(),
      },
	  //google.maps.TransitLine
      //transitOptions: google.maps.vehicle.type.[selectVehicle]
  };
  directionsService.route(request, function(response, status) {
    if (status == google.maps.DirectionsStatus.OK) {
      directionsDisplay.setDirections(response);
    }
  });
}
