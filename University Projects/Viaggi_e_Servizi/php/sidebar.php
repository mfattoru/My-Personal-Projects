<div id="sidebar">
	<a href="../php/cerco.php"><img src="../images/search.png"/> Cerca </a>
	<a href="../php/offro.php"><img src="../images/travel.png"/> Offri </a>
	<a href="../php/profilo.php"><img src="../images/user.png" /> Profilo </a> 
	<a href="../php/calendario.php"><img src="../images/event.png" /> Eventi </a>
	<?
	if($_SESSION['matricola']){
	?>
	<a href="../php/logout.php"><img src="../images/logout.png" /> Logout</a>
	<?
	}
	else{
	?>
	<a href="../php/registrazione.php"><img src="../images/register.png" /> Registrazione</a>
	<?
	}
	?>
	<a href="https://www.facebook.com/Laboratorioaudiovisuale?fref=ts" target="_blank"><img src="../images/facebook.png"; style="max-width:25px"/></a>
	<a href="https://twitter.com/Naplesquare" target="_blank"><img src="../images/twitter.png" style="max-width:25px"; /></a>
	<a href="http://www.youtube.com/NapleSquare" target="_blank"><img src="../images/youtube.png"; style="max-width:25px" /></a>
</div>