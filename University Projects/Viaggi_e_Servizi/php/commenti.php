<!DOCTYPE html>

<html>

<head>
	<style type="text/css">
		input[type="submit"] , textarea[name="messaggio"], .riga {
			border: 4px solid rgba(0,0,0,0.1);
			padding: 8px 10px;
			-webkit-border-radius: 5px;
			-moz-border-radius: 5px;
			border-radius: 5px;
			outline: 0;
		}
		textarea{
			resize:none;
			width:350px;
		}
		.riga{
			width:350px;
			text-align:left;	
		}
		div#comm.cella a{
			text-decoration: none;
			color:#39599F;
		}
		div.cella{
			overflow:auto;
			word-wrap:break-word;
		}
		#comm{
			text-transform:capitalize;
			font-weight:bold;
		}	
		img{
			border:0;
		}
	</style>
	
</head>

<body>
	<?php
		session_start();
		if($_SESSION['matricola']){
			include '../dbconnect.php';
			$imprevisto = $_GET['imprevisto'];
			$matricola = $_SESSION['matricola'];
			$commento = $_POST['messaggio'];
			if($commento){
				$query='INSERT INTO Commenti_Imprevisti (IdImprevisto,matricola,testo) VALUES ("'.$imprevisto.'","'.$matricola.'","'.$commento.'")';
				$result = mysql_query($query);
			}
			$query="SELECT IdCommento,matricola,testo,N_piace,N_nopiace FROM Commenti_Imprevisti WHERE IdImprevisto=".$imprevisto." ORDER BY data";
			$result = mysql_query($query);
			print('<CENTER><DIV class="tabella">');
			while($resultset = mysql_fetch_array($result)){
				$query2="SELECT nome,cognome FROM Utente WHERE matricola=".$resultset[1];
				$result2 = mysql_query($query2);
				$resultset2 = mysql_fetch_array($result2);
				print('<DIV class="riga">');
				print('<DIV id="comm" class="cella"><A href="../profilopubblico.php?matricola='.$resultset[1].'">'.$resultset2[0].' '.$resultset2[1].'</A></DIV>');  //nome e cognome di chi commenta
				print('<DIV class="cella">'.$resultset[2].'</DIV>');	//commento
				print('<DIV class="cella"> <A href="piace.php?id='.$resultset[0].'&piace=y&imp='.$imprevisto.'"><img src="../images/piace.jpg" width="15" height="15"></A> '.$resultset[3].' <A href="piace.php?id='.$resultset[0].'&imp='.$imprevisto.'"><img src="../images/nopiace.jpg" width="15" height="15"></A> '.$resultset[4].'</DIV>');
				print('</DIV><br>');
			}
			print("</DIV>");
			
			print('<B>Inserisci Un Commento</B>');
			print('<form  name="comment" action="commenti.php?imprevisto='.$imprevisto.'" method="post">');
			print('<textarea name="messaggio" cols="30" rows="10" maxlength="500"></textarea><br>');
			print('<input type="submit" value="Aggiungi Commento">');
			print('</form></CENTER>');	 
		}
		else{ //utente non loggato
			header("Location: ../index.html");
		}
	?>
</body>
</html>
