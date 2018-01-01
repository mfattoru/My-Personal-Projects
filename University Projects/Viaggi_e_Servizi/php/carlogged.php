<!DOCTYPE html>
<html>
<head>
	<link href="../css/default.css" rel="stylesheet" type="text/css" media="all" />
	<link href="../css/sidebar.css" rel="stylesheet" type="text/css" media="all" />
</head>
<body>
	<div id="header" class="container">
		<div id="logo">
			<a href="../index.php"><img src="../../images/logo.jpg" /></a>
		</div>
		<div id="menu"> 
			<ul>
				<li><a href="../index.html" accesskey="1" title="">Homepage</a></li>
				<li><a href="/about.html" accesskey="2" title="">About</a></li>
				<li><a href="/static/calendario.html" accesskey="3" title="">Calendario</a></li>
				<li  class="current_page_item" ><a href="/php/carhome.php" accesskey="4" title="">Car Pooling</a></li>
				<li><a href="/static/indicazioni.html" accesskey="5" title="">Come Arrivare</a></li>
			</ul>
		</div>
		<div id="login">
			<?php
				session_start();
				if($_SESSION['matricola']){
					print("<div style='width: 140px;'>Benvenuto ".$_SESSION['matricola']."!<br></div>");
					print("<div style='width:140px;'><a href='../../php/logout.php'>Logout</a></div>");
				}else
					print('<div style="width: 50px; float:left;">MATR</div><input style="width: 90px" type="text" /><br />
						<div style="width: 50px; float:left;">PASS</div><input style="width: 90px" type="password" />
						<input type="submit" value="Entra" />');
			?>
		</div>
	</div>
	<div align="center">
		<a href="../php/offro.php">
			<h3>OFFRI UN VIAGGIO</h3><img src="../images/car-icon_lg.png" />
		</a>
		<a href="../cerco.php">
			<h3>CERCA UN VIAGGIO</h3><img src="../images/diario-viaggio-cerca.jpg" />
		</a>
	</div>
	<div id="sidebar">
		<a href="../cerco.php"><img src="../images/search.png";/> Cerca </a>
		<a href="offro.php"><img src="../images/travel.png" /> Offri </a>
		<a href="../profilo.html"><img src="../images/user.png" /> Profilo </a>
		<a href="../static/calendario.html"><img src="../images/warning.png" /> Imprevisti </a>
		<a href="logout.php"><img src="../images/logout.png"/> Logout </a>
		<a href="https://www.facebook.com/Laboratorioaudiovisuale?fref=ts"><img src="../images/facebook.png"; style="max-width:25px"/></a>
		<a href="https://twitter.com/Naplesquare"><img src="../images/twitter.png" style="max-width:25px"; /></a>
		<a href="http://www.youtube.com/NapleSquare"><img src="../images/youtube.png"; style="max-width:25px" /></a>
	</div>
	<div id="footer" class="container">
		<p>Informatica e Culture Digitali | Università degli Studi di Napoli Federico II</p>
		<p>&copy; 2013 Sitename.com. | Photos by <a href="http://fotogrph.com/">Fotogrph</a> | Design by <a href="http://www.freecsstemplates.org/" rel="nofollow">FreeCSSTemplates.org</a>.</p>
	</div>
</body>
</html>

