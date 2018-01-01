
<?
	session_start();
	if($_SESSION['matricola']){
		$nome = $_SESSION['nome'];
		$cognome = $_SESSION['cognome'];
		?>
		<div style="float: left;">
			<img src="../images/avatar/mini.jpg" width="48" />
		</div>
		<div style="float: left; margin-left:5px;">
			<?echo $nome." ".$cognome;?>
			<div style="float: right; margin-top:16px;">
				<a href="../../php/profilo.php">Profilo</a>
				-
				<a href="../../php/logout.php">Logout</a>
			</div>
		</div>
		<?
	} else {
		?>
		<form action="../../php/login.php" method="post">
		<div style="width: 50px; float:left;">MATR</div><input style="width: 90px" type="text" name="user" />
		<br />
		<div style="width: 50px; float:left;">PASS</div><input style="width: 90px" type="password" name="password" />
		<input type="submit" value="Entra" />
		<a href="../../php/registrazione.php">Registrati</a>
		</form>
		<?
	}
?>
