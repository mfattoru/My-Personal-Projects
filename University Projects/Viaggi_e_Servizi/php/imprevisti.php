<!DOCTYPE html>

<?php
    
    //keep date from request
    $data = $_GET['data'];
   
    //connect to database
    include '../dbconnect.php';
    
    //make query
    $query ="SELECT * FROM Imprevisti WHERE data='".$data."'";
    
    //execute query
    $result = mysql_query($query);
    
?>

<html>
<head>
	<link href="../css/calendario.css" rel="stylesheet" type="text/css" media="all" />
	<link href="../css/imprevisti.css" rel="stylesheet" type="text/css" media="all" />
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<title>Monte di piet&agrave - Info e car pooling</title>
	<meta name="keywords" content="" />
	<meta name="description" content="" />
	<link href="../css/default.css" rel="stylesheet" type="text/css" media="all" />
	<!--[if IE 6]>
		<link href="default_ie6.css" rel="stylesheet" type="text/css" />
	<![endif]-->
	<title>Home Page</title>
</head>

<body>
	<div id="header" class="container">
		<div id="logo">
			<a href="../index.php"><img src="../images/logo.jpg" /></a>
		</div>
		<div id="menu"> 
			<ul>
				<li ><a href="../index.php" accesskey="1" title="">Homepage</a></li>
				<li><a href="about.php" accesskey="2" title="">About</a></li>
				<li class="current_page_item"><a href="calendario.php" accesskey="3" title="">Calendario</a></li>
				<li><a href="carhome.php" accesskey="4" title="">Car Pooling</a></li>
				<li><a href="indicazioni.php" accesskey="5" title="">Come Arrivare</a></li>
			</ul>
		</div>
		<div id="login">
			<?include "giulogin.php";?>
		</div>
		<?include "sidebar.php";?>
	</div>
	<div id="welcome" class="wrapper-style1">
		<header class="title">
			<h2>Eventi Del giorno <?php echo date("d-m-Y", strtotime($_GET['data'])); ?> </h2>
			<span class="byline">Oggi nella tua citt&agrave </span> </header>
	</div>
	<div id='imprevisti-box'>
	<table id='imprevisti'>
	    <tr id='head'>
		<td id='top-left'><b>Data</b></td>
		<td><b>Testo</b></td>
		<td><b>Fonte</b></td>
		<td id='top-right'><b>Inserito da</b></td>
	    </tr>
	<?php
	    //fetch result and print on html document
	    while($resultset = mysql_fetch_array($result)){
			print("<tr id='row'>");
			print("<td>".$resultset[1]."</td>");
			print("<td>".$resultset[3]."</td>");
			print("<td>".$resultset[4]."</td>");
			print("<td>".$resultset[2]."</td>");
			print('<td><A href="/php/commenti.php?imprevisto='.$resultset[0].'">Commenta</A></td>');
			print("</tr>");
	    }
	?>
	</table>
	<?php
		session_start();
		if($_SESSION['matricola'] && $_GET['testo'] && $_GET['fonte']){
			$query="INSERT INTO Imprevisti (data,matricola,testo,fonte)  VALUES ('".$_GET['data']."','".$_SESSION['matricola']."','".$_GET['testo']."','".$_GET['fonte']."')";
			if( mysql_query($query) ){ 
				//if insert is successful
				echo"<div color='green'>Inserimento effettuato!</div>";
				//wait
				header("Location: imprevisti.php?data=".$_GET['data']);
			}else{ 
				//if insert is unsuccessful
				echo"<div color='red'>'Errore! Inserimento non effettuato')</div>";
			    //remove incorrect data
				if(isset($_SESSION['testo']))
					unset($_SESSION['testo']);
				if(isset($_SESSION['fonte']))
					unset($_SESSION['fonte']);
				header("Location: imprevisti.php?data=".$_GET['data']);
			}
		}else if($_SESSION['matricola']){
			$matricola = $_SESSION['matricola'];
			//insert form
			print("<div id='form'>");
			print("	<form method='GET' action='imprevisti.php'>");
			print("		<br><label for='tipo'>Tipo:</label><br>");
			print("		<select name='tipo'>");
			print("			<option value='diservizio'>Disservizio</option>");
			print("			<option value='evento'>Evento</option>");
			print("			<option value='imprevisto'>Imprevisto</option>");
			print("		</select><br>");
			print("		<label for='testo'>Descrizione: </label><br>");
			print("		<textarea name='testo' required maxlenght='50' rows='3' cols='25'></textarea><br>");
			print("		<label for='fonte'>Fonte: </label><br><input type='text' required name='fonte'> <br>");
			print("		<label id='qresult' visibility='hidden' for='result' visibility='hidden'></label>");
			print(" 	<input type='hidden' name='data' value='".$data."'>");
			print("		<button id='impbutton' type='submit'>Invia</button>");
			print("	</form>");
			print("</div>");
		}
	?>
	</div>
	<div id="footer" class="container">
		<p>Informatica e Culture Digitali | Universit&agrave degli Studi di Napoli Federico II</p>
		<p>&copy; 2013 Sitename.com. | Photos by <a href="http://fotogrph.com/">Fotogrph</a> | Design by <a href="http://www.freecsstemplates.org/" rel="nofollow">FreeCSSTemplates.org</a>.</p>
	</div>
</body>
</html>


