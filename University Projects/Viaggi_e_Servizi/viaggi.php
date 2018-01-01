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
	<link href="css/default.css" rel="stylesheet" type="text/css" media="all" />
	<link href="css/sidebar.css" rel="stylesheet" type="text/css" media="all" />

	
	<!--[if IE 6]>
	<link href="default_ie6.css" rel="stylesheet" type="text/css" />
	<![endif]-->
	
	<link href="css/smoothness/jquery-ui-1.10.3.custom.css" rel="stylesheet">
	<script src="script/jquery-1.9.1.ac.js"></script>
	<script src="script/jquery-ui.ac.js"></script>
	<script src="script/autocomplete.js"></script>
	
	<style type="text/css">
		.viaggio {
			font-size: 1em;
			font-weight: 700;
			padding:10px;
			margin:20px;
	    	height:270px;
	    	width:870px;
	    	margin-left:12%;
	  	}
	   
	   	.viaggio-sx, .viaggio-dx {
	   		float:left;
	  	}
	  	
	  	.viaggio-sx {
	    	width:150px;
	    	padding: 10px;
	  	}
	  	
	  	.viaggio-dx {
	  		width:700px;
	  		margin-top:20px;
	  	}
	  	
	  	.viaggio-dxup {
	  		margin-top:30px;
	   		-moz-border-radius: 10px 10px 10px 10px;
	    	-webkit-border-radius: 10px 10px 10px 10px;
	    	background-color:#39599F;
			color:#FFFFFF;
			padding:10px;
	  	}
	  	
	  	.viaggio-dxdo {
	  		padding-top:20px;
	  	}
	  	
	  	.viaggio-dxdo img {
	  		margin-right: 20px;
	  	}
	  	
	  	.viaggio-titolo {
	  		font-size: 2em;
	  	}
	  	
	  	.viaggio-data {
	  		float:right;
	  	}
	</style>
	
</head>
<body>
	<div id="header" class="container">
		<div id="logo">
			<a href="../index.php"><img src="../../images/logo.jpg" /></a>
		</div>
		<div id="menu"> 
			<ul>
				<li><a href="/index.html" accesskey="1" title="">Homepage</a></li>
				<li><a href="/about.html" accesskey="2" title="">About</a></li>
				<li><a href="/static/calendario.html" accesskey="3" title="">Calendario</a></li>
				<li class="current_page_item"><a href="/php/carhome.php" accesskey="4" title="">Car Pooling</a></li>
				<li><a href="/static/indicazioni.html" accesskey="5" title="">Come Arrivare</a></li>
			</ul>
		</div>
	</div>
	<div id="welcome" class="wrapper-style1">
		<header class="title">
			<h2>Viaggi disponibili</h2>
			<span class="byline">Cerca tra le offerte di viaggio</span>
		</header>
		
		<?php
		    session_start();
		    if(($_SESSION['matricola']) && ($_POST)) {
				// ritrovamento dati
				include_once('DbConnect.php');
				
				$part = $_POST['loc'];
				$dest = $_POST['destinazione'];
				$data = $_POST['data'];
				
				$query = "SELECT * FROM Viaggi";
				$risultati = mysql_query($query)
					or die("Errore nella query: " . mysql_error());
				
				?>
				<article>
					<?
					$n=1;
					while ($riga = mysql_fetch_array($risultati, MYSQL_ASSOC)) { ?>
						<div class="viaggio">
							<div class="viaggio-sx">
								<img src="images/avatar/<?echo $n++?>.jpg" />
								<br />
								Andrea Mato
							</div>
							<div class="viaggio-dx">
								<div class="viaggio-dxup">
									<div class="viaggio-titolo"> <?echo $riga['titolo']?></div>
									<div class="viaggio-data"> <?echo $riga['data']?></div>
									<div class="viaggio-testo"><strong>Partenza: </strong><?echo $riga['partenza']?></div>
									<div class="viaggio-testo"><strong>Destinazione: </strong><?echo $riga['destinazione']?></div>
								</div>
								<div class="viaggio-dxdo">
									<img src="images/icone/facebook.png" />
									<img src="images/icone/Google-plus-icon.png" />
									<img src="images/icone/message-green-icon.png" />
								</div>
							</div>
						</div>
					
					<? } ?>
				</article>
				<?
		    }
		    else {
		    	?><article><?
		    		echo "Non sei autenticato o la sessione è scaduta. Effettua il login.";
		    	?></article><?
			}
		?>
		
		</div>
	<div id="sidebar">
		<a href="../cerco.php"><img src="images/search.png";/> Cerca </a>
		<a href="/offro.php"><img src="/images/travel.png" /> Offri </a>
		<a href="../profilo.html"><img src="/images/user.png" /> Profilo </a>
		<a href="../static/calendario.html"><img src="/images/warning.png" /> Imprevisti </a>
		<a href="/php/logout.php"><img src="/images/logout.png"/> Logout </a>
		<a href="https://www.facebook.com/Laboratorioaudiovisuale?fref=ts"><img src="images/facebook.png"; style="max-width:25px"/></a>
		<a href="https://twitter.com/Naplesquare"><img src="images/twitter.png" style="max-width:25px"; /></a>
		<a href="http://www.youtube.com/NapleSquare"><img src="images/youtube.png"; style="max-width:25px" /></a>
	</div>
	<div id="footer" class="container">
		<p>Informatica e Culture Digitali | Università degli Studi di Napoli Federico II</p>
		<p>&copy; 2013 Sitename.com. | Photos by <a href="http://fotogrph.com/">Fotogrph</a> | Design by <a href="http://www.freecsstemplates.org/" rel="nofollow">FreeCSSTemplates.org</a>.</p>
	</div>
</body>
</html>