<!DOCTYPE html>
<html>
    <head>
	<script type="text/javascript">
	    var stile = "top=10, left=10, width=400, height=400, status=no, menubar=no, toolbar=no scrollbars=no";
 
	    function Popup(apri) {
		window.open(apri, "", stile);
	    }
	</script>

	<link href="profilo.css" rel="stylesheet">
	<link href="css/smoothness/jquery-ui-1.10.3.custom.css" rel="stylesheet">
	<script src="script/jquery-1.9.1.js"></script>
	<script src="script/jquery-ui-1.10.3.custom.js"></script>
	<script>
	    $(function() {		
		$( "#tabs" ).tabs();

	    });
	</script>

	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<title>Monte di piet&agrave - Info e car pooling</title>
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
		<img src="images/logo.jpg" />
	    </div>
	    <div id="menu"> 
		<ul>
		    <li><a href="../index.html" accesskey="1" title="">Homepage</a></li>
		    <li><a href="/about.html" accesskey="2" title="">About</a></li>
		    <li><a href="/static/calendario.html" accesskey="3" title="">Calendario</a></li>
		    <li><a href="/php/carhome.php" accesskey="4" title="">Car Pooling</a></li>
		    <li><a href="/static/indicazioni.html" accesskey="5" title="">Come Arrivare</a></li>
		</ul>
	    </div>
	    <div id="login">
			<div style="width: 50px; float:left;">MATR</div><input style="width: 90px" type="text" />
			<br />
			<div style="width: 50px; float:left;">PASS</div><input style="width: 90px" type="password" />
			<input type="submit" value="Entra" />
		</div>
	</div>
	<center><div id="middle">
<?php
    session_start();
    //check that user is logged in
    if($_SESSION['matricola']){
	$matricola = $_GET['matricola'];
	include 'dbconnect.php';

/***********************************************************************************************************

			    USER INFORMATION
***********************************************************************************************************/

	//make query
	$query ="SELECT nome,cognome,cdl,media_feed FROM Utente WHERE matricola='".$matricola."'";
    
	//execute query
	$result = mysql_query($query);

	//fetch result
	$row = mysql_fetch_array($result);

	//show user information
	if($_SESSION['matricola'] == $matricola){
	    print("
		<div class=\"profilo\">
		    <img src=\"avatar.php?matricola=".$matricola."\" height=\"250\" width=\"200\">
		    <button type=\"button\" onClick=\"Popup('select_avatar.php')\">Cambia Avatar</button>
		    <br><b>Nome:</b> ".$row[0]."
		    <br><b>Cognome:</b> ".$row[1]."
		    <br><b>CDL:</b> ".$row[2]."
		    <br><b>Media Voti:</b> ".$row[3]."
		    <br><button type=\"button\" onClick=\"Popup('modifica.php')\">Modifica Dati</button>
		</div>");
	}
	else{
	    print("
		<div class=\"profilo\">
		    <img src=\"avatar.php?matricola=".$matricola."\" height=\"250\" width=\"200\">
		    <b>Nome:</b> ".$row[0]."
		    <b>Cognome:</b> ".$row[1]."
		    <b>CDL:</b> ".$row[2]."
		    <b>Media Voti:</b> ".$row[3]."
		</div>");
	}
/***********************************************************************************************************

			    TRAVEL INFORMATION
***********************************************************************************************************/
	//make query
	$query = "SELECT * FROM Viaggi WHERE matricola ='".$matricola."'";
	
	//execute query
	$result=mysql_query($query);

	//show travel information
	print("
	    <div id=\"tabs\">
		<ul>
		    <li><a href=\"#tabs-1\">Offerte</a></li>
		    <li><a href=\"#tabs-2\">Feedback</a></li>
		</ul>
		<div id=\"tabs-1\">");
	while($row=mysql_fetch_array($result)){
	    print("
		    <div class=\"viaggio\">
			<div class=\"riga-1\">
			    <div><b>Titolo:</b> ".$row['titolo']."</div>
			    <div><b>Data:</b> ".$row['data']."</div>
			    <div><b>Posti:</b> ".$row['NumPosti']."</div>
			</div>
			<div class=\"riga-2\">
			    <div><b>Partenza:</b> ".$row['partenza']."</div>
			    <div><b>Destinazione:</b> ".$row['destinazione']."</div>
			</div>
			<div class=\"riga-3\">
			    <div><b>Note:</b> ".$row['note']."</div>
			</div>
		    </div><br>
	    ");
	}
	print("
		</div>");
/***********************************************************************************************************

			    FEEDBACK INFORMATION
***********************************************************************************************************/
	print("
		<div id=\"tabs-2\">
		    <p>un giorno ci saranno i feedback</p>
		</div>
	    </div>\n");
    }
    else{
	print("sessione scadduta\n");
    }
?>
	</div></center>
	<div id="footer" class="container">
	    <p>Informatica e Culture Digitali | Università degli Studi di Napoli Federico II</p>
	    <p>&copy; 2013 Sitename.com. | Photos by <a href="http://fotogrph.com/">Fotogrph</a> | Design by <a href="http://www.freecsstemplates.org/" rel="nofollow">FreeCSSTemplates.org</a>.</p>
	</div>
    </body>
</html>