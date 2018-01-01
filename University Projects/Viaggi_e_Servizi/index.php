<? session_start() ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
	<!--
	Design by Free CSS Templates
	http://www.freecsstemplates.org
	Released for free under a Creative Commons Attribution 2.5 License
	
	Name       : UpRight 
	Description: A two-column, fixed-width design with dark color scheme.
	Version    : 1.0
	Released   : 20130526
	
	-->
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<title>Monte di pietà - Info e car pooling</title>
	<meta name="keywords" content="" />
	<meta name="description" content="" />
	<link href="css/default.css" rel="stylesheet" type="text/css" media="all" />
	<!--[if IE 6]>
<link href="default_ie6.css" rel="stylesheet" type="text/css" />
<![endif]-->
</head>
<body>
	<div id="header" class="container">
		<div id="logo">
			<a href="index.php"><img src="images/logo.jpg" /></a>
		</div>
		<div id="menu"> 
			<ul>
				<li class="current_page_item"><a href="index.php" accesskey="1" title="">Homepage</a></li>
				<li><a href="/php/about.php" accesskey="2" title="">About</a></li>
				<li><a href="/php/calendario.php" accesskey="3" title="">Calendario</a></li>
				<li><a href="/php/carhome.php" accesskey="4" title="">Car Pooling</a></li>
				<li><a href="/php/indicazioni.php" accesskey="5" title="">Come Arrivare</a></li>
			</ul>
		</div>
		<div id="login">
			<?include "php/giulogin.php";?>
		</div>
	</div>
	
	<div id="welcome" class="wrapper-style1">
		<header class="title">
			<h2>Monte Di Pietà</h2>
			<span class="byline">Servizi di informazione e car pooling per studenti universitari</span> </header>
		<a href="#" class="image image-full"><img src="images/4480-Monte_di_Piet_C3_A02.jpg" alt="" /></a>
		<p>Benvenuto! Questo sito è un punto di incontro per gli studenti universitari della Federico II di Napoli.
			 Gli studenti interessati a raggiungere la sede di Monte di Pietà possono usufruire del <strong>calendario 
			 interattivo</strong> per reperire o condividere informazioni sul traffico, la viabilità e lo stato dei 
			 trasporti pubblici.
			 Inoltre questa è una piattaforma social per il <strong>car pooling</strong> ovvero la condivisione 
			 di automobili da parte degli studenti che affrontano il viaggio con lo scopo di abbattere i costi 
			 di spostamento e promuovere la mobilità sostenibile.</p>
	</div>
	<div id="portfolio" class="wrapper-style1">
		<header class="title">
			<h2>CENTRO SERVIZI</h2>
			<span class="byline">Scopri i servizi che offriamo ed entra a far parte della comunità</span> </header>
		<div id="column1">
			<p><a href="/php/calendario.php" class="image image-full"><img src="images/pic02.jpg" alt="" /></a></p>
			<p>Consulta il nostro calendario per leggere le informazioni sul traffico, la viabilità e lo stato dei 
			 trasporti pubblici nel giorno che desideri.<br /><br /></p>
		</div>
		<div id="column2">
			<p><a href="#" class="image image-full"><img src="images/pic03.jpg" alt="" /></a></p>
			<p>Cerca o offri un posto auto per raggiungere l'università. Consulta i pareri di chi viaggia 
				in compagnia oppure lascia un feedback per il viaggio 
				a cui hai partecipato.</p>
		</div>
		<div id="column3">
			<p><a href="/php/indicazioni.php" class="image image-full"><img src="images/pic04.jpg" alt="" /></a></p>
			<p>Consulta una rapida guida su come arrivare a Monte di Pietà. Sono inoltre disponibili i consigli 
				degli studenti e una selezione di contatti utili.</p>
		</div>
		<div id="column4">
			<p><a href="/php/registrazione.php" class="image image-full"><img src="images/pic05.jpg" alt="" /></a></p>
			<p>Se sei uno studente della Federico II e vuoi usufruire di tutti i servizi a te riservati registrati 
				al sito oppure effettua il login.<br /><br /></p>
		</div>
	</div>
	<?include "php/sidebar.php";?>
	<div id="footer" class="container">
		<p>Informatica e Culture Digitali | Università degli Studi di Napoli Federico II</p>
		<p>&copy; 2013 Sitename.com. | Photos by <a href="http://fotogrph.com/">Fotogrph</a> | Design by <a href="http://www.freecsstemplates.org/" rel="nofollow">FreeCSSTemplates.org</a>.</p>
	</div>
</body>
</html>