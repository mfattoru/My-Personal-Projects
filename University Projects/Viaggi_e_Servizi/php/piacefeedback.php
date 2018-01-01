<!DOCTYPE html>

<html>

<head>
</head>

<body>
	<?php
		session_start();
		if($_SESSION['matricola']){
			include '../dbconnect.php';
			$feed=$_GET['feed'];
			$idcommento = $_GET['id'];
			$piace = $_GET['piace'];
			$query="SELECT * FROM PiaceFeedback WHERE commento=".$idcommento." AND matricola=".$_SESSION['matricola'];
			$result = mysql_query($query);
			if(!mysql_fetch_array($result)){
				if($piace){
					$query="UPDATE Commenti_Utente SET N_piace=N_piace+1 WHERE IdCommento=".$idcommento;
					$result = mysql_query($query);
				}
				else{
					$query="UPDATE Commenti_Utente SET N_nopiace=N_nopiace+1 WHERE IdCommento=".$idcommento;
					$result = mysql_query($query);
				}
				$query="INSERT INTO PiaceFeedback VALUES (".$idcommento.",".$_SESSION['matricola'].")";
				$result = mysql_query($query);
				header("Location: /php/commentifeedback.php?feedback=".$feed);
			}
			header("Location: /php/commentifeedback.php?feedback=".$feed);
		}
		else{ //utente non loggato
			header("Location: ../index.html");
		}
	?>
</body>
</html>