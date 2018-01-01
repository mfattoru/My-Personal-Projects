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
		<link href="../css/default.css" rel="stylesheet" type="text/css" media="all" />
		<link href="../css/sidebar.css" rel="stylesheet" type="text/css" media="all" />
		<link href="../css/offro.css" rel="stylesheet">
		<link href="../css/smoothness/jquery-ui-1.10.3.custom.css" rel="stylesheet">
		<script src="../script/jquery-1.9.1.ac.js"></script>
		<script src="../script/jquery-ui.ac.js"></script>
		<script src="../script/autocomplete.js"></script>
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
                <li class="current_page_item"><a href="carhome.php" accesskey="4" title="">Car Pooling</a></li>
                <li><a href="indicazioni.php" accesskey="5" title="">Come Arrivare</a></li>
            </ul>
        </div>
        <div id="login">
            <?include "giulogin.php";?>
        </div>
    </div>
		<div id="welcome" class="wrapper-style1">
			<header class="title">
				<h2>Offri un viaggio</h2>
				<span class="byline">Organizzati con i tuoi colleghi per viaggiare.</span>
			</header>
			<?php
				if($_SESSION['matricola']){	
					/*Query execution*/
					$inserted="";
					if( $_POST['data'] ){
						include '../dbconnect.php';
						$query="INSERT INTO Viaggi (partenza,destinazione,matricola,NumPosti,note,data,costomin,costomax,titolo) VALUES ('".$_POST['partenza']."','".$_POST['destinazione']."','".$_SESSION['matricola']."','".$_POST['posti']."','".$_POST['note']."','".$_POST['data']."','".$_POST['cmin']."','".$_POST['cmax']."','".$_POST['titolo']."')";
						if(mysql_query($query))
							$inserted="Inserimento effetuato!";
						else
							$inserted="ERRORE inserimento NON effetuato!";
					}
				?>
			<p style="text-align:center;"> Ciao  <?php echo $nome; ?> 
						In questa sezione puoi rendere disponibile te ed il tuo mezzo di trasporto per uno o piu' viaggi <br><?php echo $inserted; ?></p>
			<article>
				<form class="registrazione" method="post" action="../php/offro.php">
					<fieldset>
						<p style="text-align:center;">
							<label for='titolo'>Titolo</label> 
							<input type='text' name='titolo' required placeholder='Breve descrizione'>
						</p>
						<p style="text-align:center;">
							<label for='data'>Data</label> 
							<input type='date' name='data' required placeholder='dd-mm-yyyy'>
						</p>
						<p style="text-align:center;">
							<label for='partenza'>Comune di partenza</label>
							<input id='loc' type='text' name='partenza' required placeholder='Partenza'>
						</p>
						<p style="text-align:center;">
							<label for='destinazione'>Destinazione</label> 
							<select name="destinazione">
								<option value="monte">Monte di pietà</option>
								<option value="segreteria">Segreteria</option>
							</select>
						</p>
						<p style="text-align:center;">
							<label for='posti'>Posti</label>
							<input type='number' min='1' name='posti' required placeholder='Disponibili'>
						</p>
						<p style="text-align:center;">
							<label for='cmin'>Costo minimo (euro)</label>
							<input type='number' name='cmin' min='0' required placeholder='A persona'>
						</p>
						<p style="text-align:center;">
							<label for='cmax'>Costo massimo (euro)</label>
							<input type='number' name='cmax' min='0' required placeholder='A persona'>
						</p>
						<p style="text-align:center;">
							<label for='note'>Note</label><br />
							<textarea name='note' rows='5' cols='20' placeholder='Info aggiuntive'></textarea>
						</p>
						<p style="text-align:center;" class="bottone">
								<br />
								<button class="bottone-invia" type="submit">Invia</button>
						</p>
					</fieldset>
				</form>
			</article>
			<?php
				}else
					print("<p>Sessione scaduta</p>");
			?>
		</div>
		<div id="sidebar">
			<?include("sidebar.php");?>
		</div>
		<div id="footer" class="container">
			<p>Informatica e Culture Digitali | Università degli Studi di Napoli Federico II</p>
			<p>&copy; 2013 Sitename.com. | Photos by <a href="http://fotogrph.com/">Fotogrph</a> | Design by <a href="http://www.freecsstemplates.org/" rel="nofollow">FreeCSSTemplates.org</a>.</p>
		</div>
	</body>
</html>