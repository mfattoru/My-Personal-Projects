<!DOCTYPE html>

<html>

<head>
	<link href="../css/calendario.css" rel="stylesheet" type="text/css" media="all" />
	<link href="../css/imprevisti.css" rel="stylesheet" type="text/css" media="all" />
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<title>Monte di piet&agrave - Info e car pooling</title>
	<meta name="keywords" content="" />
	<meta name="description" content="" />
	<link href="../css/default.css" rel="stylesheet" type="text/css" media="all" />
	<script type="text/javascript" src="../script/imprevisti.js"></script>
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
			<h2>Calendario Eventi</h2>
			<span class="byline">Informati su tutto ci&ograve che avviene nella tua citt&agrave</span> </header>
		<p>Grazie al servizio di gestione imprevisti offerto dal portale Naplesquare viagi e servizi potrai essere informato su tutti gli imprevisti che potrai trovare durante il tuo percorso.Tramite una semplice registrazione inoltre avrai la possibilità di segnalare agli altri utenti la presenza di disagi nella città cliccanndo su un giorno del calendario.</p>
	</div>
	<script src="../script/calendar.js" language="JavaScript" type="text/javascript"></script>
	<div id="footer" class="container">
		<p>Informatica e Culture Digitali | Universit&agrave degli Studi di Napoli Federico II</p>
		<p>&copy; 2013 Sitename.com. | Photos by <a href="http://fotogrph.com/">Fotogrph</a> | Design by <a href="http://www.freecsstemplates.org/" rel="nofollow">FreeCSSTemplates.org</a>.</p>
	</div>
</body>
</html>


