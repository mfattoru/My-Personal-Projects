<? session_start() ?>
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
	<!--[if IE 6]>
    <link href="default_ie6.css" rel="stylesheet" type="text/css" />
    <![endif]-->
    <style type="text/css">
        .car-box {
            float:left;
            width:200px;
            text-align:center;
            margin-bottom:30px;
        }
        
        #cont {
            width:400px;
            margin: 0 auto;
        }
        
        .car-box img {
            height:100px;
        }
        
        a {
            text-decoration:none;
        }
        
        a:hover{
            color:#39599F;
        }
    </style>
</head>
<body>
	<div id="header" class="container">
		<div id="logo">
			<img src="../images/logo.jpg" />
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
			<h2>Car Pooling</h2>
            <span class="byline">Benvenuto nel sistema di car pooling</span> </header>
		<?
		if($_SESSION['matricola']){
		?>
		<div id="cont">
		<div class="car-box">
		    <a href="cerco.php"><span style="text-align:center; font-weight: bold;" >CERCA UN VIAGGIO</span>
            <img src="../images/search-icon.png" style="margin: 10px auto;" /></a>
		</div>
		<div class="car-box">
		    <a href="offro.php">
            <span style="text-align:center; font-weight: bold;" >OFFRI UN VIAGGIO</span>
            <img src="../images/offri.jpg" style="margin: 10px auto;" /></a>
        </div>
        </div>
		<div style="clear: both;"></div>
	    <?
        } else {
            ?>
            <a href="#" class="image image-full"><img src="../images/carpoolingg.jpg" alt="" /></a>
            <p><strong>Viaggi e Servizi</strong> di NapleSquare ti permette di entrare a far parte di una grande community che offre 
            servizi di car pooling. Se non lo sai, il car pooling è una modalità di trasporto che consiste nella condivisione di 
            automobili private tra un gruppo di persone, con il fine principale di ridurre i costi del trasporto.
            Se sei uno studente della Federico II puoi iscriverti con la tua email istituzionale e usufruire del servizio. 
            </p>
            <p><strong>Dopo aver effettuato il login potrai utilizzare una toolbar per 
                usufruire delle funzioni di ricerca e offerta di viaggi.</strong></p>
            <?
        }
	   ?>
        <p>
            Condividere l’auto significa suddividere le spese, quindi l'utilizzo sistematico del 
            meccanismo di Car Pooling consente di ridurre fino al 75% (con 4 passeggeri a bordo) il 
            costo di olio e carburante e di eventuali parcheggi o pedaggi.<br />
            Inoltre utilizzando meno l'auto si riducono anche i costi di manutenzione.<br />
            Ad esempio, considerando un costo al km del carburante pari a circa 10 centesimi di euro, 
            ogni componente di un equipaggio di 4 persone può risparmiare:(*)<br />
                - oltre 480 euro all'anno di carburante<br />
                - oltre 335 euro all'anno di pedaggio<br />
            <p style="font-size: 12px">(*) Stima elaborata in caso di utilizzo di un'autovettura di piccola 
                cilindrata (1.200 cc - 82 cv) con le seguenti ipotesi: A) prezzo medio nazionale 2011 della 
                benzina verde pari a ca. 1,62 (fonte: Ministero dello Sviluppo Economico - novembre 2011 - ); B) 
                consumo carburante pari a ca. 17,5 Km/litro nel ciclo misto (fonte: casa automobilistica); C) 
                viaggio giornaliero: 60 km; D) pedaggio al casello di Milano Nord A/R pari a 3,20 euro/giorno; 
                pedaggio con sconto Car Pooling pari a 1,10 euro; E) 231 giorni lavorativi; 73% dei viaggi in 
                modalità Car Pooling con 4 passeggeri.
            </p>
        </p>
    </div>
	<? include "sidebar.php"; ?>
	<div id="footer" class="container">
		<p>Informatica e Culture Digitali | Università degli Studi di Napoli Federico II</p>
		<p>&copy; 2013 Sitename.com. | Photos by <a href="http://fotogrph.com/">Fotogrph</a> | Design by <a href="http://www.freecsstemplates.org/" rel="nofollow">FreeCSSTemplates.org</a>.</p>
	</div>
</body>
</html>