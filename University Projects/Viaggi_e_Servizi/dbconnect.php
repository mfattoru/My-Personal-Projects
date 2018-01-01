<?php
    //connect to database,need to do it better
    $host = "localhost";
    $user = "viaggieservizi";
    $pass = "jaQu5esA";
	
    $con = mysql_connect($host,$user,$pass)
		or die("Connessione non riuscita: " . mysql_error());
    
    //connection ok
    mysql_select_db("my_viaggieservizi")
		or die("Connessione non riuscita: " . mysql_error());
?>