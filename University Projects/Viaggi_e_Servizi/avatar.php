<?php
    
    header('Content-Type: image/jpg');
    
    $matricola = $_GET[matricola];
    //connect to database
    include 'dbconnect.php';
    
    //make query
    $query ="SELECT avatar FROM Utente WHERE matricola ='".$matricola."'";
    
    //execute query
    $result = mysql_query($query);
    
    //fetch result
    $resultset = mysql_fetch_array($result);

    echo $resultset[0];
?>