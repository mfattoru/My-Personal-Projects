<!DOCTYPE html>

<?php
	//check that user is logged in
	//if($_SESSION['matricola']){
	    $viaggio = $_GET['viaggio'];
	    
	    //connect to database
	    include '../dbconnect.php';

	    //make query
	    $query ="SELECT * FROM Viaggi V JOIN Utente U ON V.matricola = U.matricola WHERE IdViaggio='".$viaggio."'";
    
	    //execute query
	    $result = mysql_query($query);

	    //fetch result
	    $row = mysql_fetch_array($result);
	    //print("coglione ".$row[partenza]." bho");
	 //}
//echo "ciao mondo";
?>

<html>

    <head>
		<title>Dettagli Viaggio</title>
		<script src="https://maps.googleapis.com/maps/api/js?key=AIzaSyAzqsLaK6Yo3veuvVOIztc3zmlyqaBCzXY&sensor=false"></script>
		<script src="../script/mappaviaggio.js" type="text/javascript"></script>
		
		<link href="../css/smoothness/jquery-ui-1.10.3.custom.css" rel="stylesheet">
		<script src="../script/jquery-1.9.1.ac.js"></script>
		<script src="../script/jquery-ui.ac.js"></script>
		<script src="../script/autocomplete.js"></script>
		<link href="../css/indicazioni.css" rel="stylesheet" type="text/css" media="all" >

		<style>
		    .bordato{
			background-color: #39599F;
			font-weight: bold;
			color: white;
			height:30px;
			border: solid 1px #fff;
			border-radius: 16px;  
			box-sizing: border-box;
			padding-left: 10px;
			padding-right: 10px;
			padding-top: 2px;
			padding-bottom: 2px;
		    }
		    
		    .bordato, .bordato:-moz-placeholder {
			color: white;
		    }
		 
		    .bordato, .bordato::-webkit-input-placeholder {
			color: white;
		    }

		    #note{
			background-color: #39599F;
			font-weight: bold;
			color: white;
			border: solid 1px #fff;
			border-radius: 16px;  
			box-sizing: border-box;
			padding-left: 10px;
			padding-right: 10px;
			padding-top: 2px;
			padding-bottom: 2px;
			min-height: 100px;
			max-height:350;
			width: 200px; 
		    }
		</style>
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
					<li><a href="indicazioni.php" accesskey="5" title="">Come Arrivare</a></li>
				</ul>
			</div> 
			<div id="login">
				<?include "giulogin.php";?>
			</div>
		</div>
		<div id="welcome" class="wrapper-style1">
		<header class="title">
			<h2>Dettagli viaggio</h2>
			
		</div><br>
		<h1 align="center">
			<center>
			<DIV id="tab" class="tabella">
				<DIV class="riga">
					<DIV id="menu_map" class="cella">
						<DIV class="topside">
						<B>Partenza:</B> <br><span id="loc" class="bordato"><?print($row[partenza]);?></span><BR><br>
						<B>Destinazione:</B> <br><span id="end" class="bordato"><?print($row[destinazione]);?></span><br><br>
						<B>Automobilista:</B><br><span class="bordato"><?print($row[nome]." ".$row[cognome]);?></span><br>
						<B>Data:</B> <br><span class="bordato"><?print($row[data]);?></span><br><br>
						<B>Ore:</B> <br><span class="bordato"><?print($row[ora]);?></span><br><br>
						<B>Note:</B> <br><div id="note"><?print($row[note]);?></div><br><br>
						</DIV>
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





