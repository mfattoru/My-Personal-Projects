<!DOCTYPE html>
<html>
    <head>
    <script type="text/javascript">
	var stile = "top=10, left=10, width=400, height=400, status=no, menubar=no, toolbar=no scrollbars=no";
 
	function Popup(apri) {
	    window.open(apri, "", stile);
	}
    </script>
    </head>
    <body>
	<center><top><h2>Profilo Utente</h2></top></center>
<?php
    session_start();
    //check that user is logged in
    if($_SESSION['matricola']){
	$matricola = $_SESSION['matricola'];
	include 'dbconnect.php';

/***********************************************************************************************************

			    USER INFORMATION
***********************************************************************************************************/

	//make query
	$query ="SELECT nome,cognome,CDL,media_feed FROM Utente WHERE matricola='".$matricola."'";
    
	//execute query
	$result = mysql_query($query);

	//fetch result
	$row = mysql_fetch_array($result);

	//show user information
	print("<table align=\"left\">");
	    print("<tr><td><img src=\"avatar.php?matricola=".$matricola."\" height=\"250\" width=\"200\"></td><tr>");
	    print("<tr><td><button type\"button\" onClick=\"Popup('select_avatar.php')\" >Cambia Avatar</button></td></tr>");
	    print("<tr><td><b>Nome:</b> ".$row[0]."</td></tr>");
	    print("<tr><td><b>Cognome:</b> ".$row[1]."</td></tr>");
	    print("<tr><td><b>CDL:</b> ".$row[2]."</td></tr>");
	    print("<tr><td><b>Media Voti:</b> ".$row[3]."</td></tr>");
	print("</table>");

/***********************************************************************************************************

			    TRAVEL INFORMATION
***********************************************************************************************************/
	/*//make query
	$query = "SELECT * FROM Viaggi WHERE matricola ='".$matricola."'";
	
	//execute query
	$result=mysql_query($query);

	//show travel information
	print("<table border=\"2\">
		    <tr>
			<td><td>
		    </tr>");
	while($row=mysql_fetch_array($result)){
	    print("<tr><td></td></tr>");
	}*/
    }
    else{
	print("sessione scadduta\n");
    }
?>
    </body>
</html>