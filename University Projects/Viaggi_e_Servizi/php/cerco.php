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
	<link href="../css/offro.css" rel="stylesheet">

	
	<!--[if IE 6]>
	<link href="default_ie6.css" rel="stylesheet" type="text/css" />
	<![endif]-->
	
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
			<h2>Cerca un viaggio</h2>
			<span class="byline">Cerca tra le offerte di viaggio</span>
		</header>
		
		<?php
		    session_start();
		    if($_SESSION['matricola']) {
				// logged
                $oggi = date("Y-m-d");
				?>
				<p style="text-align: center;">Ciao <?echo $nome; ?>. Cerca tra gli annunci inseriti il viaggio condiviso
						selezionando il comune di partenza che preferisci e la data del viaggio.</p>
				<article>
					<form style="text-align: center;" class="registrazione" method="post" action="viaggi.php">
				        <fieldset>
				            <p style="text-align: center;">
				                <label for="partenza">Comune di partenza</label>
				                <input id='loc' type='text' name='loc' required placeholder='Partenza'>
				            </p>
				            <p style="text-align: center;">
				                <label for="destinazione">Destinazione</label>
				                <select name="destinazione">
							    	<option value="monte">Monte di pietà</option>
							  		<option value="segreteria">Segreteria</option>
								</select>
				            </p>
				            <p style="text-align: center;">
				                <label for="data">Data</label>
				                <input type='date' id="data" name='data' placeholder='dd-mm-yyyy' required min="<?echo$oggi;?>">
				            </p>
				        </fieldset>
				        <p style="text-align: center;" class="bottone">
				        	<br />
				        	<button class="bottone-invia" type="submit">Invia</button>
				        </p>
				    </form>
				</article>
				<?
		    }
		    else {
		    	echo "Non sei autenticato";
			}
		?>
		
		</div>
		<?include "sidebar.php";?>
	<div id="footer" class="container">
		<p>Informatica e Culture Digitali | Università degli Studi di Napoli Federico II</p>
		<p>&copy; 2013 Sitename.com. | Photos by <a href="http://fotogrph.com/">Fotogrph</a> | Design by <a href="http://www.freecsstemplates.org/" rel="nofollow">FreeCSSTemplates.org</a>.</p>
	</div>
</body>
</html>