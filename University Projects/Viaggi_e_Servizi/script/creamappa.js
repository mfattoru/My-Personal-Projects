var directionsDisplay;
var directionsService = new google.maps.DirectionsService();
var map;
var happy;
var sad;

var markers=new Array();


function initialize() {
	var i=0;
	var index=0;
	var locations = new Array();
	var LatEmote = new Array(40.852217,40.852254,40.849170,40.849349,40.857772,40.849057,40.849187,40.846281,40.846703,40.851401,40.852344,40.853090,40.847377,40.848903,40.845697);
	var LangEmote = new Array(14.266481,14.271602,14.269005,14.260079,14.272396,14.257613,14.254491,14.256840,14.259812,14.256251,14.259480,14.250221,14.265617,14.269136,14.262645);
	var happy = {url: '../images/maps/xfelice.png',};
	var sad = {url: '../images/maps/xtriste.png'};
	var love = {url: '../images/maps/xinnamorato.png'};
	
	for(i=0; i < LatEmote.length; i++){
		locations[i] = new google.maps.LatLng(LatEmote[i],LangEmote[i]);
		index++;
	}

	
	directionsDisplay = new google.maps.DirectionsRenderer();
	var monte = new google.maps.LatLng(40.8490531, 14.257604);
	var mapOptions = {
		zoom:14,
		mapTypeId: google.maps.MapTypeId.ROADMAP,
		center: monte
	}
 
	map = new google.maps.Map(document.getElementById('map_canvas'), mapOptions);
	directionsDisplay.setMap(map);
	directionsDisplay.setPanel(document.getElementById('directions-panel'));
	
	for(i=0; i < locations.length; i++){
		if(i < 5){
			var marker = new google.maps.Marker({ 
				position: locations[i],
				map: map, 
				title: 'Sono molto felice',
				animation: google.maps.Animation.DROP,
				icon:happy,
			});
		}
		else if(i<10){
			var marker = new google.maps.Marker({ 
				position: locations[i],
				map: map, 
				title: 'Sono triste',
				animation: google.maps.Animation.DROP,
				icon:sad,
			});
		}
		else{
			var marker = new google.maps.Marker({ 
				position: locations[i],
				map: map, 
				title: 'Innamorato perso',
				animation: google.maps.Animation.DROP,
				icon:love,
			});
		}
		markers[i]=marker;
	}
}

function calcRoute() {
  //var selectVehicle = document.getElementById('vehicle').value;
  var selectedMode = document.getElementById('mode').value;
  var start = document.getElementById('loc').value;
  var end = document.getElementById('end').value;
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
