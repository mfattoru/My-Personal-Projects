
<!DOCTYPE html>
<html>
    <head>
	<script type="text/javascript">
	    var stile = "top=10, left=10, width=400, height=400, status=no, menubar=no, toolbar=no scrollbars=no";
 
	    function Popup(apri) {
		window.open(apri, "", stile);
	    }
	</script>

	<link href="../css/profilo.css" rel="stylesheet">
	<link href="../css/smoothness/jquery-ui-1.10.3.custom.css" rel="stylesheet">
	<script src="../script/jquery-1.9.1.js"></script>
	<script src="../script/jquery-ui-1.10.3.custom.js"></script>
	<script>
	    $(function() {		
		$( "#tabs" ).tabs();

	    });
	</script>
 
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<title>Monte di piet&agrave - Info e car pooling</title>
	<meta name="keywords" content="" />
	<meta name="description" content="" />
	<link href="../css/default.css" rel="stylesheet" type="text/css" media="all" />
	<link href="../css/sidebar.css" rel="stylesheet" type="text/css" media="all" />

	<!--[if IE 6]>
		<link href="default_ie6.css" rel="stylesheet" type="text/css" />
	<![endif]-->
    </head>

    <body>
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
		    <li><a href="indicazioni.php" accesskey="5" title="">Come Arrivare</a></li>
		</ul>
	    </div>
	    <div id="login">
		<?
		    include "giulogin.php";
		?>
	    </div>
	</div>
	<center><div id="middle">

	    <div class="profilo">
		<img src="../images/avatar/1.jpg" height="300" >
		<div class="dati">
		    <br><b>Nome:</b> Matteo
		    <br><b>Cognome:</b> Ricci
		    <br><b>CDL:</b> Culture Digitali
		    <br><b>Media Voti:</b> 4
		</div>
	    </div>

	    <div id="tabs">
		<ul>
		    <li><a href="#tabs-1">Offerte</a></li>
		    <li><a href="#tabs-2">Feedback</a></li>
		</ul>
		<div id="tabs-1">
		    <div class="viaggio">
			<div class="riga-1">
			    <div><b>Titolo:</b>Viaggio in facolta</div>
			    <div><b>Data:</b> 2013-07-30</div>
			    <div><b>Posti:</b> 3</div>
			</div>
			<div class="riga-2">
			    <div><b>Partenza:</b> Torre del greco</div>
			    <div><b>Destinazione:</b> Monte di pieta</div>
			</div>
			<div class="riga-3">
			    <div><b>Note:</b> incontro al casello autostradale di Torre del greco ore 07:00</div> 
			</div>
		    </div><br>

		    <div class="viaggio">
			<div class="riga-1">
			    <div><b>Titolo:</b> In segreteria</div>
			    <div><b>Data:</b> 2013-07-15</div>
			    <div><b>Posti:</b> 3</div>
			</div>
			<div class="riga-2">
			    <div><b>Partenza:</b> Torre del greco</div>
			    <div><b>Destinazione:</b> Segreteria Didattica</div>
			</div>
			<div class="riga-3">
			    <div><b>Note:</b> incontro al casello autostradale di Torre del greco ore 09:00</div> 
			</div>
		    </div><br>

		    <div class="viaggio">
			<div class="riga-1">
			    <div><b>Titolo:</b> Esame Sistemi multimediali</div>
			    <div><b>Data:</b> 2013-07-10</div>
			    <div><b>Posti:</b> 3</div>
			</div>
			<div class="riga-2">
			    <div><b>Partenza:</b> Torre del greco</div>
			    <div><b>Destinazione:</b> Monte di pieta</div>
			</div>
			<div class="riga-3">
			    <div><b>Note:</b> incontro al casello autostradale di Torre del greco ore 10:00</div> 
			</div>
		    </div><br>
	    
		</div>
		<div id="tabs-2">
		    <div class="modulo-feedback">
			<form name="FormFeedback" method="POST" action="lasciafeedback.php">
			    <textarea id="TestoFeedback" maxlenght="200" placeholder="Lascia un feedback..."></textarea>
			    <label>Voto: </label>
			    <select name="voto">
				<option value="1">1</option>
				<option value="2">2</option>
				<option value="3">3</option>
				<option value="4">4</option>
				<option value="5">5</option>
			    </select>
			    <input type="submit" value="invia">
			</form>
		    </div>

		    <div class="feedback">
			<div class="intestazione-left">
			    <div class="data-post-left">posted on 12-07-2013 at 13:00</div>
			    <div class="voto-post-left">Voto: 5</div>
			</div>
			<div class="mini-avatar-left">
			    <img src="../images/avatar/2.jpg" height="80px" width="60px">
			    Mario Verdi
			</div>
			<button class="tasto-left" type="button" onClick="Popup('commentifeedback.php?feedback=100')">Commenti</button>
			<div class="speech-bubble speech-bubble-left">E' bellissimo viaggiare con lui</div>
		    </div>
		    <div class="feedback">
			<div class="intestazione-right">
			    <div class="data-post-right">posted on 05-07-2013 at 13:00</div>
			    <div class="voto-post-right">Voto: 4</div>
			</div>
			<div class="mini-avatar-right">
			    <img src="../images/avatar/3.jpg" height="80px" width="60px">
			    Mara Bianchi
			</div>
			<button class="tasto-right" type="button" onClick="Popup('commentifeedback.php?feedback=100')">Commenti</button>
			<div class="speech-bubble speech-bubble-right">Puntuale ed efficiente!</div>
		    </div>
		    <div class="feedback">
			<div class="intestazione-left">
			    <div class="data-post-left">posted on 21-06-2013 at 13:00</div>
			    <div class="voto-post-left">Voto: 5</div>
			</div>
			<div class="mini-avatar-left">
			    <img src="../images/avatar/4.jpg" height="80px" width="60px">
			    Maria Gialli
			</div>
			<button class="tasto-left" type="button" onClick="Popup('commentifeedback.php?feedback=100')">Commenti</button>
			<div class="speech-bubble speech-bubble-left">Ottimo compagno di viaggio!</div>
		    </div>
		</div>
	    </div>
	</div></center>
	<?
	    include "sidebar.php";
	?>
	<div id="footer" class="container">
	    <p>Informatica e Culture Digitali | Università degli Studi di Napoli Federico II</p>
	    <p>&copy; 2013 Sitename.com. | Photos by <a href="http://fotogrph.com/">Fotogrph</a> | Design by <a href="http://www.freecsstemplates.org/" rel="nofollow">FreeCSSTemplates.org</a>.</p>
	</div>
    </body>
</html>