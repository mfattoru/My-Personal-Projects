<!DOCTYPE html>

<html>
    <head>
		<title>Info Contatto</title>
		<script src="https://maps.googleapis.com/maps/api/js?key=AIzaSyAzqsLaK6Yo3veuvVOIztc3zmlyqaBCzXY&sensor=false"></script>
		<script src="../script/creamappa.js" type="text/javascript"></script>
		
		<link href="../css/smoothness/jquery-ui-1.10.3.custom.css" rel="stylesheet">
		<script src="../script/jquery-1.9.1.ac.js"></script>
		<script src="../script/jquery-ui.ac.js"></script>
		<script src="../script/autocomplete.js"></script>
		
		<link href="../css/indicazioni.css" rel="stylesheet" type="text/css" media="all" >
    </head>
	<link href="../css/default.css" rel="stylesheet" type="text/css" media="all" >
	<body onload="initialize()">
		<div id="header" class="container">
			<div id="logo">
				<a href="../index.php"><img src="../images/logo.jpg" /></a>
			</div>
			<div id="menu">
				<ul> 
					<li><a href="../index.php" accesskey="1" title="">Homepage</a></li>
					<li><a href="about.php" accesskey="2" title="">About</a></li>
					<li><a href="calendario.php" accesskey="3" title="">Calendario</a></li>
					<li><a href="carhome.php" accesskey="4" title="">Car Pooling</a></li>
					<li class="current_page_item"><a href="indicazioni.php" accesskey="5" title="">Come Arrivare</a></li>
				</ul>
			</div> 
			<div id="login">
				<?include "giulogin.php";?>
			</div>
		</div>
		<div id="welcome" class="wrapper-style1">
		<header class="title">
			<h2>Pianifica il tuo viaggio</h2>
			<span class="byline">scegli il percorso migliore</span> </header>
			<p>Pianifica il tuo viaggio scegliendo quale mezzo utilizzare.in tre semplici passi,tramite la selezione del luogo di partenza,luogo di arrivo e mezzo che hai intenzione di utilizzare,ti verrà calcolato il miglior itinerario per raggiungere la segreteria o la tua sede universitaria nel minor tempo possibile.
			Inoltre tramite l'integrazione della mappa emozionale ti sarà possibile raggiungere luoghi basandosi sugli stati d'animo di altri utenti</p>
		</div><br>
		<h1 align="center">
			<center>
			<DIV id="tab" class="tabella">
				<DIV class="riga">
					<DIV id="menu_map" class="cella">
						<DIV class="topside">
						<B>Partenza:</B> <br><input type="text" id="loc" class="bordered"><BR>
						<B>Destinazione:</B> <br><select id="end" class="bordered">
									<option value="Monte di Pietà, NA, Italia">Monte Di Piet&agrave</option>
									<option value="Via Monteoliveto, 3 80134 Napoli, Italia">Segreteria didattica</option>
									<option value="Vico Fico Al Purgatorio, Napoli, NA">Zona Triste</option>
									<option value="Vico VII Duchesca, Napoli, NA">Zona felice</option>
									<option value="Via Antonietta de Pace, Napoli, NA">Zona Innamorata</option>

									<!--<option value="">vuoto</option>
									<option value="">vuoto</option> -->
								</select>
						<!--<input type="hidden" id="end" value="Monte di Pietà, NA, Italia"> -->
						<div id="panel">
							<B>Tipo Di Percorso:</B><br>
							<select id="mode" class="bordered" onchange="calcRoute();">
								<option value="DRIVING">In Auto</option>
								<option value="WALKING">A Piedi</option>
								<option value="TRANSIT">Trasporto Pubblico</option>
							</select>
						</div>
						<br>
						<CENTER><button type="button" class="bottone-invia" onclick="calcRoute();">Calcola Percorso</button></CENTER>
						<br>
						<!--<div id="mezzi">
							<b>Mezzo Di Trasporto Preferito: </b>
							<select id="vehicle" onchange="calcRoute();">
								<option value="BUS">Autobus</option>
								<option value="RAIL">Treno</option>
								<option value="TRAM">Tram</option>
								<option value="METRO_RAIL">Metropolitana</option>
							</select>
						</div> -->
						</DIV>
						<div id="directions-panel"></div>
					</DIV>
					<DIV id="map_canvas"></DIV>
					<!--<DIV class="riga">
						<div id="directions-panel" style="width: 500px; height: 400px;"></div>
					</DIV>-->
					
				</DIV>
			</DIV>
			</center>
		</h1>
		
		<?include "sidebar.php";?>
		<div id="footer" class="container">
			<p>Informatica e Culture Digitali | Universit&agrave degli Studi di Napoli Federico II</p>
			<p>&copy; 2013 Sitename.com. | Photos by <a href="http://fotogrph.com/">Fotogrph</a> | Design by <a href="http://www.freecsstemplates.org/" rel="nofollow">FreeCSSTemplates.org</a>.</p>
		</div>
    </body>
</html>
