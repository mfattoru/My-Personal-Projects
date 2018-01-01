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
	
	<style type="text/css">
		article{
		    margin: 0 auto;
		    width: 382px;
		    padding: 20px 32px 20px 32px;
		    border: solid 2px #5B5B5B;
		    border-radius: 16px;
		}
		 
		fieldset{
		    margin: 0;
		    padding: 0;
		    border: none;
		}
		 
		.registrazione p{
		    margin: 20px 0;
		}
		 
		.registrazione label{
		    padding-left: 10px;
		}
		 
		.registrazione input{
		    background-color: #39599F;
		    color: #000000;
		    height: 30px;
		    width: 100%;
		    margin: 8px 0 0;
		    padding: 3px 16px 3px 16px;
		    border: solid 1px #fff;
		    border-radius: 16px;
		    opacity: 0.5;
		     
		    box-sizing: border-box;
		}
		 
		.registrazione input:-moz-placeholder {
		    color: #ccc;
		    font-style: italic;
		}
		 
		.registrazione input::-webkit-input-placeholder {
		    color: #ccc;
		    font-style: italic;
		}
		 
		.registrazione input:hover {
		    opacity: 1;
		}
		 
		.registrazione input:focus {
		    opacity: 1;
		    border-color: #39599F;
		    background-color: #fff;
		    color: #000;
		    outline: none;
		}
		 
		p.bottone{
		    text-align: right;
		    margin-bottom: 0;
		}
		 
		.bottone-invia{
		    color: #fff;
		    background-color: #39599F;
		    opacity: 0.5;
		    height: 62px;
		    width: 62px;
		    border-radius: 50%;
		    border: solid 1px #fff;
		    cursor: pointer;
		 
		    transition: opacity 0.75s ease;
		}
		 
		.bottone-invia:hover {
		    opacity: 1;
		}
	</style>
	
	<!--[if IE 6]>
	<link href="default_ie6.css" rel="stylesheet" type="text/css" />
	<![endif]-->
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
				<li><a href="carhome.php" accesskey="4" title="">Car Pooling</a></li>
				<li><a href="indicazioni.php" accesskey="5" title="">Come Arrivare</a></li>
			</ul>
		</div>
		<div id="login">
			<?include "giulogin.php";?>
		</div>
	</div>
	<div id="welcome" class="wrapper-style1">
		<header class="title">
			<h2>Registrazione</h2>
			<span class="byline">Riempi tutti i campi ed entra a far parte della comunità</span>
		</header>
		
		<?php
		    session_start();
		    if($_SESSION['matricola']) {
				//redirect to home if logged in
				header("Location: ../index.php");
		    }
		    else if($_POST['matricola']) {
		    	
				function randomPassword() {
				    $alphabet = "abcdefghijklmnopqrstuwxyzABCDEFGHIJKLMNOPQRSTUWXYZ0123456789";
				    $pass = array(); //remember to declare $pass as an array
				    $alphaLength = strlen($alphabet) - 1; //put the length -1 in cache
				    for ($i = 0; $i < 8; $i++) {
				        $n = rand(0, $alphaLength);
				        $pass[] = $alphabet[$n];
				    }
				    return implode($pass); //turn the array into a string
				}
		    	
				//check user and password
				include '../DbConnect.php';
				
				$nome  = $_POST['nome'];
				$cogn  = $_POST['cognome'];
				$matr  = $_POST['matricola'];
				$cdl   = $_POST['cdl'];
				$email = $_POST['email'];
				$pass  = randomPassword();
				
				mysql_query("INSERT INTO Utente (nome, cognome, email, matricola, cdl, media_feed, password) 
						VALUES ('$nome', '$cogn', '$email', '$matr', '$cdl', 0, '$pass')");
						
				$oggetto="Viaggi e Servizi, Registrazione";
			    $testo="\n\n Da: Viaggi e servizi - Registrazione utente
			    		\n Le tue credenziali per l'accesso:
			    		\n Matricola: ".$matr.
						"\n Password: ".$pass.
						"\n Ti consigliamo di cambiare la tua password al primo accesso.";
			    $destinatario=$email;
			    
			    // Intestazioni generali
			    $header = "From: Viaggi e Servizi, Registrazione\n";
			    // Intestazioni specifiche per Mail HTML
			    $header .= "MIME-Version: 1.0\n";
			    $header .= "Content-Type: text/html; charset=\"iso-8859-1\"\n";
			    $header .= "Content-Transfer-Encoding: 7bit\n\n";
			           
			    mail($destinatario, $oggetto, $testo, "From: Viaggi e Servizi - Registrazione");
			    
			    echo '<div class="testi" align="center">Registrazione avvenuta con successo!<br>
			    Abbiamo inviato una mail con la password a '.$email.'</div>';
			}
			else {
			    ?>
			    <p>Per inserire informazioni nel nostro calendario o partecipare al car pooling gestito dagli
					 studenti è necessario registrarsi. <br /><strong>Tutti</strong> i campi sono obbligatori.</p>
				<article>
					<form class="registrazione" method="post" action="registrazione.php">
				        <fieldset>
				            <p>
				                <label for="nome">Nome</label>
				                <input type="text" id="nome" name="nome" placeholder="es. Mario" required value="" />
				            </p>
				            <p>
				                <label for="cognome">Cognome</label>
				                <input type="text" id="cognome" name="cognome" placeholder="es. Rossi" required value="" />
				            </p>
				            <p>
				                <label for="email">E-mail</label>
				                <input type="email" id="email" name="email" placeholder="es. mariorossi@studenti.unina.it" required value="" pattern="^[a-z0-9][_.a-z0-9-]+@studenti.unina.it$" title="è possibile effettuare la registrazione soltanto tramite e-mail istituzonale"/>
				            </p>
				 			<p>
				                <label for="nome">Matricola</label>
				                <input type="text" id="matricola" name="matricola" placeholder="es. N86123456" required value="" />
				            </p>
				 			<p>
				                <label for="nome">CdL</label>
				                <input type="text" id="cdl" name="cdl" placeholder="es. Sociologia" required value="" />
				            </p>
				        </fieldset>
				        <p class="bottone">
				        	<br />
				        	<button class="bottone-invia" type="submit">Invia</button>
				        </p>
				    </form>
				</article>
			    <?
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