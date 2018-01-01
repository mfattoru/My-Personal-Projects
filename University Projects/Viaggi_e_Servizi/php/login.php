<!DOCTYPE html>

<html>

<head>
	<link href="../css/calendario.css" rel="stylesheet" type="text/css" media="all" />
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
			<h2>Effettua il login</h2>
		</header>
		<p>Errore nell'inserimento dei dati: utente e/o password sbagliati</p>
	</div>

	<div>
<?php
    session_start();
    if($_SESSION['matricola']){
	//redirect to home if logged in
        header("Location: ../index.php");
    }
    else if($_POST['user'] && $_POST['password']){
		//check user and password
		
		include '../dbconnect.php';
		
		//make query
		$query = "SELECT * FROM Utente WHERE matricola='".$_POST['user']."'";
	
		//execute query
		$result = mysql_query($query);
	
		//fetch result
		$row = mysql_fetch_array($result);
		if($row['password'] == $_POST['password']){
		    //authentication ok
		    $_SESSION['matricola'] = $_POST['user'];
		    $_SESSION['nome'] = $row['nome'];
		    $_SESSION['cognome'] = $row['cognome'];
		    $_SESSION['cdl'] = $row['cdl'];
		    $_SESSION['feed'] = $row['media_feed'];
		    header("Location: /index.php");
		}
		else{
			header("Location: ../php/login.php");
		}
    }
    else {
		//there are no session or parameter
		print("
			    <center>
			    <form action=\"../php/carhome.php\" method=\"POST\">
			    <b>Matricola</b><input style =\"position: relative; left: 12px;\" type=\"text\" name=\"user\"><br>
			    <b>Password</b><input style =\" position: relative; left: 10px;\" type=\"password\" name=\"password\"><br>
			    <input type=\"submit\" value=\"invia\">
			    </form>
			    </center>");
    }
?>
		<p style="position: relative; left:38%; color: #39599F;">Hai dimenticato la password? clicca <a style="color: #39599F" href="../php/recuperapassword.php">qui</a></p>
	</div>
	<div id="footer" class="container">
		<p>Informatica e Culture Digitali | Universit&agrave degli Studi di Napoli Federico II</p>
		<p>&copy; 2013 Sitename.com. | Photos by <a href="http://fotogrph.com/">Fotogrph</a> | Design by <a href="http://www.freecsstemplates.org/" rel="nofollow">FreeCSSTemplates.org</a>.</p>
	</div>
</body>
</html>