<?php
	session_start();
	if($_SESSION['matricola'] && $_GET['testo'] && $_GET['fonte']){
		$query="INSERT INTO Imprevisti (data,matricola,testo,fonte)  VALUES ('".$_GET['data']."','".$_SESSION['matricola']."','".$_GET['testo']."','".$_GET['fonte']."')";
		if( mysql_query($query) ){ 
			//if insert is successful
			echo"<div color='green'>Inserimento effettuato!</div>";
			//wait
			sleep(5);
			//and hide
			echo"<script type='text/javascript'>fumetto()</script>";
			header("Location: imprevisti.php?data=".$_GET['data']);
		}else{ 
			//if insert is unsuccessful
			echo"<div color='red'>'Errore! Inserimento non effettuato')</div>";
			//wait
			sleep(5);
			//remove incorrect data
			if(isset($_SESSION['testo']))
				unset($_SESSION['testo']);
			if(isset($_SESSION['fonte']))
				unset($_SESSION['fonte']);
			echo"<script type='text/javascript'>fumetto()</script>";
			//and return to insert menu
			header("Location: imprevisti.php?data=".$_GET['data']);
		}
	}else if($_SESSION['matricola']){
		$matricola = $_SESSION['matricola'];
		//insert form
		print("<div id='bubble' class='bubble-hide'>");
		print("	<button id='impbutton' onclick='fumetto()'>X</button>");
		print("	<form method='GET' action='imprevisti.php'>");
		print("		<br><label class='bubble' for='tipo'>Tipo:</label><br>");
		print("		<select name='tipo'>");
		print("			<option value='diservizio'>Disservizio</option>");
		print("			<option value='evento'>Evento</option>");
		print("			<option value='imprevisto'>Imprevisto</option>");
		print("		</select><br>");
		print("		<label class='bubble'  for='testo'>Descrizione: </label><br>");
		print("		<textarea name='testo' required maxlenght='50' rows='3' cols='25'></textarea><br>");
		print("		<label class='bubble'  for='fonte'>Fonte: </label><br><input type='text' required name='fonte'> <br>");
		print("		<label class='bubble'  id='qresult' visibility='hidden' for='result' visibility='hidden'></label>");
		print(" 	<input type='hidden' name='data' value='".$data."'>");
		print("		<button id='impbutton' type='submit'>Invia</button>");
		print("	</form>");
		print("</div>");
	}
?>