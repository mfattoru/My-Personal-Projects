<?php
include '../dbconnect.php';
	$query=\"INSERT INTO Viaggi (partenza,destinazione,matricola,NumPosti,note,data,costomin,costomax,titolo) VALUES ('".$_GET['partenza']."','".$_GET['a']."','".$_SESSION['matricola']."','".$_GET['posti']."','".$_GET['note']."','".$_GET['data']."','".$_GET['cmin']."','".$_GET['cmax']."','".$_GET['descr']."')";
	if(mysql_query($query))
		print("<p>Inserimento effettuato</p>");
	else
		print("<p>Errore inserimento NON effettuato</p>");
?>