<!DOCTYPE html>
<?php
    $anno = $_GET['anno'];
	$mese = $_GET['mese'];
	if(!empty($anno) && !empty($mese)){
		header("location: http://viaggieservizi.altervista.org/php/calendario.php?anno=".$anno."&mese=".$mese); 
	}
	else{
		header("location: http://viaggieservizi.altervista.org/php/calendario.php"); 
	}
?>
