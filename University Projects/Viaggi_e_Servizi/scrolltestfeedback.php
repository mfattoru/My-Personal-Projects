<!DOCTYPE html>
<html>	
<head> 
  <link rel='stylesheet' type='text/css' href='default.css'> 
  <link rel='stylesheet' type='text/css' href='scrollbox.css'>
</head>
 <body>
  <?php
    session_start();
    $_SESSION['matricola'] = "0000";
    //check that user is logged in
    if($_SESSION['matricola']){
	$matricola = $_SESSION['matricola'];
	
	//connect to database
	include 'dbconnect.php';
    
	//make query
	$query ="SELECT commentatore,voto,testo FROM Commenti_Utente WHERE commentato='".$matricola."'";
    
	//execute query
	$result = mysql_query($query);

	print("<div class='box'>");
	print("<div class='inner-box'>");
	if(mysql_num_rows($result) != 0){
	  //fetch result, visualization of 5 or less results
	  $i=0;
      print("<table align='left'>");
	  while( $row = mysql_fetch_array($result) ){
	    print("<tr><td><b>Da:</b> ".$row['commentatore']." </td></tr>");
	    print("<tr><td><b>Voto</b> ".$row['voto']." </td></tr>");
	    print("<tr><td><b>Testo</b>".$row['testo']. " </td></tr>");
	    print("<tr><td><br></td></tr>");
	    $i++;
	  }
	  print("</table>");
	}else{ 
	    echo"Nofeedback"; 
	}
	print("</div>");
	print("</div>");
	}
  ?>
 </body>
</html>